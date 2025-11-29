#pragma once

#include <string>

class Calculator {
private:
    const double PI = 3.14159265358979323846;
    std::string expression;
    size_t pos;

    // Helper functions
    char peek();
    char get();
    void skipWhitespace();

    // Recursive parsing logic
    double parseFactor();
    double parsePower();
    double parseTerm();
    double parseExpression();

public:
    // Constructor
    Calculator(std::string input);

    // Main public method
    double solve();
};
