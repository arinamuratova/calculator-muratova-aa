# Calculator Application  

## What has been done?  

This project implements a console-based calculator that supports:  
- Basic arithmetic operations: addition, subtraction, multiplication, and division.  
- Floating-point numbers: an optional mode for decimal calculations.  
- Parentheses: for controlling the order of operations.  
- Error handling: warnings for division by zero, incorrect input, unrecognized characters, and mismatched parentheses.  

### Key Features:  
- Supports +, -, *, / operations.  
- Switchable between integer and floating-point modes (--float).  
- Recognizes expressions with parentheses, e.g., (2 + 3) * 5.  
- Displays error messages for invalid input.  

Example expressions:  
- 5 + 3 → 8  
- 10 / 2 → 5  
- 3 * (2 + 1) → 9  
- 5.5 * 2 (in --float mode) → 11.0000  

## How to run/use it?  

### 1. Clone the Repository  

Clone the repository using:  

git clone https://github.com/your-username/calculator.git
cd calculator

### 2. Build the Application  

Use the Makefile to build the project:  

make 

This will generate an executable file app.exe in the build directory.  

### 3. Run the Calculator  

#### Standard Mode (Integer Calculation):  

./build/app.exe "5 + 3"

Output:  

8

#### Floating-Point Mode:  

./build/app.exe --float "5.5 * 2"

Output:  

11.0000 

#### Error Handling Example  

./build/app.exe "10 / 0"

Output:  

Ошибка: некорректное выражение 

### 4. Run the Tests  

The project includes unit tests and integration tests.  

#### Run Unit Tests:  

make run-tests 

#### Run Integration Tests:  

make run-integration-tests 

## How it's made?  

The calculator is implemented in C and processes mathematical expressions using parsing and computation logic.  

### 1. Expression Parsing  

The program analyzes the input string and identifies:  
- Operands (integers and floating-point numbers).  
- Operators (+, -, *, /).  
- Parentheses for operation precedence.  

### 2. Expression Evaluation  

The program follows the PEMDAS rule (Parentheses, Exponents, Multiplication/Division, Addition/Subtraction):  
1. Parentheses are evaluated first.  
2. Then multiplication and division.  
3. Finally, addition and subtraction.  

It supports both integer and floating-point modes.  

### 3. Error Handling  

The program detects and handles errors such as:  
- Invalid expressions (missing operators, unrecognized characters, mismatched parentheses).  
- Division by zero.  
- Loss of precision in floating-point mode.  

### 4. Testing  

- Unit tests: test individual functions (parsing, evaluation).  
- Integration tests: test the full calculator with various inputs.  

### Artifact: app.exe  

The compiled project produces the executable app.exe, which can be run on any system with the required dependencies.  

### Dependencies:  
1. Make — for automated building.  
2. GCC — C compiler.  
3. Google Test — testing framework.  

### Build and Test Commands:  

Build the Project: 
make build

Run Unit Tests:
make run-tests

Run Integration Tests:  
make run-integration-tests
