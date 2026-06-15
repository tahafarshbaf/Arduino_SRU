# Project 07 — Security System: Keypad, LCD & Persistent User Database


## 1. What Are We Building?

We will build an **entrance security system** for a building, similar to a keypad
door lock used in offices and apartment buildings.

- A **4×4 matrix keypad** lets people enter a **User ID** and a **PIN code**.
- A **16×2 I2C LCD** displays prompts, feedback, and menus.
- A **green LED** lights up when access is granted.
- A **red LED** lights up when access is denied.
- All user accounts and PINs are stored in **EEPROM**, so they survive power loss.

### User Numbering Scheme

| User ID | Role |
|---------|------|
| **0** | **Administrator** — can add new users or change anyone's PIN |
| **1 – 10** | Regular building users, each with their own PIN |

The administrator logs in with ID `0` and the **admin password**. From the admin
menu, they can register a new user or update an existing user's PIN — both using
the same simple operation: *"set User ID `X`'s PIN to `____`."* If User `X` didn't
exist before, this operation creates them. If they did exist, it overwrites their PIN.

### Security Feature: Lockout

If **3 wrong PIN attempts** are made in a row (for any user, including admin),
the system locks for **30 seconds**, displaying a warning and ignoring all key presses.
This is standard behavior in real access-control systems and prevents brute-force guessing.

---

## 2. What Will You Learn?

By the end of this project you will be able to:

- Understand **I2C communication** and why it only needs two signal wires
- Install and use **third-party libraries** (Keypad, LiquidCrystal_I2C)
- Control a **character LCD**: positioning text, clearing the screen, printing variables
- Read a **matrix keypad** using a 2D array (`keymap`)
- Use **EEPROM** to store data that survives power loss
- Design a simple **address layout** for storing structured data in EEPROM
- Build a **multi-state state machine** with `enum` for a menu-driven system
- Build up user input character-by-character into a `String`
- Implement a basic **security lockout** using `millis()`

---

## 3. Components Needed

| Quantity | Component | Notes |
|----------|-----------|-------|
| 1 | Arduino Uno | Any compatible clone |
| 1 | 4×4 Matrix Keypad | 16 keys: 0–9, A–D, `*`, `#` |
| 1 | 16×2 LCD with I2C backpack (PCF8574) | Only 4 wires needed: VCC, GND, SDA, SCL |
| 1 | Green LED | Access granted indicator |
| 1 | Red LED | Access denied / lockout indicator |
| 2 | 220 Ω resistors | One per LED |
| 1 | Breadboard | |
| Several | Jumper wires | |
| 1 | USB cable | |

> **Why I2C LCD instead of a regular parallel LCD?**  
> A standard 16×2 LCD needs **6+ digital pins**. Our keypad already needs **8 pins**.
> An I2C backpack reduces the LCD to just **2 signal wires (SDA, SCL)** — freeing up
> almost all of the Arduino's pins for the keypad and LEDs.

---

## 4. Key Concepts

### 4.1 I2C Communication and the `Wire` Library

**I2C (Inter-Integrated Circuit)** is a communication protocol that lets multiple
devices share just **two wires**:

| Wire | Name | Purpose |
|------|------|---------|
| **SDA** | Serial Data | Carries the actual data |
| **SCL** | Serial Clock | Synchronizes timing between devices |

On Arduino Uno, these are fixed to specific pins:

| Signal | Arduino Uno Pin |
|--------|----------------|
| SDA | **A4** |
| SCL | **A5** |

Every I2C device has a unique **address** (a number from 0–127) so the Arduino can
talk to multiple devices on the same two wires without confusion. The `Wire` library
(built into Arduino) handles the low-level protocol — we rarely call it directly,
but library authors use it internally.

> **Finding your LCD's address:**  
> Most I2C LCD backpacks use address `0x27` or `0x3F`. If your LCD shows nothing,
> see the **I2C Scanner** tool in Section 5.

### 4.2 Installing Third-Party Libraries

So far we have only used the **Servo** library, which comes built into the Arduino IDE.
This project needs **two libraries that must be installed manually**:

- `Keypad` by Mark Stanley & Alexander Brevig
- `LiquidCrystal_I2C` by Frank de Brabander (or "Lucas Maziero" fork — either works)

**To install a library:**

1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for the library name
4. Click **Install**

Once installed, `#include <LibraryName.h>` works exactly like the built-in libraries.

### 4.3 The LiquidCrystal_I2C Library

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // I2C address, columns, rows
```

| Method | What It Does |
|--------|-------------|
| `lcd.init()` | Initialize the display (call once in `setup()`) |
| `lcd.backlight()` | Turn on the backlight |
| `lcd.clear()` | Erase everything on the screen |
| `lcd.setCursor(col, row)` | Move the "cursor" to a position (0-indexed: columns 0–15, rows 0–1) |
| `lcd.print(value)` | Print text or a number at the current cursor position |

**Example — print on both lines:**

```cpp
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Enter User ID:");
lcd.setCursor(0, 1);
lcd.print("> ");
```

> Unlike `Serial.println()`, the LCD does **not** scroll or wrap automatically.
> Text that goes past column 15 simply disappears. Always call `lcd.clear()`
> before drawing a new screen to avoid leftover characters.

### 4.4 Matrix Keypads and 2D Arrays

A 4×4 matrix keypad has **16 buttons** but only **8 wires** (4 rows + 4 columns).
Each button sits at the intersection of one row wire and one column wire. The
`Keypad` library scans these wires to determine which button is pressed.

We describe the button layout using a **2D array** (an array of arrays):

```cpp
char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
```

`keys[row][col]` — for example, `keys[0][0]` is `'1'`, `keys[3][2]` is `'#'`.

Setting up the keypad object:

```cpp
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = {9, 8, 7, 6};   // Connect to keypad row pins
byte colPins[COLS] = {5, 4, 3, 2};   // Connect to keypad column pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
```

Reading a key press is a single line:

```cpp
char key = keypad.getKey();   // Returns the character, or NO_KEY (0) if nothing pressed
```

> **`if (key)`** works because `NO_KEY` is defined as `0`, and `0` is `false` in
> a boolean context — so `if (key)` is `true` only when a real key was pressed.

### 4.5 EEPROM — Storage That Survives Power Loss

Every variable we've used so far lives in **RAM**, which is **erased when power is
removed**. For a security system, this is a problem — every power cycle would
forget all registered users and reset PINs to default!

**EEPROM** (Electrically Erasable Programmable Read-Only Memory) is a small
separate memory chip built into the Arduino that **retains data without power**.
Arduino Uno has **1024 bytes** of EEPROM.

```cpp
#include <EEPROM.h>
```

| Function | Use For | Notes |
|----------|---------|-------|
| `EEPROM.write(address, byteValue)` | Writing a single byte (0–255) | |
| `EEPROM.read(address)` | Reading a single byte | |
| `EEPROM.put(address, variable)` | Writing any data type (int, float, etc.) | Only writes if the value actually changed |
| `EEPROM.get(address, variable)` | Reading any data type | |

> ⚠️ **EEPROM has a limited lifespan**: approximately **100,000 write cycles**
> per memory cell. `EEPROM.put()` checks whether the value has changed before
> writing, automatically protecting the chip. Avoid calling `EEPROM.write()`
> repeatedly in a loop with changing values.

#### The "First Run" Problem

The very first time your code runs on a fresh Arduino, EEPROM contains **random
leftover data** from the factory or previous sketches. We need a way to detect
"has this EEPROM ever been set up by *our* program?"

**Solution: a "magic number."** We reserve address 0 for a special marker byte.
On startup, we check if it matches our chosen magic number:

```cpp
const byte EEPROM_MAGIC = 0xCD;   // arbitrary "signature" value

if (EEPROM.read(0) != EEPROM_MAGIC) {
    // EEPROM has never been initialized by this program — set defaults
    // ... write default values ...
    EEPROM.write(0, EEPROM_MAGIC);   // mark as initialized
}
```

After this runs once, the magic number is permanently stored, and every future
power-on skips re-initialization — preserving any changes the admin made.

### 4.6 Designing a User Database in EEPROM

We need to store, for each user ID 1–10:

- An **active flag** (1 byte): is this user ID registered? (0 = no, 1 = yes)
- A **PIN** (an `int`, 2 bytes on Arduino Uno)

Plus one admin PIN (`int`, 2 bytes) and one magic-number byte.

We calculate addresses using simple formulas instead of hardcoding 30+ numbers:

```cpp
const int EEPROM_FLAG_ADDR  = 0;     // 1 byte  — magic number
const int EEPROM_ADMIN_ADDR = 1;     // 2 bytes — admin PIN (addresses 1-2)

// User i's data starts at address 3 + (i-1)*3
//   byte 0 of that block: active flag
//   bytes 1-2:            PIN (int)

int userActiveAddr(int userID)   { return 3 + (userID - 1) * 3; }
int userPasswordAddr(int userID) { return 4 + (userID - 1) * 3; }
```

**Memory map for MAX_USERS = 10:**

| Address Range | Contents |
|----------------|----------|
| 0 | Magic number (initialization flag) |
| 1–2 | Admin PIN |
| 3 | User 1 active flag |
| 4–5 | User 1 PIN |
| 6 | User 2 active flag |
| 7–8 | User 2 PIN |
| ... | ... |
| 30 | User 10 active flag |
| 31–32 | User 10 PIN |

Total used: **33 bytes** out of 1024 available — plenty of room to spare.

### 4.7 Extended State Machines

In Project 04, our fire alarm had two states: NORMAL and ALARM. This project needs
**many more states** because it behaves like a menu system:

```cpp
enum SystemState {
  IDLE,                  // "Enter User ID:"
  ENTERING_ID,           // user is typing their ID
  ENTERING_PASSWORD,     // user is typing their PIN
  ADMIN_MENU,            // admin logged in, showing menu
  ADMIN_SELECT_USER,     // admin is typing which user to edit
  ADMIN_NEW_PASSWORD,    // admin is typing the new PIN for that user
  LOCKED_OUT             // too many wrong attempts — ignore input
};

SystemState state = IDLE;
```

A `switch` on `state` inside `loop()` decides **how to interpret the next key press**
— the same key (`'5'`, for example) means something different depending on the
current state: part of an ID, part of a PIN, or part of a new password.

### 4.8 Building Input from Key Presses

The keypad gives us **one character at a time**. We accumulate these into a `String`
until the user presses `#` (submit) or `*` (cancel):

```cpp
String inputBuffer = "";

// On each numeric key press:
if (key >= '0' && key <= '9') {
    inputBuffer += key;          // Append digit to the string
}

// On '#' (submit):
int value = inputBuffer.toInt();  // Convert "1234" → 1234
inputBuffer = "";                 // Clear for next entry
```

> **Limitation to be aware of:** `"0012".toInt()` returns `12`, not `0012`. If a
> PIN is stored as `12` and the user types `"0012"`, it will still match — both
> become `12` after `toInt()`. This is consistent (both sides go through the same
> conversion) but means **leading zeros don't make PINs more unique**. See
> Exercise 6 for a fix using `String` comparison instead.

---

## 5. Hardware Setup

### Pin Connections

| Component | Arduino Pin |
|-----------|------------|
| Keypad Row 1–4 | 9, 8, 7, 6 |
| Keypad Col 1–4 | 5, 4, 3, 2 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| LCD VCC | 5V |
| LCD GND | GND |
| Green LED (+) | 220Ω → Pin 11 |
| Red LED (+) | 220Ω → Pin 12 |
| Both LED (–) | GND |

### Wiring Diagram (Text)

```
Arduino                 4x4 Keypad
─────────              ────────────
Pin 9  ─────────────── R1
Pin 8  ─────────────── R2
Pin 7  ─────────────── R3
Pin 6  ─────────────── R4
Pin 5  ─────────────── C1
Pin 4  ─────────────── C2
Pin 3  ─────────────── C3
Pin 2  ─────────────── C4

Arduino                 I2C LCD Backpack
─────────              ──────────────────
5V     ─────────────── VCC
GND    ─────────────── GND
A4     ─────────────── SDA
A5     ─────────────── SCL

Arduino                 LEDs
─────────              ──────────────────
Pin 11 ── [220Ω] ────── Green LED (+) ── GND
Pin 12 ── [220Ω] ────── Red LED (+)   ── GND
```

### Tool: I2C Address Scanner

If the LCD shows nothing (blank or solid blocks), upload this small sketch first
to find your LCD's actual I2C address:

```cpp
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Scanning I2C bus...");

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  Serial.println("Scan complete.");
}

void loop() {}
```

Use the address printed here (commonly `0x27` or `0x3F`) in your `LiquidCrystal_I2C`
constructor.

### LCD Contrast

Many I2C LCD backpacks have a small **potentiometer**. If the screen is blank or
shows solid black blocks, turn this potentiometer with a screwdriver until text
becomes visible — this adjusts contrast, not brightness.

---

## 6. The Code

### Version 1 — Single Shared Password (Foundation)

This version introduces the LCD, keypad, and EEPROM with the **simplest possible**
design: one shared PIN for the whole building, no users, no admin.

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <EEPROM.h>

// ── LCD setup ──────────────────────────────────────────────────
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Change 0x27 if your scanner found a different address

// ── Keypad setup ───────────────────────────────────────────────
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ── LEDs ───────────────────────────────────────────────────────
const int GREEN_LED = 11;
const int RED_LED   = 12;

// ── EEPROM layout ────────────────────────────────────────────
const int  EEPROM_FLAG_ADDR     = 0;
const int  EEPROM_PASSWORD_ADDR = 1;       // 2 bytes (int)
const byte EEPROM_MAGIC         = 0xAB;
const int  DEFAULT_PASSWORD     = 1234;

String enteredPIN = "";

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  initializeEEPROM();
  showIdleScreen();
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;          // No key pressed — do nothing

  if (key >= '0' && key <= '9') {
    if (enteredPIN.length() < 4) {
      enteredPIN += key;
      updatePINDisplay();
    }
  } else if (key == '#') {
    checkPassword();
  } else if (key == '*') {
    enteredPIN = "";
    showIdleScreen();
  }
}

// ── EEPROM setup on first run ─────────────────────────────────
void initializeEEPROM() {
  if (EEPROM.read(EEPROM_FLAG_ADDR) != EEPROM_MAGIC) {
    EEPROM.put(EEPROM_PASSWORD_ADDR, DEFAULT_PASSWORD);
    EEPROM.write(EEPROM_FLAG_ADDR, EEPROM_MAGIC);
  }
}

// ── Display helpers ────────────────────────────────────────────
void showIdleScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter PIN:");
  lcd.setCursor(0, 1);
}

void updatePINDisplay() {
  lcd.setCursor(0, 1);
  for (unsigned int i = 0; i < enteredPIN.length(); i++) {
    lcd.print('*');             // Show stars instead of digits
  }
}

// ── Password check ─────────────────────────────────────────────
void checkPassword() {
  int storedPassword;
  EEPROM.get(EEPROM_PASSWORD_ADDR, storedPassword);

  int entered = enteredPIN.toInt();

  lcd.clear();
  lcd.setCursor(0, 0);

  if (entered == storedPassword) {
    lcd.print("Access Granted");
    digitalWrite(GREEN_LED, HIGH);
    delay(2000);
    digitalWrite(GREEN_LED, LOW);
  } else {
    lcd.print("Access Denied");
    digitalWrite(RED_LED, HIGH);
    delay(2000);
    digitalWrite(RED_LED, LOW);
  }

  enteredPIN = "";
  showIdleScreen();
}
```

**Try it:** The default PIN is `1234`. Enter `1`, `2`, `3`, `4`, then `#`.





---

### Why Check Lockout at the Very Top of `loop()`?

```cpp
if (state == LOCKED_OUT) {
  if (millis() - lockoutStart >= LOCKOUT_TIME) {
    wrongAttempts = 0;
    resetToIdle();
  }
  return;
}
```

This is checked **before** reading the keypad. While locked out, the function
returns immediately — the keypad is never even read, so **no key press has any
effect** until the timer expires. This is the same `millis()`-based non-blocking
timing pattern used for tracking elapsed time without freezing the program with
`delay()`.

### Why Is `'A'` Used for the Admin Menu, Not a Number?

Numbers `0`–`9` are reserved for entering IDs and PINs. The extra keys `A`, `B`,
`C`, `D` on a 4×4 keypad are "free" — perfect for menu commands that should never
be confused with numeric input.

### Tracing an Example: Admin Edits User 3

1. Admin presses `0`, `#` → `currentUserID = 0`, state → `ENTERING_PASSWORD`
2. Admin types `9999`, `#` → matches `EEPROM_ADMIN_ADDR` → `showAdminMenu()`
3. Admin presses `A` → state → `ADMIN_SELECT_USER`, prompt "User ID (1-10):"
4. Admin types `3`, `#` → `targetUserID = 3`, state → `ADMIN_NEW_PASSWORD`
5. Admin types `5`, `5`, `5`, `5`, `#` →
   - `EEPROM.put(userPasswordAddr(3), 5555)`
   - `EEPROM.write(userActiveAddr(3), 1)`
   - "User Saved!" → back to `ADMIN_MENU`
6. Admin presses `*` → `resetToIdle()`

Now User `3` can log in with PIN `5555`, even after the Arduino is unplugged
and plugged back in — because the data lives in EEPROM, not RAM.

---

## 8. Exercises & Challenges

### Exercise 1 — Change Default Admin PIN ⭐

Change `DEFAULT_ADMIN_PIN` to a 4-digit PIN of your choice. Re-upload the code.

**Question:** Does the new default take effect immediately? Why or why not?
*(Hint: think about `EEPROM_MAGIC` and the "first run" check.)*

---

### Exercise 2 — Add Buzzer Feedback ⭐⭐

Using `tone()` and `noTone()` from Project 04:

- Play a **short high beep** (1500 Hz, 100 ms) on **Access Granted**
- Play a **lower, longer beep** (300 Hz, 400 ms) on **Access Denied**
- Play **three descending beeps** when entering `LOCKED_OUT`

---

### Exercise 3 — Lockout Countdown on LCD ⭐⭐

While `state == LOCKED_OUT`, update the second line of the LCD every second to
show a countdown:

```
Too Many Tries!
Wait: 27 sec
```

*Hint: Calculate `remaining = (LOCKOUT_TIME - (millis() - lockoutStart)) / 1000`
and only call `lcd.print()` when this value changes, to avoid constant flickering.*

---


---



### Exercise 5 — Fix the Leading-Zero PIN Problem ⭐⭐⭐

As discussed in Section 4.8, `"0012"` and `"12"` are treated as the same PIN
because both become `12` after `.toInt()`.

Modify the system to store and compare PINs **as 4-character strings** instead
of integers, so `"0012"` and `"12"` are different PINs.

*Hint: `EEPROM.put()` can store a `char[5]` array. You'll need to pad shorter
entries with leading zeros before saving, or require exactly 4 digits before
accepting `#`.*
