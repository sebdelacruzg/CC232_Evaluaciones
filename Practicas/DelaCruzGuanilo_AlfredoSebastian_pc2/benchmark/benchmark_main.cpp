#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include "Solution.h"

void measurePerformance(Solution& sol, const std::string& formula, const std::string& description) {
    std::cout << "Prueba: " << description << "\n";
    std::cout << "Longitud: " << formula.length() << " caracteres\n";

    // Tomar el tiempo justo antes de ejecutar
    auto start = std::chrono::high_resolution_clock::now();
    
    // Ejecutamos la funcion
    std::string result = sol.countOfAtoms(formula);
    
    // Tomar el tiempo justo despues
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calcular duracion en milisegundos con precision de decimales
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Tiempo: " << duration.count() << " ms\n";
    std::cout << "----------------------------------------\n";
}

int main() {
    Solution sol;
    
    std::cout << "--- BENCHMARK ---\n\n";

    // Formula Corta (Comportamiento Base)
    std::string formula_corta = "K4(ON(SO3)2)2";
    measurePerformance(sol, formula_corta, "Formula estandar anidada");

    // Formula Larga (O(N) sobre el tamaño del string
    std::string formula_larga = "";
    for(int i = 0; i < 500; i++) {
        formula_larga += "K4(ON(SO3)2)2"; 
    }
    measurePerformance(sol, formula_larga, "Formula de estres (x500 veces)");

    // Anidamiento Profundo (El peor caso para O(N^2))
    std::string formula_profunda = "H";
    for(int i = 0; i < 500; i++) {
        formula_profunda = "(" + formula_profunda + ")2";
    }
    measurePerformance(sol, formula_profunda, "Anidamiento extremo recursivo");

    std::cout << "Analisis: El Caso 2 es mas lento por la longitud del string.\n";
    std::cout << "El Caso 3 es eficiente porque solo procesa un atomo unico (H) por nivel.\n";
    
    return 0;
}