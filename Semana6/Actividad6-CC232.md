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








