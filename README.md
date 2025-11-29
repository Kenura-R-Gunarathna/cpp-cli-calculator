# C++ Recursive Descent Scientific Calculator

A robust command-line scientific calculator built in C++ using a **Recursive Descent Parser**.

This project demonstrates advanced parsing logic, class-based architecture, and unit testing. It now features **persistent history tracking** using **SQLite**, allowing you to save and review past calculations across sessions.

## Features

- **Arithmetic Operations:** `+`, `-`, `*`, `/`, `%` (Modulus), `^` (Exponents).
- **Mathematical Functions:**
  - Trigonometry: `sin`, `cos`, `tan` (Supports Radians and Degrees).
  - Logarithms: `log` (Base 10), `ln` (Natural log), `log(x, base)` (Custom base).
  - Roots: `sqrt`.
- **Persistent History:** Automatically saves every calculation to a local SQLite database (`calc_history.db`).
- **CLI Modes:** Supports both Interactive (REPL) mode and Command Line Arguments (for scripting).
- **Complex Expressions:** Handles deeply nested parentheses `(( ))` and operator precedence (PEMDAS/BODMAS).
- **Unit Testing:** Includes a dedicated Test Project with 100% pass rate.

## Getting Started

### Prerequisites

- **Visual Studio 2022** (with C++ Desktop Development workload).
- **vcpkg** (C++ Package Manager).
- **SQLite3** (Installed via vcpkg).

### Installation & Build

1. **Install Dependencies:**
   Open a terminal (PowerShell/CMD) and install SQLite for 64-bit Windows using vcpkg:
   ```powershell
   vcpkg integrate install
   vcpkg install sqlite3:x64-windows
   ```

2. **Open the Project:**
   Open `HelloWorld.sln` in Visual Studio.

3. **Configure Build:**
   - Set the build configuration to **Debug** (or Release) and **x64**.
   - *Note: This is required because the SQLite library installed is x64.*

4. **Run:**
   Press **Ctrl + F5** to build and run.

## Usage

### 1. Interactive Mode (REPL)
Run the application without arguments to enter the loop.

```text
>> 2 + 3 * 5
ans = 17

>> sin(30, deg)
ans = 0.5

>> history
--- History ---
2 + 3 * 5 = 17
sin(30, deg) = 0.5
---------------
```

### 2. Command Line Arguments (CLI)
You can use the calculator directly from your terminal without entering the loop.

**Evaluate an expression:**
```powershell
.\HelloWorld.exe eval "log(100) + 5"
# Output: 7
```

**View History:**
```powershell
.\HelloWorld.exe history
# Output: Database dump of past calculations
```

**Help:**
```powershell
.\HelloWorld.exe --help
```

## Project Structure

- **HelloWorld/** (Main Application)
  - `HelloWorld.cpp`: Main entry point (Handles CLI args and REPL loop).
  - `Calculator.h/.cpp`: The Recursive Descent Parser logic.
  - `HistoryManager.h/.cpp`: Handles SQLite database connections and logging.
- **CalculatorTests/** (Unit Tests)
  - `CalculatorTests.cpp`: Logic verification.
  - `HistoryTests.cpp`: Database persistence verification.

## Testing

This project uses the **Microsoft Native Unit Test Framework**.

1. Open the solution in Visual Studio.
2. Go to **Test** > **Test Explorer**.
3. Click **Run All**.
   *(Note: Ensure the Test Project is also set to x64 to match the SQLite dependency).*
