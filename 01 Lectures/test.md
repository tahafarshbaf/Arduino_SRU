# Project 05 — Robotic Hand: Rock, Paper, Scissors

> **Course Level:** Complete Beginner  
> **Estimated Class Time:** 100–120 minutes  
> **Board:** Arduino Uno (or any compatible board)  
> **Prior Knowledge:** Servo library, `.attach()`, `.write()`, `for` loops, functions, Serial Monitor, `bool`, `analogRead()`

---

## Table of Contents

1. [What Are We Building?](#1-what-are-we-building)
2. [What Will You Learn?](#2-what-will-you-learn)
3. [Components Needed](#3-components-needed)
4. [Key Concepts](#4-key-concepts)
5. [Hardware Setup](#5-hardware-setup)
6. [The Code](#6-the-code)
7. [How the Code Works — Step by Step](#7-how-the-code-works--step-by-step)
8. [Exercises & Challenges](#8-exercises--challenges)
9. [Common Mistakes & Troubleshooting](#9-common-mistakes--troubleshooting)
10. [Summary](#10-summary)

---

## 1. What Are We Building?

We will program a **5-fingered robotic hand** to play Rock-Paper-Scissors against a
human player. Each finger is controlled by one servo motor connected to a joint.

The human types their choice (`R`, `P`, or `S`) into the **Serial Monitor**. The Arduino
randomly picks its own choice, moves the hand into the correct shape, calculates who
won, and tracks the score. First to **3 wins** takes the match.

> **Note:** This project covers only the **software and electronics** side.
> The mechanical hand itself is assumed to be pre-built. Our job is to make it move correctly.

---

## 2. What Will You Learn?

By the end of this project you will be able to:

- Store multiple objects in an **array** (e.g., 5 servos in one array)
- Define and use an **`enum`** to represent a fixed set of named choices
- Use **`switch / case`** as a cleaner alternative to long `if / else if` chains
- Generate random numbers with `random()` and improve randomness with `randomSeed()`
- Read and process **String input** from the Serial Monitor
- Use **`static_cast`** to convert between data types
- Structure a complete program into **small, single-purpose functions**
- Understand a **common beginner bug**: `&` vs `&&` and `|` vs `||`

---

## 3. Components Needed

| Quantity | Component | Notes |
|----------|-----------|-------|
| 1 | Arduino Uno | Any compatible clone |
| 5 | Servo motors (SG90 or MG90S) | One per finger |
| 1 | External 5V power supply | Required — 5 servos exceed Arduino's current limit |
| 1 | Breadboard | For power distribution |
| 15 | Jumper wires | 3 per servo (signal, power, GND) |
| 1 | USB cable | For Serial Monitor communication |

### Power Note — Why External Power Is Mandatory Here

In Project 03 we warned about using external power for multiple servos. Here, with
**5 servos** moving simultaneously, it is not optional — it is required.

Five SG90 servos moving at once can draw up to **2.5 A** peak. The Arduino's 5V pin
can supply roughly **0.4–0.5 A**. Without external power, the board will reset or
behave unpredictably mid-game.

**Wiring rule:** External 5V → servo power wires. Arduino GND and external supply
GND must be **connected together** (shared common ground).

---

## 4. Key Concepts

### 4.1 Arrays of Objects

In Project 03 we created one servo: `Servo myServo;`

Now we need five. We could write:

```cpp
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
```

But this is repetitive and hard to maintain. Instead, we use an **array of objects**:

```cpp
Servo servos[5];        // An array that holds 5 Servo objects
```

Elements are accessed by index (0-based):

```cpp
servos[0].write(90);    // Move the first servo
servos[4].write(0);     // Move the fifth servo
```

The real power is using this with a `for` loop:

```cpp
// Move ALL 5 servos to 0° with one loop — instead of 5 separate lines
for (int i = 0; i < 5; i++) {
    servos[i].write(0);
}
```

Similarly, we store the pin numbers in a **parallel array of constants**:

```cpp
const int SERVO_PINS[] = {3, 5, 6, 9, 10};
```

This links index 0 → pin 3, index 1 → pin 5, and so on. Attaching all servos becomes:

```cpp
for (int i = 0; i < 5; i++) {
    servos[i].attach(SERVO_PINS[i]);
}
```

---

### 4.2 `enum` — Named Constants for a Fixed Set of Choices

Rock, Paper, and Scissors are three distinct states. We could represent them as
numbers (0, 1, 2) or strings (`"R"`, `"P"`, `"S"`), but both approaches have problems:

- Numbers are hard to read: what does `if (choice == 2)` mean?
- Strings are slow to compare and prone to typos.

An **`enum`** (enumeration) lets us define a **named set of integer constants**:

```cpp
enum Choice { ROCK, PAPER, SCISSORS, NONE };
```

Under the hood, `ROCK = 0`, `PAPER = 1`, `SCISSORS = 2`, `NONE = 3`. But in the
code we write readable names:

```cpp
Choice userChoice = ROCK;

if (userChoice == PAPER) { ... }   // clear and readable
```

We also declare variables of the enum type:

```cpp
Choice userChoice = NONE;    // type is Choice, value is NONE
Choice pcChoice   = NONE;
```

---

### 4.3 `switch / case`

When you need to do different things depending on the value of one variable,
a `switch` statement is cleaner than a chain of `if / else if`:

```cpp
// Using if/else if — works but verbose:
if (choice == ROCK)     { /* ... */ }
else if (choice == PAPER)    { /* ... */ }
else if (choice == SCISSORS) { /* ... */ }

// Using switch/case — same logic, cleaner layout:
switch (choice) {
    case ROCK:
        // do something
        break;
    case PAPER:
        // do something
        break;
    case SCISSORS:
        // do something
        break;
    default:
        // runs if none of the above matched
        break;
}
```

> **`break` is required.** Without it, execution **falls through** to the next case.
> This is a common and confusing bug — always end each `case` with `break`.

---

### 4.4 `random()` and `randomSeed()`

`random(min, max)` returns a random integer in the range `[min, max-1]`:

```cpp
random(0, 3)   // returns 0, 1, or 2
```

**The problem:** Arduino is a deterministic machine. Without intervention, it produces
the **same sequence of "random" numbers** every time it powers on.

**The fix:** `randomSeed(value)` initializes the random number generator with a
starting value (the *seed*). Using different seeds gives different sequences.

```cpp
randomSeed(analogRead(A0));   // Pin A0 is floating — reads electrical noise
```

An unconnected analog pin reads random electrical noise from the environment.
This gives a different seed every power-on, producing genuinely unpredictable numbers.

> Always call `randomSeed()` once inside `setup()`, before any `random()` call.

---

### 4.5 `static_cast` — Converting Between Types

The result of `random(0, 3)` is an `int`. We want to store it as a `Choice` (our enum).
In C++, this conversion is done explicitly with `static_cast`:

```cpp
pcChoice = static_cast<Choice>(random(0, 3));
```

This tells the compiler: *"I know this integer corresponds to a valid `Choice` value —
convert it."* It is safer than an implicit conversion and makes the intent clear.

---

### 4.6 Reading String Input from Serial Monitor

`Serial.readString()` captures everything the user typed until a timeout:

```cpp
String input = Serial.readString();
input.trim();           // Remove whitespace and newline characters
input.toUpperCase();    // Convert to uppercase so 'r', 'R' both work
```

To extract the first character:

```cpp
char firstChar = input.charAt(0);   // 'R', 'P', or 'S'
```

We then convert this character to our `Choice` enum using a dedicated function:

```cpp
Choice charToChoice(char c) {
    switch (c) {
        case 'R': return ROCK;
        case 'P': return PAPER;
        case 'S': return SCISSORS;
        default:  return NONE;
    }
}
```

---

### 4.7 Critical Bug in the Simple Version — `&` vs `&&` and `|` vs `||`

The simple version of the code uses single `&` and `|` operators:

```cpp
if (receivedChar.startsWith("R") & rand == 2) pc_point++;   // ← BUG
if (user_point == 3 | pc_point == 3) Serial.println(...);   // ← BUG
```

This is one of the most common and confusing beginner mistakes in C/C++:

| Operator | Name | What It Does |
|----------|------|-------------|
| `&&` | Logical AND | Returns `true` if **both** conditions are true. Stops early if first is false (**short-circuit**) |
| `&` | Bitwise AND | Operates on **individual bits** of two integers. Does NOT short-circuit |
| `\|\|` | Logical OR | Returns `true` if **at least one** condition is true |
| `\|` | Bitwise OR | Operates on individual bits. Does NOT short-circuit |

**For conditions in `if` statements, always use `&&` and `||`.**

Using `&` and `|` on boolean-like values often gives the correct result *by accident*
because `true` is represented as 1 and `false` as 0 — but it is semantically wrong,
can cause subtle bugs with non-boolean integers, and prevents short-circuit evaluation.

```cpp
// WRONG — uses bitwise operator on conditions:
if (receivedChar.startsWith("R") & rand == 2)

// CORRECT — uses logical operator:
if (receivedChar.startsWith("R") && rand == 2)
```

---

## 5. Hardware Setup

### Servo-to-Finger Mapping

| Servo Index | Arduino Pin | Finger |
|-------------|------------|--------|
| `servos[0]` | Pin 3 | Thumb |
| `servos[1]` | Pin 5 | Index finger |
| `servos[2]` | Pin 6 | Middle finger |
| `servos[3]` | Pin 9 | Ring finger |
| `servos[4]` | Pin 10 | Pinky |

### Gesture Angle Table

| Gesture | Thumb (0) | Index (1) | Middle (2) | Ring (3) | Pinky (4) |
|---------|-----------|-----------|------------|----------|-----------|
| **Rock** ✊ | 0° | 0° | 0° | 0° | 0° |
| **Paper** 🖐 | 90° | 90° | 90° | 90° | 90° |
| **Scissors** ✌ | 0° | 90° | 90° | 0° | 0° |

> The exact angles depend on how the servos are mechanically installed in the hand.
> 0° = finger closed (curled), 90° = finger open (extended) is assumed here.
> You may need to **reverse these values** (or use different angles) based on your
> specific build.

### Wiring Diagram (Text)

```
External 5V Supply (+) ─── Servo power rails (all red wires)
External 5V Supply (–) ─┬─ Servo ground rails (all brown/black wires)
                         └─ Arduino GND          ← shared ground!

Arduino Pin  3  ─── servos[0] signal (orange/yellow)
Arduino Pin  5  ─── servos[1] signal
Arduino Pin  6  ─── servos[2] signal
Arduino Pin  9  ─── servos[3] signal
Arduino Pin 10  ─── servos[4] signal
```

---

## 6. The Code

### Version 1 — Simple (as written first)

```cpp
#include <Servo.h>

Servo Servo1, Servo2, Servo3, Servo4, Servo5;

String user_choice, pc_choice;
unsigned int user_point = 0, pc_point = 0;

void setup() {
  Serial.begin(9600);

  Servo1.attach(3);   Servo2.attach(5);
  Servo3.attach(6);   Servo4.attach(9);
  Servo5.attach(10);

  // Start in ROCK position (all fingers closed)
  Servo1.write(0);  Servo2.write(0);  Servo3.write(0);
  Servo4.write(0);  Servo5.write(0);
}

void loop() {
  if (Serial.available() > 0) {
    String receivedChar = Serial.readString();

    int rand = random(1, 4);   // 1, 2, or 3

    if (rand == 1) { rock();      pc_choice = "R"; }
    if (rand == 2) { paper();     pc_choice = "P"; }
    if (rand == 3) { scissors();  pc_choice = "S"; }

    // Score logic (note: uses & and | — see Section 4.7)
    if (receivedChar.startsWith("R") && rand == 2) pc_point++;
    if (receivedChar.startsWith("P") && rand == 1) user_point++;
    if (receivedChar.startsWith("R") && rand == 3) user_point++;
    if (receivedChar.startsWith("S") && rand == 1) pc_point++;
    if (receivedChar.startsWith("S") && rand == 2) user_point++;
    if (receivedChar.startsWith("P") && rand == 3) pc_point++;

    Serial.print("You: ");    Serial.print(receivedChar);
    Serial.print("\tPC: ");   Serial.print(pc_choice);
    Serial.print("\tYour points: "); Serial.print(user_point);
    Serial.print("\tPC points: ");   Serial.println(pc_point);

    if (user_point == 3 || pc_point == 3)
      Serial.println("Game finished!");
  }
}

void rock() {
  Servo1.write(0);  Servo2.write(0);  Servo3.write(0);
  Servo4.write(0);  Servo5.write(0);
}

void paper() {
  Servo1.write(90); Servo2.write(90); Servo3.write(90);
  Servo4.write(90); Servo5.write(90);
}

void scissors() {
  Servo1.write(0);  Servo2.write(90); Servo3.write(90);
  Servo4.write(0);  Servo5.write(0);
}
```

**Problems in Version 1 (to discuss with students):**

| Problem | Line | Effect |
|---------|------|--------|
| Original code used `&` and `\|` instead of `&&` and `\|\|` | Score lines, game-over check | Works by accident on booleans, but semantically wrong |
| `random(1, 4)` → values 1, 2, 3 (1-indexed) | rand generation | Inconsistent with convention; `random(0, 3)` is cleaner |
| 5 separate Servo objects | Declaration | Requires 5 lines to attach, 5 lines to move — doesn't scale |
| Score logic spread across 6 `if` statements | `loop()` | Hard to read and verify for correctness |
| No game-over lockout | `loop()` | Game keeps accepting input after "finished" |
| No restart mechanism | — | Must reset the board to play again |

---

### Version 2 — Optimized

```cpp
#include <Servo.h>

// ── Pin & game configuration ──────────────────────────────────
const int SERVO_PINS[]        = {3, 5, 6, 9, 10};
const int NUM_SERVOS          = 5;
const int ROCK_ANGLE          = 0;
const int PAPER_ANGLE         = 90;
const int SCISSORS_OPEN       = 90;
const int SCISSORS_CLOSED     = 0;
const int WIN_SCORE           = 3;

// ── Enum: named constants for the three choices ───────────────
enum Choice { ROCK, PAPER, SCISSORS, NONE };

// ── Global state ──────────────────────────────────────────────
Servo servos[NUM_SERVOS];
Choice userChoice = NONE;
Choice pcChoice   = NONE;
int    userScore  = 0;
int    pcScore    = 0;
bool   gameActive = true;

// ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));       // Seed with electrical noise

  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(SERVO_PINS[i]);
    servos[i].write(ROCK_ANGLE);    // Start in ROCK position
  }

  Serial.println("=== Rock Paper Scissors — Robotic Hand ===");
  Serial.println("Enter: R (Rock)  P (Paper)  S (Scissors)");
}

// ─────────────────────────────────────────────────────────────
void loop() {
  if (!gameActive) {
    if (Serial.available() > 0) {
      String input = Serial.readString();
      input.trim();
      input.toUpperCase();
      if (input == "RESTART" || input == "RESET") {
        resetGame();
        Serial.println("Game restarted! Enter R, P, or S:");
      }
    }
    return;   // Do nothing else if game is over
  }

  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();
    input.toUpperCase();

    userChoice = charToChoice(input.charAt(0));

    if (userChoice == NONE) {
      Serial.println("Invalid input! Use R, P, or S");
      return;
    }

    pcChoice = static_cast<Choice>(random(0, 3));   // 0, 1, or 2 → enum
    moveServosToChoice(pcChoice);

    int result = determineWinner(userChoice, pcChoice);
    updateScore(result);
    displayRoundResult();
    checkGameOver();
  }
}

// ── Convert character to enum ─────────────────────────────────
Choice charToChoice(char c) {
  switch (c) {
    case 'R': return ROCK;
    case 'P': return PAPER;
    case 'S': return SCISSORS;
    default:  return NONE;
  }
}

// ── Move all servos to match a given choice ───────────────────
void moveServosToChoice(Choice choice) {
  switch (choice) {
    case ROCK:
      for (int i = 0; i < NUM_SERVOS; i++)
        servos[i].write(ROCK_ANGLE);
      break;

    case PAPER:
      for (int i = 0; i < NUM_SERVOS; i++)
        servos[i].write(PAPER_ANGLE);
      break;

    case SCISSORS:
      servos[0].write(SCISSORS_CLOSED);   // Thumb  — closed
      servos[1].write(SCISSORS_OPEN);     // Index  — open
      servos[2].write(SCISSORS_OPEN);     // Middle — open
      servos[3].write(SCISSORS_CLOSED);   // Ring   — closed
      servos[4].write(SCISSORS_CLOSED);   // Pinky  — closed
      break;

    default: break;
  }
}

// ── Determine winner: +1 user wins, -1 PC wins, 0 tie ────────
int determineWinner(Choice user, Choice pc) {
  if (user == pc) return 0;
  if ((user == ROCK     && pc == SCISSORS) ||
      (user == PAPER    && pc == ROCK)     ||
      (user == SCISSORS && pc == PAPER))
    return 1;
  return -1;
}

// ── Update scores ─────────────────────────────────────────────
void updateScore(int result) {
  if (result ==  1) userScore++;
  if (result == -1) pcScore++;
}

// ── Print round result to Serial Monitor ─────────────────────
void displayRoundResult() {
  const char* names[] = {"Rock", "Paper", "Scissors"};

  Serial.print("You: ");        Serial.print(names[userChoice]);
  Serial.print(" | PC: ");      Serial.print(names[pcChoice]);
  Serial.print(" | ");

  int result = determineWinner(userChoice, pcChoice);
  if      (result ==  1) Serial.print("You win this round!");
  else if (result == -1) Serial.print("PC wins this round!");
  else                   Serial.print("Tie!");

  Serial.print(" | Score: ");
  Serial.print(userScore);
  Serial.print("-");
  Serial.println(pcScore);
}

// ── Check if match is over ────────────────────────────────────
void checkGameOver() {
  if (userScore >= WIN_SCORE) {
    Serial.println("\n*** Congratulations! You won the match! ***");
    gameActive = false;
  } else if (pcScore >= WIN_SCORE) {
    Serial.println("\n*** Game Over! PC won the match! ***");
    gameActive = false;
  }
  if (!gameActive)
    Serial.println("Type RESTART to play again.");
}

// ── Reset all game state ──────────────────────────────────────
void resetGame() {
  userScore  = 0;   pcScore    = 0;
  gameActive = true;
  userChoice = NONE; pcChoice  = NONE;
  for (int i = 0; i < NUM_SERVOS; i++)
    servos[i].write(ROCK_ANGLE);
}
```

---

## 7. How the Code Works — Step by Step

### Program Flow Diagram

```
Power ON
    │
    ▼
setup():
  randomSeed(analogRead(A0))  ← different seed every power-on
  Attach & home all 5 servos  ← one for loop handles all 5
  Print welcome message
    │
    ▼
loop() — repeating forever:
    │
    ├── gameActive == false?
    │       └── Wait for "RESTART" → resetGame() → continue
    │
    └── Serial input received?
            │
            ▼
        charToChoice(input)
            │
            ├── NONE? → print error, return
            │
            ▼
        random(0,3) → static_cast → pcChoice
            │
            ▼
        moveServosToChoice(pcChoice)  ← hand makes its gesture
            │
            ▼
        determineWinner(user, pc)  → result: +1 / 0 / -1
            │
            ▼
        updateScore(result)
            │
            ▼
        displayRoundResult()
            │
            ▼
        checkGameOver()
            │
            ├── score < WIN_SCORE → keep playing
            └── score ≥ WIN_SCORE → gameActive = false
```

### Why Is `determineWinner()` Separate from `displayRoundResult()`?

In Version 1, the score logic and display are mixed together in `loop()`. This means
to understand what's happening, you have to read the entire function.

In Version 2, each function does **exactly one thing**:

- `determineWinner()` → only computes the result, returns a number
- `updateScore()` → only modifies score variables
- `displayRoundResult()` → only handles printing

This is called the **Single Responsibility Principle**. It makes each function
easy to test, easy to change, and easy to understand independently.

---

## 8. Exercises & Challenges

### Exercise 1 — Add a Delay Before Reveal ⭐

Right now the hand moves instantly. Make it more dramatic: after receiving the user's
choice, print `"3... 2... 1..."` with 700 ms between each number, *then* move the servos.

---

### Exercise 2 — Smooth Gesture Transition ⭐⭐

Instead of snapping directly to the target angle, write a `smoothMove()` function
that sweeps all servos gradually from their current angle to the target angle,
similar to the sweep in Project 03.

```cpp
void smoothMove(int targetAngles[], int steps, int stepDelay) {
    // your code here
}
```

*Hint: Use `servos[i].read()` to get the current angle of each servo.*

---

### Exercise 3 — Score Display with Progress Bar ⭐⭐

After each round, instead of just printing `Score: 2-1`, print a visual bar
in the Serial Monitor:

```
You:  ██░░░  (2/3)
PC:   █░░░░  (1/3)
```

Use a `for` loop to print `█` for earned points and `░` for remaining points.

---

### Exercise 4 — Cheat Detection ⭐⭐

The game currently accepts input like `"Rock"`, `"RRR"`, or `"Rzzz"` as Rock
because it reads only `charAt(0)`. Add input validation:

- Accept **only** single-character inputs: `R`, `P`, or `S`
- If the input is longer than 1 character, print `"Please enter only one letter."`

*Hint: Use `input.length()` to check the number of characters.*

---

### Exercise 5 — Best of N ⭐⭐⭐

Modify the game so the player can choose the **win target** at the start.
At startup, prompt:

```
Enter win target (e.g. 3 for best of 5): 
```

Read the number from Serial, store it in `WIN_SCORE` (which must now be a variable,
not a constant), and play until one player reaches it.

---

### Bonus Challenge — Victory Gesture ⭐⭐⭐

When a player wins the match, make the hand perform a **celebration animation**:
repeatedly alternate between a fist (ROCK) and open hand (PAPER) three times,
then hold the winner's last gesture.

---

## 9. Common Mistakes & Troubleshooting

### One or More Fingers Don't Move

| Possible Cause | Solution |
|----------------|----------|
| That servo's signal wire on wrong pin | Check that `SERVO_PINS[]` matches physical wiring |
| Servo not attached (`.attach()` skipped) | Confirm the `for` loop in `setup()` runs for all 5 |
| Insufficient power | Use external 5V supply — never power 5 servos from the Arduino 5V pin |

---

### Hand Always Makes the Same Gesture

| Possible Cause | Solution |
|----------------|----------|
| `randomSeed()` not called | Add `randomSeed(analogRead(A0))` inside `setup()` |
| A0 pin is connected to something | Leave A0 floating (no wire attached) for noise-based seeding |

---

### Game Does Not Stop at 3 Points

| Possible Cause | Solution |
|----------------|----------|
| Using `=` instead of `==` in comparison | `if (userScore = 3)` assigns; `if (userScore == 3)` compares |
| Using `\|` instead of `\|\|` | Bitwise vs. logical operator (see Section 4.7) |
| `checkGameOver()` not called | Verify it is called at the end of every round |

---

### `static_cast` Gives Wrong Choices

If `pcChoice` always shows the same value, the `random()` function may not be
seeded. If `static_cast` throws a warning, ensure `random(0, 3)` produces only
0, 1, or 2 — which map cleanly to `ROCK`, `PAPER`, `SCISSORS`.

---

### Serial Monitor Shows Garbage on Input

| Possible Cause | Solution |
|----------------|----------|
| Baud rate mismatch | Set Serial Monitor to **9600** baud |
| Line ending adds extra characters | Call `input.trim()` after `readString()` |
| User typed lowercase | Call `input.toUpperCase()` before processing |

---

### `switch` Falls Through to Next Case

If you forget `break`, execution continues into the next `case`:

```cpp
switch (choice) {
    case ROCK:
        moveToRock();
        // ← missing break! Falls into PAPER case
    case PAPER:
        moveToPaper();
        break;
}
```

If the hand moves to Paper when you expected Rock, check every `case` for a missing `break`.

---

## 10. Summary

This project combined servo motor control with a complete interactive program.
You learned:

- **Arrays of objects** (`Servo servos[5]`) let you manage many instances of the
  same component with a single loop, instead of duplicating code.
- **`enum`** defines a set of named constants, making code self-documenting and
  preventing invalid values.
- **`switch / case`** cleanly handles multi-branch logic based on a single variable.
  Always end each `case` with `break`.
- **`random(min, max)`** generates pseudo-random integers. **`randomSeed()`** with
  a floating analog pin makes the sequence genuinely unpredictable.
- **`static_cast<Type>(value)`** converts between types explicitly — essential when
  assigning a random integer to an enum variable.
- **`&&` and `||`** are the correct logical operators for conditions. **`&` and `|`**
  are bitwise operators and must not be used for `if` conditions.
- **Single-responsibility functions** (`determineWinner`, `updateScore`, `displayRoundResult`)
  make complex programs easy to read, test, and modify.

### New Syntax Introduced

| Feature | Example |
|---------|---------|
| Array of objects | `Servo servos[5];` |
| Parallel constant array | `const int SERVO_PINS[] = {3, 5, 6, 9, 10};` |
| Enum definition | `enum Choice { ROCK, PAPER, SCISSORS, NONE };` |
| Enum variable | `Choice userChoice = NONE;` |
| switch / case | `switch(c) { case 'R': return ROCK; break; }` |
| randomSeed | `randomSeed(analogRead(A0));` |
| random range | `random(0, 3)` → 0, 1, or 2 |
| static_cast | `static_cast<Choice>(random(0, 3))` |
| String methods | `.trim()`, `.toUpperCase()`, `.charAt(0)`, `.length()` |

### New Vocabulary

`array of objects` · `enum` · `enumeration` · `switch` · `case` · `break` · `fall-through`
`randomSeed` · `pseudo-random` · `static_cast` · `type conversion` · `logical AND/OR`
`bitwise AND/OR` · `single responsibility` · `game state` · `latch`

---

*Next Project → **LCD + Sensor Dashboard**: Displaying live sensor data on a 16×2 LCD screen.*