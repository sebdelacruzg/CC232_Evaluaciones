# Bitácora de Desarrollo - PC3
2026-06-07: 
- Estructuracion inicial de la PC3, ajuste de la estructura general y rutas de repositorio.

- Agregar el archivo CmakeLists.txt de la PC3
- Continuación del análisis del problema para la codificación de la solución.

2026-06-08:
- Lectura sobre la teoria de merge en Skew Heaps.
- Definicion de la estructura NodoSkewHeap y separacion de la API (skew_heap.h) de la implementacion (.cpp).
- Creacion del esqueleto de las funciones de reversion para armar la logica.
- Continuación del análisis del problema para el seguimiento de la codificación de la solución.

2026-06-09:
- Implementacion de la logica matematica para desarmar el Skew Heap en src/skew_heap.cpp.
- Se aplico el concepto de Un-Swap iterativo, subiendo por los punteros al padre (`tree[curr].P`) para mantener la complejidad asintotica amortizada.
- La extraccion ahora prioriza la "left spine" basandose firmemente en el invariante del merge.
- Integracion del modulo principal en src/main.cpp. Se implemento lectura rapida (Fast I/O) para manejar la carga de N nodos eficientemente y formatear la salida segun los estandares del problema.

2026-06-10:
- Pruebas unitarias con cassert en test_skew_heap.cpp.
- Validacion del invariante de la columna izquierda antes de aplicar el Un-Swap.
- Correccion en las aserciones de test_skew_heap.cpp: Se identifico y corrigio un error de interpretacion sobre la regla de insercion en arboles degenerados hacia la izquierda (left spine), basandome en el Sample 3 oficial.
- Refactorizacion de las pruebas unitarias para validar la secuencia completa de extraccion (minima y maxima) contra los 3 Samples del problema, asegurando el manejo correcto del caso "impossible".