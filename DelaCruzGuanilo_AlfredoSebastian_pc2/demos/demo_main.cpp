#include <iostream>
#include <string>
#include "Solution.h"

int main() {
    Solution sol;
    std::string input;

    std::cout << "--- Analizador de Formula Quimica ---\n";
    std::cout << "Ingrese la formula (o 'exit' para salir): ";
    
    while (std::cin >> input && input != "exit") {
        std::string result = sol.countOfAtoms(input);
        std::cout << "Resultado ordenado: " << result << "\n\n";
        std::cout << "Ingrese otra formula: ";
    }

    return 0;
}