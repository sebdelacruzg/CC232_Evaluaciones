# PC3 - CC232

#### Estudiante

- Nombre: Alfredo Sebastián De la Cruz Guanilo
- Código: 20242054J
- Problema asignado: 8. ICPC World Finals 2025 - A-Skew-ed Reasoning
- Enlace oficial: https://worldfinals.icpc.global/problems/2025/finals/problems/problemset.pdf

#### Referencia oficial

- CSV oficial:
  https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv

#### Relación con Semanas 4-6

- Semana principal: Semana 6
- Estructura usada: Skew Heap (Árbol binario auto-ajustable)
- Estructura de la librería `cc232` relacionada: BinaryHeap / Heaps Mezclables

#### Resumen de la solución

El problema requiere determinar las posibles secuencias de inserción originales que dieron lugar a una configuración final dada de un Skew Heap, o reportar si dicha estructura es imposible. Dado que un Skew Heap realiza un intercambio incondicional (*swap*) de los hijos izquierdo y derecho en cada operación de fusión (*merge*), la solución implementa un algoritmo inverso (*bottom-up*). El programa identifica los candidatos viables para haber sido la última raíz insertada recorriendo de forma inversa la "espina izquierda" (*left spine*) del árbol, aplicando un des-intercambio (*un-swap*) destructivo controlado para verificar la validez estructural y reconstruir las permutaciones de los elementos.

#### Invariante principal

- **Propiedad del Skew Heap Inverso:** En cada paso del proceso de reconstrucción, el nodo extraído como supuesta última raíz debe pertenecer estrictamente a la espina izquierda actual del subárbol analizado. Tras la extracción, la operación inversa del *un-swap* (intercambio de las ramas izquierda y derecha de los nodos en el camino de fusión) debe restaurar la propiedad estructural exacta del Skew Heap en el estado inmediatamente anterior a dicha inserción.

#### Complejidad

- Tiempo por operación: $O(\log N)$ amortizado para el proceso de des-fusión por nodo.
- Tiempo total: $O(N \log N)$ amortizado en el caso promedio para la reconstrucción completa de las secuencias.
- Espacio: $O(N)$ para almacenar la representación indexada del árbol y las permutaciones candidatas en vectores dinámicos.

#### Archivos relevantes

- [`src/`](./src/): Código fuente principal de la solución ([`main.cpp`](./src/main.cpp), [`skew_heap.cpp`](./src/skew_heap.cpp)).
- [`include/`](./include/): Cabecera y definición formal de la estructura ([`skew_heap.h`](./include/skew_heap.h)).
- [`tests/`](./tests/): Suite de pruebas unitarias automatizadas ([`test_skew_heap.cpp`](./tests/test_skew_heap.cpp)).
- [`demos/`](./demos/): Programa sandbox aislado para comprobar las trazas del merge ([`demo_merge_skew.cpp`](./demos/demo_merge_skew.cpp)).
- [`resultados/`](./resultados/): Evidencias de ejecución manual, salida de CTest y análisis de casos borde.
- [`docs/bitacora.md`](./docs/bitacora.md): Diario de desarrollo detallado por días de confirmación.
- [`docs/respuestas_obligatorias.md`](./docs/respuestas_obligatorias.md): Respuestas formales a las preguntas comunes y específicas.

#### Limpieza del repositorio

El repositorio no contiene carpetas `build/`, archivos `.exe`, binarios ni objetos gracias a una configuración estricta del archivo `.gitignore`. Puede verificarse ejecutando:

```bash
git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles|__pycache__)"
```
#### Compilación

El proyecto compila limpiamente mediante CMake desde una copia vacía:
```bash
cmake -S . -B build
cmake --build build
```

#### Ejecucion

Comando exacto para ejecutar el programa principal de forma manual:
```bash
./build/solucion_pc3
```
#### Pruebas

Para ejecutar las pruebas unitarias automatizadas, utiliza el siguiente comando:
```bash
ctest --test-dir build
```

Se validan las pruebas requeridas por la rúbrica reflejadas en resultados/casos_borde.txt y ejecutadas mediante CTest:

* Caso mínimo: Validación con $N=1$, procesando una raíz única sin hijos sin fallos de segmento.

* Caso frontera (Estructura vacía): Control de lectura con $N=0$ que finaliza el flujo de forma segura.Caso con imposibilidad estructural: Validación del Sample 2 oficial, detectando un árbol inválido (raíz con hijo derecho exclusivo) y retornando "impossible".

* Caso extremo pequeño: Validación interactiva y manual usando el Sample 1 oficial del ICPC.

* Prueba del invariante principal: Test unitario propio incorporado para asegurar que los candidatos de inserción provengan únicamente de la espina izquierda.

#### Evidencia Git

Al inicio del video obligatorio se ejecutarán los siguientes comandos en la raíz para validar el proceso real de desarrollo distribuido en 5 días diferentes:
```bash
git status
git log --date=short --pretty=format:"%ad - %h - %an - %s"
git log --date=short --pretty=format:"%ad" | sort | uniq -c
git log --graph --oneline --decorate --all
git log --date=short --name-status --pretty=format:"%ad - %h - %s" -- Semana4 Semana5 Semana6 Practicas practica-calificada3
git log --date=short --stat --pretty=format:"%ad - %h - %s"
```
#### Preguntas obligatorias

Todas las preguntas comunes y las específicas del problema de Skew Heap (Problema 8) se encuentran completamente respondidas en el archivo independiente [`docs/respuestas_obligatorias.md`](./docs/respuestas_obligatorias.md) y serán sustentadas de forma oral en el video.

#### Bitácora obligatoria

Resumen diario del flujo técnico disponible en el archivo [`docs/bitacora.md`](./docs/bitacora.md).

#### Respuestas obligatorias

Cuestionario completo y numerado disponible en el archivo [`docs/respuestas_obligatorias.md`](./docs/respuestas_obligatorias.md).
#### Declaración de autoría

Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación. También declaro que el repositorio entregado corresponde al trabajo mostrado en el video y que no contiene builds, ejecutables ni archivos generados usados para aparentar funcionamiento.