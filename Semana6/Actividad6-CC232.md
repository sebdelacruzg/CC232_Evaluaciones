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

**1. ¿Por qué conviene expresar `parent`, `left`, `right` y pruebas de frontera como funciones pequeñas?**


**2. ¿Qué ventaja tiene `constexpr` frente a macros?**
`constexpr` crea funciones reales con tipo, alcance y comprobacion para errores en tiempo de compilacion mientras que los macros son simple texto reemplazado antes de compilar. `constexpr` es mas seguro, mas mantenible y ofrece el mismo rendimiento esperado que un macro
**3. ¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?**
**4. ¿Qué condición identifica una hoja en la representación implícita?**
**5. ¿Qué cambió en `percolateDown` después de usar las fuciones auxiliares?**



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








