// HelloWorld.cpp

#include <iostream>

static double add(double a, double b);
static double subtract(double a, double b);
static double multiply(double a, double b);
static double divide(double a, double b);

int main()
{
    std::cout << "-----------------------------------\n";
    std::cout << "Hello World from simple calculator!\n";
    std::cout << "-----------------------------------\n";

    double a = 0.0, b = 0.0;
    unsigned int operation = 0u;

    std::cout << "Enter the operation (0:add, 1:subtract, 2:multiply, 3:divide): ";
    if (!(std::cin >> operation)) {
        std::cout << "Invalid input for operation\n";
        return 1;
    }

    std::cout << "Enter first number: ";
    if (!(std::cin >> a)) {
        std::cout << "Invalid number\n";
        return 1;
    }

    std::cout << "Enter second number: ";
    if (!(std::cin >> b)) {
        std::cout << "Invalid number\n";
        return 1;
    }

    double result = 0.0;
    switch (operation)
    {
    case 0:
        result = add(a, b);
        break;
    case 1:
        result = subtract(a, b);
        break;
    case 2:
        result = multiply(a, b);
        break;
    case 3:
        if (b == 0.0) {
            std::cout << "Division by zero\n";
            return 1;
        }
        result = divide(a, b);
        break;
    default:
        std::cout << "Invalid operation\n";
        return 1;
    }

    std::cout << "Result: " << result << '\n';
    return 0;
}

static double add(double a, double b)
{
    return a + b;
}

static double subtract(double a, double b)
{
    return a - b;
}

static double multiply(double x, double y)
{
    return x * y;
}

static double divide(double a, double b)
{
    return a / b;
}