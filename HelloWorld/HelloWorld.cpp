// HelloWorld.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

// Function to determine the priority of operators
// Higher number means higher priority
int static getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to perform the math operation
double static applyOp(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return b == 0 ? 0 : a / b;
    case '^': return std::pow(a, b);
    case '%': return std::fmod(a, b);
    }
    return 0;
}

// Check if char is an operator or parenthesis
bool static isOperator(char c)
{
    // Corrected the logic to use OR (||) instead of commas
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == '(' || c == ')');
}

int main()
{
    std::cout << "==================================\n";
    std::cout << "Advanced Calculator (PEMDAS)\n";
    std::cout << "Supports: + - * / ^ % ( )\n";
    std::cout << "==================================\n";
    std::cout << "Type 'exit' to quit\n\n";

    std::string input;

    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            std::cout << "Goodbye!\n";
            break;
        }

        // We use two vectors to act as Stacks
        std::vector<double> values;
        std::vector<char> ops;

        bool errorFound = false;

        for (size_t i = 0; i < input.length(); i++)
        {
            if (input[i] == ' ') continue;

            // 1. If it's a number, parse the whole number
            if (std::isdigit(input[i]) || input[i] == '.') {
                std::string valStr;
                while (i < input.length() && (std::isdigit(input[i]) || input[i] == '.')) {
                    valStr += input[i];
                    i++;
                }
                values.push_back(std::stod(valStr));
                i--; // Step back because the loop increments i
            }
            // 2. If it's an opening bracket, push to ops stack
            else if (input[i] == '(') {
                ops.push_back('(');
            }
            // 3. If it's a closing bracket, solve entire brace
            else if (input[i] == ')') {
                while (!ops.empty() && ops.back() != '(')
                {
                    if (values.size() < 2) { errorFound = true; break; }

                    double val2 = values.back(); values.pop_back();
                    double val1 = values.back(); values.pop_back();
                    char op = ops.back(); ops.pop_back();

                    if (op == '/' && val2 == 0) {
                        std::cout << "Error: Division by zero\n";
                        errorFound = true;
                        break;
                    }

                    values.push_back(applyOp(val1, val2, op));
                }
                // Pop the opening '('
                if (!ops.empty()) ops.pop_back();
            }
            // 4. If it's an operator
            else if (isOperator(input[i])) {
                // While top of 'ops' has same or greater precedence to current operator, apply 'ops' to values
                while (!ops.empty() && ops.back() != '(' &&
                    getPrecedence(ops.back()) >= getPrecedence(input[i]))
                {
                    if (values.size() < 2) { errorFound = true; break; }

                    double val2 = values.back(); values.pop_back();
                    double val1 = values.back(); values.pop_back();
                    char op = ops.back(); ops.pop_back();

                    if (op == '/' && val2 == 0) {
                        std::cout << "Error: Division by zero\n";
                        errorFound = true;
                        break;
                    }

                    values.push_back(applyOp(val1, val2, op));
                }
                ops.push_back(input[i]);
            }
            else {
                std::cout << "Error: Invalid character '" << input[i] << "'\n";
                errorFound = true;
            }

            if (errorFound) break;
        }

        // Apply remaining operators in the stack
        while (!ops.empty() && !errorFound)
        {
            if (values.size() < 2) {
                // This happens if trailing operators exist (e.g. "2 +")
                errorFound = true;
                break;
            }

            double val2 = values.back(); values.pop_back();
            double val1 = values.back(); values.pop_back();
            char op = ops.back(); ops.pop_back();

            if (op == '/' && val2 == 0) {
                std::cout << "Error: Division by zero\n";
                errorFound = true;
                break;
            }

            values.push_back(applyOp(val1, val2, op));
        }

        if (!errorFound && !values.empty()) {
            std::cout << "ans = " << values.back() << "\n\n";
        }
        else if (!errorFound && values.empty()) {
            // Case were input was empty or just spaces
        }
        else {
            std::cout << "Calculation Error.\n\n";
        }
    }

    return 0;
}