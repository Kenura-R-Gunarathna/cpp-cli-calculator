// HelloWorld.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <stdexcept>

// ==========================================
// THE CALCULATOR CLASS
// ==========================================
class Calculator {
private:
    std::string expression; // The math string (e.g., "2+2")
    size_t pos;             // Current index we are reading at

    // Helper: Look at the current character without moving
    char peek() {
        if (pos >= expression.length()) return 0; // Null char if end
        return expression[pos];
    }

    // Helper: Get current character and move to next
    char get() {
        if (pos >= expression.length()) return 0;
        return expression[pos++];
    }

    // Helper: Skip spaces
    void skipWhitespace() {
        while (pos < expression.length() && std::isspace(expression[pos])) {
            pos++;
        }
    }

    // ==========================================
    // RECURSIVE PARSING LOGIC
    // Hierarchy: Expression -> Term -> Power -> Factor
    // ==========================================

    // Level 4: Factor (Numbers and Parentheses)
    // This is where the recursion magic happens!
    double parseFactor() {
        skipWhitespace();
        char c = peek();

        // 1. Handle Parentheses (Recursion)
        if (c == '(') {
            get(); // Eat '('

            // CALL ITSELF: Calculate what is inside the brackets
            double result = parseExpression();

            skipWhitespace();
            if (peek() == ')') {
                get(); // Eat ')'
            }
            else {
                std::cout << "Warning: Missing closing bracket ')'\n";
            }
            return result;
        }

        // 2. Handle Negative numbers (Unary minus)
        if (c == '-') {
            get();
            return -parseFactor();
        }

        // 3. Handle actual numbers
        if (std::isdigit(c) || c == '.') {
            std::string numStr;
            while (pos < expression.length() && (std::isdigit(peek()) || peek() == '.')) {
                numStr += get();
            }
            return std::stod(numStr);
        }

        return 0; // Default error value
    }

    // Level 3: Powers (^)
    double parsePower() {
        double left = parseFactor();
        skipWhitespace();

        if (peek() == '^') {
            get(); // Eat '^'
            double right = parsePower(); // Recursion allows 2^3^4
            return std::pow(left, right);
        }
        return left;
    }

    // Level 2: Terms (*, /, %)
    double parseTerm() {
        double left = parsePower();
        skipWhitespace();

        while (peek() == '*' || peek() == '/' || peek() == '%') {
            char op = get();
            double right = parsePower();

            if (op == '*') left = left * right;
            else if (op == '/') {
                if (right == 0) throw std::runtime_error("Division by zero");
                left = left / right;
            }
            else if (op == '%') left = std::fmod(left, right);
        }
        return left;
    }

    // Level 1: Expressions (+, -)
    // This is the entry point logic
    double parseExpression() {
        double left = parseTerm();
        skipWhitespace();

        while (peek() == '+' || peek() == '-') {
            char op = get();
            double right = parseTerm();

            if (op == '+') left = left + right;
            else if (op == '-') left = left - right;
        }
        return left;
    }

public:
    // Constructor: Sets up the calculator with a new string
    Calculator(std::string input) {
        expression = input;
        pos = 0;
    }

    // The public function that starts the math
    double solve() {
        try {
            return parseExpression();
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            return 0;
        }
    }
};

// ==========================================
// MAIN PROGRAM
// ==========================================
int main()
{
    std::cout << "==================================\n";
    std::cout << "Class-Based Recursive Calculator\n";
    std::cout << "==================================\n";

    std::string input;

    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") break;
        if (input.empty()) continue;

        Calculator calc(input);

        double result = calc.solve();

        std::cout << "ans = " << result << "\n\n";
    }

    return 0;
}