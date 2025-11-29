// HelloWorld.cpp

#include <iostream>
#include <string>
#include <numeric>
#include "Calculator.h"
#include "HistoryManager.h"

// ==========================================
// COMMAND HANDLERS
// ==========================================

static void printHelp() {
    std::cout << "Scientific Calculator CLI v1.0\n";
    std::cout << "Usage:\n";
    std::cout << "  calc [command]\n\n";
    std::cout << "Available Commands:\n";
    std::cout << "  (no args)       Start the interactive mode (REPL)\n";
    std::cout << "  eval <math>     Evaluate a math expression and exit\n";
    std::cout << "  history         Show calculation history\n";
    std::cout << "  help            Show this help message\n\n";
    std::cout << "Examples:\n";
    std::cout << "  calc eval \"2 + 2\"\n";
    std::cout << "  calc eval sin(30, deg)\n";
}

static void runInteractive(HistoryManager& history) {
    std::cout << "==================================\n";
    std::cout << "Interactive Mode (REPL)\n";
    std::cout << "Type 'exit' to quit\n";
    std::cout << "==================================\n";

    std::string input;
    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") break;
        if (input == "history") {
            history.showHistory();
            continue;
        }
        if (input == "help") {
            printHelp();
            continue;
        }
        if (input.empty()) continue;

        Calculator calc(input);
        double result = calc.solve();

        std::cout << "ans = " << result << "\n\n";
        history.log(input, result);
    }
}

static void runEval(HistoryManager& history, int argc, char* argv[]) {
    // Combine all remaining arguments into one string
    // This allows: calc eval 2 + 2  (instead of strictly "2 + 2")
    std::string expression = "";
    for (int i = 2; i < argc; i++) {
        expression += argv[i];
        if (i < argc - 1) expression += " "; // Add space between args
    }

    if (expression.empty()) {
        std::cout << "Error: No expression provided.\n";
        std::cout << "Try: calc eval \"2 + 2\"\n";
        return;
    }

    Calculator calc(expression);
    double result = calc.solve();

    // Print JUST the result (useful for scripts)
    std::cout << result << "\n";

    history.log(expression, result);
}

// ==========================================
// MAIN ENTRY POINT
// ==========================================

int main(int argc, char* argv[])
{
    // Initialize Database
    HistoryManager history("calc_history.db");
    history.init();

    // 1. If no arguments provided, run Interactive Mode
    if (argc == 1) {
        runInteractive(history);
        return 0;
    }

    // 2. Parse the Command (argv[1])
    std::string command = argv[1];

    if (command == "history") {
        history.showHistory();
    }
    else if (command == "eval") {
        runEval(history, argc, argv);
    }
    else if (command == "help" || command == "--help" || command == "-h") {
        printHelp();
    }
    else {
        std::cout << "Unknown command: " << command << "\n";
        printHelp();
        return 1;
    }

    return 0;
}
