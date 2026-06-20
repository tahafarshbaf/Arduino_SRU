# Hands on Arduino!

**Beginner Arduino programming course — Shahid Rajaei University**

A from-scratch, project-based path into embedded systems: starting from "what is a microcontroller" and ending with a working security system, built one concept at a time.


## 📖 Lectures

Each lecture lives in [`01 Lectures/`](./01%20Lectures) and builds directly on the one before it.

| # | Lecture | What it covers |
|---|---|---|
| 01 | [Introduction](<./01 Lectures/01-Introduction.md>) | Arduino's history, the Uno R3 board, the ATmega328P microcontroller |
| 02 | [C Overview](<./01 Lectures/02-C Overview.md>) | Variables, loops, conditionals, functions — the language fundamentals |
| 03 | [Blink](<./01 Lectures/03-Blink.md>) | Your first program: digital output, `pinMode`, `digitalWrite` |
| 04 | [Potentiometer](<./01 Lectures/04-Potentiometer.md>) | Analog input, `analogRead`, mapping values |
| 05 | [Fire Alarm System](<./01 Lectures/05-Fire%20Alarm%20System.md>) | Sensors, thresholds, conditional logic in a real project |
| 06 | [Servo](<./01 Lectures/06-Servo.md>) | PWM signals and controlling a servo motor |
| 07 | [Security System](<./01 Lectures/07-Security%20System.md>) | Putting it all together — sensors, logic, and actuation in one build |
| — | [Advanced](<./01 Lectures/Advanced.md>) | Enums, state machines, and cleaner control-flow patterns |

<br/>

## 📝 Assignments

Practice problems live in [`02 Assignments/`](./02%20Assignments). These lean on the C fundamentals from Lecture 02 — series, number theory, numerical approximation — to build programming muscle before it gets applied to hardware.

- [HW01](<./02 Assignments/HW01.md>) — factorial series, Armstrong numbers, Goldbach's conjecture, prime/perfect number checks, and Taylor series approximations (π and sine)

<br/>

## 🖥️ Online Compilers

No local setup needed to start writing C:

1. [Compiler 1](https://compiler.edroca.com/)
2. [Compiler 2](https://matlabkar.com/tryit_codes/tryit.php?lang=c_gcc)
3. [Compiler 3](https://sourcesara.com/compiler/editor/c)

<br/>

## 🔧 Simulators

**Why use a simulator?**

- **Zero risk, zero cost** — you can't damage components with a wrong connection, and it's free to start
- **Convenience and speed** — no waiting for parts to ship or debugging physical wiring; test an idea instantly
- **Accessibility** — anyone with a browser can learn embedded systems without buying hardware first

**Online:**
1. [Wokwi](https://wokwi.com/) — free simulator for Arduino, ESP32, and Raspberry Pi Pico, entirely in-browser
2. [Tinkercad](https://www.tinkercad.com/) — best known for 3D design, but its Circuits feature simulates electronics and microcontrollers too

**Offline:**
1. [Fritzing](https://soft98.ir/software/engineering/199-fritzing.html)
2. [Proteus](https://soft98.ir/software/engineering/3535-%D8%AF%D8%A7%D9%86%D9%84%D9%88%D8%AF-proteus.html)

<br/>

## 📚 References

1. *Beginning C for Arduino* — Jack Purdum, Ph.D.
2. *Arduino Key* — Ardeshir Hakimi

<br/>

## 🛠️ Getting Started

1. Pick a compiler or simulator from above (Wokwi is the easiest starting point — no installs, no hardware required).
2. Read [Lecture 01](<./01 Lectures/01-Introduction.md>) and work through the syllabus in order.
3. Try [HW01](<./02 Assignments/HW01.md>) once you've finished the C Overview lecture.
4. Build each hardware project (Blink → Potentiometer → Fire Alarm → Servo → Security System) as you reach it — reading without building won't stick.

<br/>

## License

MIT — see [LICENSE](./LICENSE).
