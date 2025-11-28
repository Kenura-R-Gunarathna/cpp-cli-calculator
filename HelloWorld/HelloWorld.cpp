// HelloWorld.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

static bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int main()
{
    std::cout << "==================================\n";
    std::cout << "Hello World from simple calculator!\n";
    std::cout << "==================================\n";
    std::cout << "Type expressions like: 2 + 3\n";
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

        std::vector<double> numbers;
        std::vector<char> operators;

        std::string currentNumber = "";   // Build multi-digit numbers here
        size_t i = 0;

        while(i < input.length())
        {
            char c = input[i];
            
            if (std::isdigit(c) || c == '.')
            {
                currentNumber += c;
            }
            else if (isOperator(c))
            {
                if (!currentNumber.empty()) {
                    numbers.push_back(std::stod(currentNumber));
                    currentNumber = "";  // Reset for next number
                }

				operators.push_back(c);
            }
            else if (c == ' ')
            {
                i++;
                continue;
            }
            else
            {
                std::cout << "Warning: Unknown character '" << c << "'\n";
            }

            i++;
        }

		// Last number at end of input
        if (!currentNumber.empty()) {
            numbers.push_back(std::stod(currentNumber));
        }

        double result = numbers[0];

        // Loop through operators and apply them to the next number
        for (size_t opIdx = 0; opIdx < operators.size(); opIdx++)
        {
            // Safety check: ensure there is a number matching this operator
            // If we have 2 operators, we need 3 numbers.
            // numbers index: [0] [1] [2]
            // operators idx:   [0] [1]
            if (opIdx + 1 < numbers.size())
            {
                double nextNumber = numbers[opIdx + 1];
                char op = operators[opIdx];

                if (op == '+') {
                    result = result + nextNumber;
                }
                else if (op == '-') {
                    result = result - nextNumber;
                }
                else if (op == '*') {
                    result = result * nextNumber;
                }
                else if (op == '/') {
                    if (nextNumber == 0) {
                        std::cout << "Error: Cannot divide by zero.\n";
                        // Determine how to handle error? For now, just stop.
                        break;
                    }
                    result = result / nextNumber;
                }
            }
            else
            {
                std::cout << "Error: Operator '" << operators[opIdx] << "' is missing a number after it.\n";
            }
        }

        std::cout << "ans = " << result << '\n\n';
    }

    return 0;
}
