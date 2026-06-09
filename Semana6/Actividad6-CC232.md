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








