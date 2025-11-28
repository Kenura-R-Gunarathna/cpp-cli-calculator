// HelloWorld.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <algorithm> // For string tolower

// Define PI constant for conversions
const double PI = 3.14159265358979323846;

class Calculator {
private:
    std::string expression;
    size_t pos;

    char peek() {
        if (pos >= expression.length()) return 0;
        return expression[pos];
    }

    char get() {
        if (pos >= expression.length()) return 0;
        return expression[pos++];
    }

    void skipWhitespace() {
        while (pos < expression.length() && std::isspace(expression[pos])) {
            pos++;
        }
    }

    // ==========================================
    // RECURSIVE PARSING LOGIC
    // ==========================================

    double parseFactor() {
        skipWhitespace();
        char c = peek();

        // 1. Handle Functions (sin, cos, log, etc.)
        if (std::isalpha(c)) {
            std::string funcName;
            while (pos < expression.length() && std::isalpha(peek())) {
                funcName += get();
            }

            skipWhitespace();
            if (peek() != '(') {
                throw std::runtime_error("Function '" + funcName + "' missing '('");
            }
            get(); // Eat '('

            // Parse the first argument (the number)
            double arg1 = parseExpression();

            // Check for optional second argument (Comma detected)
            std::string mode = "rad"; // Default mode
            double arg2 = 0;          // For log base

            skipWhitespace();
            if (peek() == ',') {
                get(); // Eat comma
                skipWhitespace();

                // Check if the second arg is text (like "deg") or a number (like log base)
                if (std::isalpha(peek())) {
                    // It's text, likely "deg" or "rad"
                    std::string modeStr;
                    while (std::isalpha(peek())) {
                        modeStr += get();
                    }
                    if (modeStr == "deg") mode = "deg";
                }
                else {
                    // It's a number (useful for log base)
                    arg2 = parseExpression();
                    mode = "custom_base";
                }
            }

            skipWhitespace();
            if (peek() == ')') {
                get(); // Eat ')'
            }
            else {
                throw std::runtime_error("Missing closing bracket ')'");
            }

            // --- EXECUTE FUNCTIONS ---

            // Handle Trig (Convert if mode is 'deg')
            if (funcName == "sin" || funcName == "cos" || funcName == "tan") {
                if (mode == "deg") {
                    arg1 = arg1 * (PI / 180.0); // Convert Deg to Rad
                }

                if (funcName == "sin") return std::sin(arg1);
                if (funcName == "cos") return std::cos(arg1);
                if (funcName == "tan") return std::tan(arg1);
            }

            // Handle Logs
            if (funcName == "log") {
                // If user typed log(8, 2) -> arg1=8, arg2=2, mode="custom_base"
                if (mode == "custom_base") return std::log(arg1) / std::log(arg2);
                return std::log10(arg1); // Default base 10
            }
            if (funcName == "ln") return std::log(arg1);
            if (funcName == "sqrt") return std::sqrt(arg1);

            throw std::runtime_error("Unknown function: " + funcName);
        }

        // 2. Handle Parentheses
        if (c == '(') {
            get();
            double result = parseExpression();
            skipWhitespace();
            if (peek() == ')') get();
            else std::cout << "Warning: Missing ')'\n";
            return result;
        }

        // 3. Handle Negative numbers
        if (c == '-') {
            get();
            return -parseFactor();
        }

        // 4. Handle Numbers
        if (std::isdigit(c) || c == '.') {
            std::string numStr;
            while (pos < expression.length() && (std::isdigit(peek()) || peek() == '.')) {
                numStr += get();
            }
            return std::stod(numStr);
        }

        throw std::runtime_error("Unexpected character");
    }

    double parsePower() {
        double left = parseFactor();
        skipWhitespace();
        if (peek() == '^') {
            get();
            double right = parsePower();
            return std::pow(left, right);
        }
        return left;
    }

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
    Calculator(std::string input) {
        expression = input;
        pos = 0;
    }

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

int main()
{
    std::cout << "==================================\n";
    std::cout << "Scientific Calculator\n";
    std::cout << "==================================\n";
    std::cout << "Trig examples:\n";
    std::cout << "  sin(30, deg)   -> 0.5\n";
    std::cout << "  cos(3.14159)   -> -1 (Default rad)\n\n";
    std::cout << "Log examples:\n";
    std::cout << "  log(100)       -> 2  (Base 10)\n";
    std::cout << "  log(8, 2)      -> 3  (Base 2)\n";
    std::cout << "==================================\n\n";

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