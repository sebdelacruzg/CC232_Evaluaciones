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

### Bloque 10
#### Parte A 

Secuencia `{(50,50),(30,30),(70,70),(20,20),(40,40),(60,60),(80,80)}`:

Observación clave: en esta implementación la prioridad menor sube a la raíz (min-heap por prioridad). Con prioridades clave=prioridad, el elemento 20 tiene la menor prioridad y sube a la raíz.

```
Salida final del árbol:
│                       ┌── 80|p=80
│                   ┌── 70|p=70
│               ┌── 60|p=60
│           ┌── 50|p=50
│       ┌── 40|p=40
│   ┌── 30|p=30
└── 20|p=20

inorder: [20,30,40,50,60,70,80]  ← siempre ordenado
```

Después de 5 inserciones:

| Insert(clave,prio) | inorder | lvlorder | raíz | isBST | isHeap | isTreap |
|---|---|---|---|---|---|---|
| (50,50) | [50] | [50] | 50 | true | true | true |
| (30,30) | [30,50] | [30,50] | 30 | true | true | true |
| (70,70) | [30,50,70] | [30,50,70] | 30 | true | true | true |
| (20,20) | [20,30,50,70] | [20,30,50,70] | 20 | true | true | true |
| (40,40) | [20,30,40,50,70] | [20,30,40,50,70] | 20 | true | true | true |


1. La propiedad BST (orden de claves) se preserva en toda rotación local. Las rotaciones solo mueven nodos pero conservan el recorrido inorden.


2. Porque la raíz debe tener la menor prioridad (en esta implementación). Cuando se inserta un nodo con prioridad menor a la raíz actual, `bubbleUp` lo sube mediante rotaciones hasta desplazarlo a la raíz.


3. El nodo recién insertado. `bubbleUp` rota con su padre mientras el padre tenga prioridad mayor que el nodo actual.

4. El orden inorden (BST). Una rotación local solo cambia quién es padre de quién entre dos nodos adyacentes, sin alterar la relación de orden entre claves menores, el nodo, y claves mayores.

5. La propiedad de min-heap por prioridad: todo padre debe tener prioridad menor o igual a sus hijos.

#### Parte B 

```cpp
std::size_t bubbleUpCount(Node* u) {
  std::size_t rots = 0;
  while (u->parent && u->parent->priority > u->priority) {
    if (u->isRightChild()) rotateLeft(u->parent);
    else rotateRight(u->parent);
    ++rots;
  }
  if (!u->parent) root_ = u;
  return rots;
}
```

Secuencia `{(100,100),(90,90),(80,80),(70,70),(60,60)}`:

| Clave | Prio | Rotaciones | Raíz |
|---|---|---|---|
| 100 | 100 | 0 | 100 |
| 90  | 90  | 1 | 90  |
| 80  | 80  | 1 | 80  |
| 70  | 70  | 1 | 70  |
| 60  | 60  | 1 | 60  |


1. Cada elemento nuevo tiene prioridad menor que todos los anteriores (prioridad = clave, decrece). Al insertarse, siempre viola la propiedad heap respecto a su padre, así que sube exactamente una rotación hasta quedar en la raíz.

2. Cuando el nodo insertado tiene prioridad mayor o igual que su padre inmediato, es decir, ya está en posición correcta en el árbol desde su posición de hoja. No es necesaria ninguna rotación.

3. `O(log n)` esperado, porque la altura esperada del treap con prioridades aleatorias es `O(log n)`. El peor caso absoluto es la altura del árbol en ese momento, que en el peor caso degenerado puede ser `O(n)`, aunque con prioridades aleatorias ocurre con probabilidad negligible.

4. Una rotación local entre un nodo `u` y su padre `w` mueve `u` hacia arriba sin cambiar el orden inorden. El subárbol central (hijo derecho de `u` en rotación derecha, o hijo izquierdo en rotación izquierda) se reasigna al otro lado de forma que el inorden se preserve exactamente.

5. Porque las prioridades son aleatorias (o pseudoaleatorias). La estructura del árbol depende de la permutación aleatoria inducida por las prioridades, y se puede demostrar que la altura esperada es `O(log n)` para prioridades uniformes independientes. No hay garantía en el peor caso como en AVL o rojo-negro.

#### Parte C 

Eliminaciones sobre el treap de Parte A (`{50,30,70,20,40,60,80}` con prio=clave):

| Eliminar | Rotaciones | inorden | isBST | isTreap |
|---|---|---|---|---|
| 50 | 1 | [20,30,40,60,70,80] | true | true |
| 20 | 1 | [30,40,60,70,80] | true | true |
| 70 | 1 | [30,40,60,80] | true | true |

**Trazado de `remove(50)` con prioridad 50:**

Estado previo (simplificado): `20` es raíz, sus hijos son `30` y la rama izquierda. `50` tiene hijos `40` y `60`.

`trickleDown(nodo(50))`:
- Hijos: izq=40 (prio 40), der=60 (prio 60). Menor prioridad es 40 (izq).
- `izq->priority < der->priority` → `rotateRight(u)` → 40 sube, 50 baja a derecha de 40.
- Ahora nodo(50) tiene solo hijo derecho: 60.
- Solo hijo derecho → `rotateLeft(u)` → 60 sube, 50 queda como hoja.
- 50 no tiene hijos. `trickleDown` termina. Total: 1 rotación.

`splice(nodo(50))`: nodo sin hijos, simplemente se desconecta del árbol.


1. Porque en un BST común se puede reemplazar el nodo eliminado por su sucesor o predecesor inorden. En un treap, ese reemplazo podría violar la propiedad de heap por prioridad. `trickleDown` baja el nodo hasta convertirlo en hoja, preservando ambas propiedades en todo momento.

2. Para que ese hijo de menor prioridad suba a la posición del nodo actual. Si se rotara con el de mayor prioridad, ese hijo violaría la propiedad heap respecto a su nuevo padre (que tiene prioridad mayor).

3. Se aplica `rotateRight(u)`: el hijo izquierdo sube y `u` queda como hijo derecho de su antiguo hijo.

4. Se aplica `rotateLeft(u)`: el hijo derecho sube y `u` queda como hijo izquierdo.

5. La propiedad BST (los punteros padre/hijo restantes mantienen el orden inorden) y la propiedad heap por prioridad (el nodo eliminado era una hoja, así que sus vecinos no cambian su relación de prioridad). También `size_` debe decrementarse en 1 y los punteros `parent` deben actualizarse correctamente.


#### Parte D 

| Operación | Resultado Treap | Resultado BST | Propiedad usada |
|---|---|---|---|
| `findEQ(40)` | 40 | 40 | BST |
| `findEQ(35)` | null | null | BST |
| `lowerBound(35)` | 40 | 40 | BST |
| `lowerBound(40)` | 40 | 40 | BST |
| `upperBound(40)` | 50 | 50 | BST |
| `upperBound(75)` | 80 | 80 | BST |
1. Porque buscan la clave más pequeña que sea ≥ x (o > x). Solo la propiedad BST garantiza que al ir a la izquierda las claves son menores y a la derecha son mayores, permitiendo la búsqueda binaria.

2. La estructura de búsqueda por clave: `findEQ`, `findLast`, `lowerBound`, `upperBound`, `inorderKeys`.

3. La estructura de prioridades: la raíz tiene la menor prioridad (en esta implementación), y cada padre tiene prioridad menor o igual a sus hijos.

4. Porque para extraer el máximo (o mínimo) de prioridad en un treap habría que recorrer el árbol hasta la hoja de menor prioridad (que no es la raíz). En contraste, un heap binario da `getMax` en `O(1)`. El treap no está optimizado para extracción repetida de prioridades.

5. Cuando se necesitan simultáneamente búsqueda ordenada por clave (`lowerBound`, `upperBound`, rango) y balance probabilístico sin el overhead de AVL o rojo-negro. Es útil en implementaciones de conjuntos ordenados con operaciones mixtas de inserción, eliminación y búsqueda.


#### Parte E 

Pruebas agregadas en `test_public_week6.cpp` y `test_internal_week6.cpp`:

| Prueba | Cubre | Bug que atraparía |
|---|---|---|
| PI-3 | `isBST()` tras insertar | Inserción que viola orden de claves |
| PI-4 | `isHeapByPriority()` tras insertar | `bubbleUp` incompleto |
| PI-5 | `isTreap()` tras eliminar | `trickleDown` / `splice` con punteros incorrectos |
| PI-7 | Treap vacío: `empty()`, `isTreap()` | Inicialización incorrecta de `root_` |
| PI-8 | Duplicados rechazados | `addNode` que no verifica igualdad |
| PI-9 | Inorden ordenado tras insertar | Rotación que rompe BST |
| PI-10 | Eliminación de raíz preserva treap | `trickleDown` que no actualiza `root_` |
| PI-11 | `size()` consistente tras operaciones mixtas | Contador no decrementado en `splice` |

### Bloque 11

```
BinaryHeap::top()     = 1   (min-heap: menor elemento)
PQ_ComplHeap::getMax()= 14  (max-heap: mayor elemento)
BST inorder           = 1 3 4 6 7 8 10 13 14
Treap inorder         = 1 3 4 6 7 8 10 13 14
Treap isTreap()       = true
```

Tabla de comparación

| Estructura | Op principal | Propiedad mantenida | Operación eficiente | Op que no conviene | Evidencia |
|---|---|---|---|---|---|
| `BinaryHeap` (S5) | `add` / `remove` | Heap min implícito (arreglo) | `top()` O(1), `add` O(log n) | `lowerBound`, inorden | `top()=1` |
| `PQ_ComplHeap` (S6) | `insert` / `delMax` | Heap max implícito (arreglo) | `getMax()` O(1), `delMax` O(log n) | `lowerBound`, inorden | `getMax()=14` |
| `BinarySearchTree` (S5) | `add` / `remove` | BST (inorden ordenado) | `lowerBound` O(h), inorden O(n) | Extraer max repetido | inorden=1..14 |
| `Treap` (S6) | `add` / `remove` | BST + heap por prioridad | `lowerBound` E[O(log n)], `isTreap` | No es PQ pura | `isTreap=true` |


1. Un heap responde eficientemente a "dame el elemento de mayor/menor prioridad" pero no permite búsqueda por clave arbitraria ni recorrido ordenado. Un BST permite búsqueda, `lowerBound`, `upperBound` y recorrido inorden ordenado, pero no garantiza extracción del máximo en O(1).

2. En un BST el recorrido inorden visita claves en orden creciente por construcción. En un heap, los hermanos no tienen relación de orden entre sí; solo se garantiza la relación padre-hijo.

3. `PQ_ComplHeap` implementa la interfaz abstracta `PQ<T>`, usa `std::less` por defecto como max-heap, expone `isHeap()` y `complHeapIsValid`, y tiene funciones auxiliares `constexpr` limpias en lugar de macros. `BinaryHeap` de Semana 5 es un min-heap por defecto sin interfaz abstracta.

4. La propiedad BST sobre claves (para búsqueda ordenada) y la propiedad de heap sobre prioridades (para balanceo probabilístico). Las prioridades aleatorias inducen una distribución uniforme de formas del árbol, garantizando altura esperada `O(log n)`.

5. `PQ_ComplHeap` o `PQ_LeftHeap`. `getMax()` en O(1) y `delMax()` en O(log n).

6. `BinarySearchTree` o `Treap`. Ambos tienen `lowerBound` en O(altura).

7. `Treap`. Combina búsqueda ordenada como BST con altura esperada O(log n) gracias a prioridades aleatorias, sin el overhead de mantener factores de balance explícitos como AVL.

### Bloque 12 

*En `test_public_week6.cpp`:

| ID | Prueba | Bug que atraparía |
|---|---|---|
| P1 | `isHeap()` después de cada inserción | `percolateUp` que no restaura heap |
| P2 | `isHeap()` después de cada eliminación | `percolateDown` incompleto |
| P3 | `getMax()` no cambia el tamaño | `getMax` que elimina accidentalmente |
| P4 | `delMax()` decrementa el tamaño en 1 | `pop_back` olvidado |
| P5 | `heapifyFloyd` produce heap válido | Floyd que procesa nodos en orden incorrecto |
| P6 | `heapSort` ordena con repetidos | Inestabilidad que pierde elementos repetidos |
| P7 | `PQ_LeftHeap` isLeftistHeap después de `merge` | `mergeNodes` que no actualiza `npl` |
| P8 | `PQ_LeftHeap` isLeftistHeap después de `insert` | Inserción como `merge` con nodo mal inicializado |
| P9 | `PQ_LeftHeap` isLeftistHeap después de `delMax` | `delMax` que no hace `merge` de subárboles |
| P10 | Huffman: códigos para todos los símbolos con freq>0 | `huffmanMakeForest` que filtra incorrectamente |
| P11 | Huffman: prefijo libre | Árbol construido sin respetar frecuencias |
| P12 | Huffman: un solo símbolo tiene código válido | `huffmanCollectCodes` sin caso `prefix.empty()` |
| P13 | Treap: `isBST()` después de insertar | Rotación que rompe orden de claves |
| P14 | Treap: `isHeapByPriority()` después de insertar | `bubbleUp` incompleto |
| P15 | Treap: `isTreap()` después de eliminar | `trickleDown` + `splice` con punteros incorrectos |

En `test_internal_week6.cpp` (adicionales):

| ID | Prueba | Bug que atraparía |
|---|---|---|
| PI-1 | `percolateUpCount` retorna >0 para elemento máximo | Implementación que no cuenta intercambios |
| PI-1b | `percolateUpCount` retorna 0 para elemento mínimo | Count que cuenta sin hacer swap |
| PI-2 | `percolateDownCount` retorna >0 para raíz mínima | Versión count que no instrumenta correctamente |
| PI-3 | Heap vacío es válido | `isHeap()` que falla con tamaño 0 |
| PI-4 | Heap de un elemento | `getMax` que accede fuera de rango |
| PI-5 | Heap con todos iguales | Comparador estricto que rechaza iguales |
| PI-6 | `heapSort` descendente | Inversión de comparador incorrecta |
| PI-7 | Treap vacío pasa todas las validaciones | Constructor que no inicializa `root_` a null |
| PI-8 | Treap rechaza duplicados y mantiene `size` | `addNode` que no verifica igualdad |
| PI-9 | Inorden ordenado tras insertar en Treap | Rotación que rompe BST |
| PI-10 | Eliminación de raíz preserva `isTreap` | `trickleDown` que no actualiza `root_` correctamente |
| PI-11 | `size()` consistente tras operaciones mixtas | `size_` no decrementado en `splice` |
| PI-12 | Huffman 1 símbolo: encode/decode round-trip | `huffmanDecode` sin manejo de árbol hoja |
| PI-13 | `bubbleUpCount` devuelve 0 cuando no hay rotaciones | Contador que siempre incrementa |

Resultado de `ctest`

```
Test project /home/claude/Libreria_cc232/Semana6/build-debug
    Start 1: semana6_public
1/2 Test #1: semana6_public ...................   Passed    0.00 sec
    Start 2: semana6_internal
2/2 Test #2: semana6_internal .................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```
### Bloque 13 
* Abstracción (`PQ`): Separar la interfaz lógica de la memoria física permite intercambiar estructuras (arreglos vs. punteros) sin alterar los algoritmos que las usan.
* Gestión de Heaps: El heap implícito optimiza el uso de caché, pero es rígido al fusionar. El heap izquierdista soluciona esto usando nodos enlazados, logrando fusiones (`merge`) eficientes en O(log n).
* Eficiencia Algorítmica: El método de Floyd (`heapify`) reduce el costo de construir un heap desde cero de O(n log n) a O(n) operando de abajo hacia arriba. Esta optimización es la base del `heapSort` para ordenar in-situ usando memoria O(1).
* Aplicaciones Prácticas:
    * Huffman: Requiere colas de prioridad precisas para extraer subárboles mínimos y construir códigos óptimos sin ambigüedad.
    * Treap: Hibridación perfecta. Mantiene el orden de búsqueda (BST) y usa prioridades aleatorias (Heap) para auto-balancear el árbol en O(log n) mediante rotaciones locales.
* Validación: Las pruebas unitarias de invariantes no son un extra; son la única demostración matemática de que las optimizaciones en memoria no han corrompido la estructura de datos.
