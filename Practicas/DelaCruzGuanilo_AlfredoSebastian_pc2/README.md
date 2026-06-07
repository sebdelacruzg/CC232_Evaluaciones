## PC2 - CC232

### Estudiante
- Nombre: Alfredo Sebastián De la Cruz Guanilo
- Código: 20242054J
- Problema asignado: LeetCode 726 - Number of Atoms
- Enlace: https://leetcode.com/problems/number-of-atoms/description/

### Referencia oficial
- Archivo de asignación: https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv

### Tema principal
- Semana: Semana 4
- Estructura o técnica principal: Stack (Pila), HashMap (Diccionario) y Parsing Sintáctico.

### Resumen de la solución
La solución analiza la fórmula química secuencialmente. Utiliza una pila de diccionarios (`std::stack<std::map<string, int>>`) para manejar los alcances definidos por los paréntesis. Al encontrar un `(`, se apila un nuevo mapa vacío. Al leer átomos y números, se registran en el mapa del tope de la pila. Al encontrar un `)`, se extrae el mapa superior, se multiplican sus valores por el subíndice contiguo (si existe) y se suman las frecuencias resultantes al nuevo mapa en el tope. 

### Complejidad
- Tiempo: $O(N^2)$ en el peor de los casos debido al anidamiento extremo donde se iteran y fusionan mapas múltiples veces, aunque para fórmulas regulares el comportamiento tiende a ser $O(N \log N)$ considerando la inserción en el árbol rojinegro subyacente de `std::map`.
- Espacio: $O(N)$ para almacenar la pila de contextos y la construcción del string resultante.

### Invariante o idea clave
Durante toda la ejecución, el mapa situado en el tope de la pila (`st.top()`) contiene las frecuencias consolidadas de los átomos que pertenecen estricta y únicamente al nivel de anidamiento de paréntesis que se está procesando en ese momento.

### Archivos Relevantes
- **Solución:** [`include/Solution.h`](./include/Solution.h) y [`src/Solution.cpp`](./src/Solution.cpp)
- **Tests:** [`tests/test_main.cpp`](./tests/test_main.cpp)
- **Benchmark:** [`benchmark/benchmark_main.cpp`](./benchmark/benchmark_main.cpp)
- **Demo:** [`demos/demo_main.cpp`](./demos/demo_main.cpp)

### Compilación
```bash
cmake -S . -B build
cmake --build build
```
### Ejecución
```bash
# 1. Pruebas Unitarias
./build/run_tests.exe

# 2. Análisis de Rendimiento
./build/run_benchmark.exe

# 3. Aplicación Interactiva
./build/run_demo.exe
```
### Casos de prueba
H2O: Evalúa el parsing base de átomos simples con y sin multiplicadores explícitos.

Mg(OH)2: Evalúa la creación de un contexto anidado simple y la correcta multiplicación al cerrar el paréntesis.

K4(ON(SO3)2)2: Evalúa múltiples contextos anidados y la propagación de multiplicadores en cascada hacia el mapa global.

### Historial de commits
El progreso del desarrollo y los commits realizados en días distintos se demostrarán durante el historial grabado en el video de sustentación.

### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.