#include <iostream>
#include <cassert>
#include <string>
#include "Solution.h"

int main() {
    Solution sol;

    std::cout << "Ejecutando pruebas de unidad (Unit Tests)...\n";

    // Caso 1: Formula simple
    assert(sol.countOfAtoms("H2O") == "H2O");
    std::cout << "[PASS] Caso H2O\n";

    // Caso 2: Paréntesis simple
    assert(sol.countOfAtoms("Mg(OH)2") == "H2MgO2");
    std::cout << "[PASS] Caso Mg(OH)2\n";

    // Caso 3: Paréntesis anidados
    assert(sol.countOfAtoms("K4(ON(SO3)2)2") == "K4N2O14S4");
    std::cout << "[PASS] Caso K4(ON(SO3)2)2\n";

    // Caso 4: Caso con números grandes (Borde)
    assert(sol.countOfAtoms("Be32(H2O)2") == "Be32H4O2");
    std::cout << "[PASS] Caso Be32(H2O)2\n";

    std::cout << "\nTodas las pruebas pasaron exitosamente.\n";

    return 0;
}