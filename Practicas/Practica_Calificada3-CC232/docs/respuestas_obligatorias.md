## Preguntas Comunes 
1. **¿Cuál es el problema exacto asignado?**
   Problema 8: ICPC World Finals 2025 - A-Skew-ed Reasoning. Trata sobre la reconstrucción inversa de secuencias de inserción válidas para un Skew Heap.
2. **¿Qué recibe la entrada y qué produce la salida?**
   Recibe un entero $N$ seguido de las conexiones (hijo izquierdo y derecho) de cada nodo del 1 al $N$. Produce las permutaciones lexicográficamente menor y mayor que pueden generar dicha estructura, o `"impossible"` si no es estructuralmente válida.
3. **¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**
   Un enfoque de fuerza bruta que genere las $N!$ permutaciones e intente construir el heap para cada una tiene una complejidad de $O(N! \cdot N \log N)$, lo cual es inviable para $N = 200,000$.
4. **¿Cuál sería la solución ingenua y cuál es su complejidad?**
   La fuerza bruta descrita arriba con complejidad factorial.
5. **¿Qué estructura de datos elegiste?**
   Un árbol binario auto-ajustable representado mediante vectores contiguos para acceso indexado $O(1)$ a los nodos.
6. **¿Qué estructura de la librería `cc232` se parece más?**
   Se relaciona directamente con la teoría de `BinaryHeap` y Heaps Mezclables de la Semana 6.
7. **¿Qué operación domina el tiempo?**
   La identificación y recorrido de la espina izquierda para la des-fusión de los nodos.
8. **¿Qué invariante mantiene tu estructura?**
   Que todo nodo que actúe como última raíz extraída debe haber pertenecido a la espina izquierda del árbol inmediatamente antes de su remoción.
9. **¿Dónde se actualiza ese invariante en el código?**
   Dentro de la función de búsqueda de candidatos y durante la aplicación del *un-swap* destructivo en `src/skew_heap.cpp`.
10. **¿Qué caso borde puede romper una solución superficial?**
    Un árbol donde un nodo padre posea un hijo derecho pero carezca de hijo izquierdo (estructuralmente imposible en un Skew Heap tras el swap final).
11. **¿Cómo manejas duplicados, empates o elementos obsoletos?**
    A través del ordenamiento lexicográfico estricto al almacenar las permutaciones extremas (mínima y máxima) deducidas.
12. **¿Cuál es la complejidad temporal por operación?**
    $O(\log N)$ amortizado por cada paso de des-fusión inversa.

## Preguntas Obligatorias  del Problema 8: Skew Heaps

1. **¿Qué diferencia hay entre skew heap, leftist heap y heap binario completo?**
   - **Heap Binario Completo:** Se implementa sobre un arreglo (vector). Su forma es rígida, ya que se llena estrictamente por niveles de izquierda a derecha.
   - **Leftist Heap:** Es un árbol con punteros. Guarda una variable extra de balanceo por nodo (el NPL o *null path length*) para decidir matemáticamente si debe intercambiar sus hijos.
   - **Skew Heap:** Es un árbol con punteros pero más simple. No guarda ninguna variable de balanceo. Su regla de oro es el "swap incondicional": siempre intercambia a sus hijos izquierdo y derecho después de fusionar.

2. **¿Cuál es la operación dominante en un heap mezclable?**
   La operación dominante es el Merge (fusión). En los heaps mezclables, todo se reduce a fusionar: 
   - Insertar un elemento es simplemente "fusionar el heap actual con un heap nuevo de un solo nodo".
   - Extraer el mínimo (pop) es "quitar la raíz y fusionar su hijo izquierdo con el derecho".

3. **¿Qué invariante se conserva durante merge?**
   El invariante clave es el intercambio (swap) incondicional de los hijos de cada nodo que se visita durante la fusión. Como el merge siempre avanza por la rama derecha para mantener el orden, hacer este swap inmediatamente después empuja todo el "peso" del árbol hacia la izquierda. Esto garantiza que la rama derecha se mantenga corta y que el costo de las operaciones se mantenga en $O(\log N)$ amortizado.