// HelloWorld.cpp

#include <iostream>
#include <string>
#include "Calculator.h"

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