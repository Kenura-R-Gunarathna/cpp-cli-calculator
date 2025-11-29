# C++ Recursive Descent Scientific Calculator


A robust command-line scientific calculator built in C++ using a **Recursive Descent Parser**. 

This project demonstrates advanced parsing logic, class-based architecture, and unit testing using the Microsoft Native Unit Test Framework.


## Features


- **Arithmetic Operations:** `+`, `-`, `*`, `/`, `%` (Modulus), `^` (Exponents).

- **Mathematical Functions:**

  - Trigonometry: `sin`, `cos`, `tan` (Supports Radians and Degrees).

  - Logarithms: `log` (Base 10), `ln` (Natural log), `log(x, base)` (Custom base).

  - Roots: `sqrt`.

- **Complex Expressions:** Handles deeply nested parentheses `(( ))` and operator precedence (PEMDAS/BODMAS).

- **Architecture:** Separated logic into a reusable `Calculator` class (`.h` and `.cpp`).

- **Unit Testing:** Includes a dedicated Test Project with 100% pass rate.


## Getting Started


### Prerequisites

- Visual Studio 2022 (with C++ Desktop Development workload).


### How to Build and Run

1. Open `HelloWorld.sln` in Visual Studio.

2. Set `HelloWorld` as the **Startup Project** (Right-click project -> Set as Startup Project).

3. Press **Ctrl + F5** to run.


### Usage Examples


```text

>> 2 + 3 * 5

ans = 17


>> (2 + 3) * 5

ans = 25


>> sin(30, deg)

ans = 0.5


>> log(100)

ans = 2


>> log(8, 2)

ans = 3


>> 2 * (3 + (4^2))

ans = 38

```


## Project Structure


- **HelloWorld/** (Main Application)

  - `HelloWorld.cpp`: Main entry point (loop and user input).

  - `Calculator.h`: Class declaration.

  - `Calculator.cpp`: Implementation of the Recursive Descent Parser.

- **CalculatorTests/** (Unit Tests)

  - `CalculatorTests.cpp`: Contains test cases verifying math logic and edge cases.


## Testing


This project uses the **Microsoft Native Unit Test Framework**.

1. Open the solution in Visual Studio.

2. Go to **Test** > **Test Explorer**.

3. Click **Run All**.
