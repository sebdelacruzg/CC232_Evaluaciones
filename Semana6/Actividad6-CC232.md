## Actividad 6
### Bloque 1
1. 9 demos (como heapsort, huffman, treap y demas) y 2 pruebas de validación (`test_public` e `internal`).
2. La interfaz `PQ`, las implementaciones de heaps (`ComplHeap` y `LeftHeap`), `heapSort`, `Huffman` y `Treap`.
3. `Capitulo6.h` agrupa y expone el código real; `Capitulo10.h` es solo un alias de compatibilidad con la numeración del libro de Deng.
4. El `Treap` y las estructuras enlazadas, que reutilizan la base de `BinaryTree` y `BinarySearchTree` de la Semana 5.
5. `PQ_ComplHeap` (implícito) y `PQ_LeftHeap` (enlazado).
6. `BinarySearchTree`.
7. `Treap` (Clave = BST, Prioridad = Heap).
8. Éxito en el `ctest`, confirmando la validez y estabilidad de la lógica base antes de cualquier modificación.

### Bloque 2 

```cpp
inline constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) noexcept { return 2 * i + 1 < n; }
inline constexpr bool pqHasRightChild(std::size_t i, std::size_t n) noexcept { return 2 * i + 2 < n; }
inline constexpr bool pqIsLeaf(std::size_t i, std::size_t n) noexcept { return !pqHasLeftChild(i, n); }
inline constexpr bool pqIsInternal(std::size_t i, std::size_t n) noexcept { return pqHasLeftChild(i, n); }
```
```
template <class T, class Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  while (pqHasLeftChild(i, n)) { 
    std::size_t c = pqLeftChild(i);
    if (pqHasRightChild(i, n) && comp(a[c], a[pqRightChild(i)])) {
      c = pqRightChild(i);
    }
    if (!comp(a[i], a[c])) break;
    std::swap(a[i], a[c]);
    i = c;
  }
  return i;
}

```
1. Encapsulan las operaciones aritméticas de los índices (2i+1), previenen errores de escritura y vuelven el código autodescriptivo.

2. constexpr asegura la evaluación en tiempo de compilación y ofrece seguridad de tipos (type safety), superando las macros de C que hacen sustitución de texto descontrolada.

3. Se omite la comparación entre hermanos y se evalúa el intercambio directamente contra el único hijo izquierdo transitable.

4. Que la proyección matemática de su hijo izquierdo caiga fuera de los límites del arreglo (2i+1 >= n).

5. Se sustituyó pqInHeap por pqHasLeftChild y pqHasRightChild, mejorando la semántica.

Complejidad: La complejidad se mantiene intacta. El compilador aplica inline sobre estas funciones pequeñas, traduciéndolas al mismo código máquina (operaciones aritméticas y saltos condicionales) de la versión original.

### Bloque 3
```
template<class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp) {
  std::size_t swaps = 0;
  while (pqHasParent(i)) {
    const std::size_t p = pqParent(i);
    if (!comp(a[p], a[i])) break;
    std::swap(a[p], a[i]);
    i = p;
    swaps++;
  }
  return swaps;
}
```
Salida del demo creado:
```
insert(40) | swaps: 0 | heap: [40] | isHeap: true
insert(10) | swaps: 0 | heap: [40, 10] | isHeap: true
insert(70) | swaps: 1 | heap: [70, 10, 40] | isHeap: true
insert(30) | swaps: 1 | heap: [70, 30, 40, 10] | isHeap: true
insert(90) | swaps: 2 | heap: [90, 70, 40, 10, 30] | isHeap: true
insert(20) | swaps: 0 | heap: [90, 70, 40, 10, 30, 20] | isHeap: true
insert(80) | swaps: 1 | heap: [90, 70, 80, 10, 30, 20, 40] | isHeap: true
insert(60) | swaps: 1 | heap: [90, 70, 80, 60, 30, 20, 40, 10] | isHeap: true
```

1. Cuando el nodo insertado tiene una prioridad menor o igual que su padre inmediato, o al inicializar la raíz del heap.

2. Al insertar un elemento que se convierte en el nuevo máximo global y escala todos los niveles hasta la raíz.

3. La altura del heap es O(logn); el nivel donde se engancha la hoja limita físicamente la cantidad máxima de intercambios ascendentes.

4. Porque la propiedad de heap exige un ordenamiento jerárquico parcial de arriba a abajo, pero no define ninguna relación de orden horizontal entre hermanos del mismo nivel.

5. Se garantiza la forma de árbol binario completo y el orden de dominancia del elemento máximo ubicado en la raíz.

### Bloque 4
```cpp
template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  std::size_t swaps = 0;
  while (pqHasLeftChild(i, n)) {
    std::size_t c = pqLeftChild(i);
    if (pqHasRightChild(i, n) && comp(a[c], a[pqRightChild(i)])) {
      c = pqRightChild(i);
    }
    if (!comp(a[i], a[c])) break;
    std::swap(a[i], a[c]);
    i = c;
    swaps++;
  }
  return swaps;
}
```
Salida del demo creado:
```
delMax() -> 90
Antes de reparar: [10, 70, 80, 60, 30, 20, 40]
Swaps: 2
Despues de reparar: [80, 70, 40, 60, 30, 20, 10]

delMax() -> 80
Antes de reparar: [10, 70, 40, 60, 30, 20]
Swaps: 2
Despues de reparar: [70, 60, 40, 10, 30, 20]
```
Trazado manual de una eliminación extraccion de 90:
```
Se extrae 90 y se mueve el último elemento (10) a la raíz.
Estado temporal: [10, 70, 80, 60, 30, 20, 40].
10 compara con sus hijos 70 y 80. El mayor es 80. Se intercambian.
Nuevo estado: [80, 70, 10, 60, 30, 20, 40].
10 compara con sus nuevos hijos 20 y 40. El mayor es 40. Se intercambian.
Estado final: [80, 70, 40, 60, 30, 20, 10]. Nodos estables.
```

1. Para mantener la propiedad estructural de árbol binario completo, asegurando que el arreglo no tenga huecos.

2. Porque el nodo que se subió a la raíz proviene del nivel más profundo (baja prioridad) debe "hundirse" hasta recuperar su posición de dominancia.

3. SSe evalúan ambos hijos y se selecciona estrictamente al que tenga la mayor prioridad para subirlo, evitando violar la propiedad de heap entre hermanos.

4. Se omite la comparación entre hermanos y se evalúa el intercambio directamente contra el hijo izquierdo.

5. Porque el nodo desciende un nivel por cada intercambio y la altura de un árbol completo está matemáticamente acotada por O(log n).



### Bloque 5

```
template <class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, std::size_t i, Compare comp) {
    if (i >= a.size()) return true;
    std::size_t l = pqLeftChild(i);
    std::size_t r = pqRightChild(i);
    if (l < a.size() && comp(a[i], a[l])) return false;
    if (r < a.size() && comp(a[i], a[r])) return false;
    return complHeapIsValid(a, l, comp) && complHeapIsValid(a, r, comp);
}
```

1. Para todo nodo en el árbol, la prioridad del nodo es mayor o igual a la prioridad de sus hijos.

2. Por transitividad. Si A >= B y B >= C, entonces A >= C. Si cada padre cumple la regla con sus hijos inmediatos, toda la jerarquía está garantizada.

3. Por la transitividad explicada anteriormente, comparar exhaustivamente sería redundante y costoso (O(n^2)).

4. Costo O(n), ya que itera linealmente el arreglo una sola vez, realizando como máximo dos comparaciones por nodo.

5. Útil en pruebas para detectar bugs en modificaciones, pero inaceptable en producción porque validar el invariante cuesta O(n), arruinando el beneficio asintótico de las operaciones del heap que cuestan O(log n).
  


### Bloque 6 

```cpp 
std::vector<int> a = {4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89};
std::vector<int> by_insert;
std::size_t swaps_insert = 0;
for (int x : a) {
    by_insert.push_back(x);
    swaps_insert += ods::complHeapPercolateUpCount(by_insert, by_insert.size() - 1, std::less<int>{});
}

std::vector<int> by_floyd = a;
std::size_t swaps_floyd = 0;
for (std::size_t i = by_floyd.size() / 2; i-- > 0;) {
    swaps_floyd += ods::complHeapPercolateDownCount(by_floyd, by_floyd.size(), i, std::less<int>{});
}
```
| Estrategia | Arreglo Final Resultante | Intercambios Totales | isHeap | Complejidad |
| :--- | :--- | :--- | :--- | :--- |
| **A: Inserciones** | `[90, 55, 89, 34, 17, 21, 8, 4, 13, 2, 1, 3]` | 15 | True | O(n log n) |
| **B: Floyd** | `[90, 55, 89, 34, 17, 21, 8, 13, 4, 2, 1, 3]` | 8 | True | O(n) |

1. El heap representa un orden parcial jerárquico vertical, lo que permite múltiples disposiciones físicas válidas en arreglo para el mismo set de datos.
2. Cada elemento nuevo entra por el fondo (hoja) y puede trepar toda la altura del árbol, acumulando un costo alto en cada paso.
3. La mayoría de los nodos se concentran en los niveles inferiores (hojas) y bajan distancias mínimas o nulas, logrando que la sumatoria total sea lineal.
4. Comienza desde el último nodo interno con al menos un hijo (índice n/2 - 1) y avanza en reversa nivel por nivel hasta la raíz.
5. No tienen descendientes con quienes compararse ni intercambiar, por lo que cada hoja aislada ya es un sub-heap válido por defecto.

### Bloque 7

```cpp
template <class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
  if (a.size() < 2) return;
  if (ascending) {
    complHeapHeapifyFloyd(a, comp);
    for (std::size_t n = a.size(); n > 1; --n) {
      std::swap(a[0], a[n - 1]);
      complHeapPercolateDown(a, n - 1, 0, comp);
    }
  } else {
    auto inv = [&comp](const T& x, const T& y) { return comp(y, x); };
    complHeapHeapifyFloyd(a, inv);
    for (std::size_t n = a.size(); n > 1; --n) {
      std::swap(a[0], a[n - 1]);
      complHeapPercolateDown(a, n - 1, 0, inv);
    }
  }
}
```
1. Reutiliza las casillas finales que el heap libera para almacenar los máximos extraídos.

2. Extrae la raíz iterativamente y reduce el tamaño del heap para ordenar el arreglo.

3. Construir con Floyd cuesta O(n) y las n bajadas (percolateDown) cuestan O(n log n).

4. No. Los intercambios a larga distancia (raíz a hoja final) desordenan elementos idénticos.

5. Para usar solo O(1) memoria extra; crear otro vector gastaría O(n).


### Bloque 8 
```cpp
bool isValidLeftHeap(Node* u) const {
  if (!u) return true;
  if (u->left && comp_(u->value, u->left->value)) return false;
  if (u->right && comp_(u->value, u->right->value)) return false;
  if (npl(u->left) < npl(u->right)) return false;
  if (u->npl != npl(u->right) + 1) return false;
  return isValidLeftHeap(u->left) && isValidLeftHeap(u->right);
}
```
1. Se unifican la inserción y eliminación delegando todo el control y rebalanceo a la función central merge.

2. Encapsula el nuevo dato en un nodo unitario y lo fusiona con el árbol principal utilizando merge.

3. Elimina la raíz actual y aplica merge directamente entre los subárboles huérfanos izquierdo y derecho.

4. La distancia al nodo incompleto más cercano (NPL) del hijo izquierdo debe ser mayor o igual a la del derecho, sesgando la estructura a la izquierda.

5. Permite fusionar dos colas de prioridad completas en tiempo $O(\log n)$, superando el alto costo $O(n)$ de combinar arreglos enteros.

### Bloque 9 

| Símbolo | Frecuencia | Código | Longitud |
|---|---|---|---|
| A | 5  | 1100 | 4 |
| B | 5  | 1101 | 4 |
| C | 10 | 111  | 3 |
| D | 10 | 10   | 2 |
| E | 20 | 0    | 1 |

Libre de prefijos: true. Longitud ponderada: 110 bits.

El desempate está definido en `HuffmanLowerFrequencyFirst`:
```cpp
// Si frecuencias iguales, desempata por símbolo (mayor símbolo → menor prioridad)
return a->symbol > b->symbol;
```

Caso extremo: un solo símbolo `{X:100}`

```
X -> "0"
encode("XXX") = "000"
decode("000") -> "XXX"
prefijo libre = true
```

`huffmanCollectCodes` asigna `"0"` cuando `prefix` está vacío (árbol de un solo nodo hoja):
```cpp
out[u->symbol] = prefix.empty() ? "0" : prefix;
```

`huffmanDecode` para árbol de un solo nodo hoja: cada `'0'` en la cadena decodifica ese símbolo.

1. Extrae los nodos terminales de menor acumulación en tiempo sub-lineal impidiendo barridos O(n) continuos sobre la colección general.
2. Los fragmentos que cargan la estadística más baja (mayor prioridad) de representación global.
3. Un objeto compuesto que absorbe los flujos de sus elementos base sumando combinadamente sus registros de aparición.
4. Requiere validación directa (prefix.empty() ? "0" : prefix) ya que al no efectuarse fusiones la raíz simple no posee descensos estructurales de bits.
5. Anula la ambigüedad en la decodificación continua impidiendo que rutas numéricas de bits se traslapen a lo largo del árbol.
6. Altereación visual/lateral de elementos empatados generando variaciones asimétricas de códigos equivalentes sin corromper la funcionalidad.
7. Las matemáticas ponderadas se rigen por la distancia de descenso (nivel de profundidad), manteniéndose invariables ante traslaciones horizontales de empate.