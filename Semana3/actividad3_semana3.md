## Actividad 3-CC232

### Estudiante
- Nombre: Alfredo Sebastián De la Cruz Guanilo

#### Bloque 1
1. Se pasa de bloques adyacentes en RAM a nodos dispersos unidos lógicamente por punteros.
2. Acceso por rango busca el índice $i$ (lento en listas). Acceso por posición opera desde un puntero ya conocido (rápido en listas).
3. Al ubicar el nodo, insertar/borrar es $O(1)$ reasignando punteros. Pero hallar el índice $i$ exige iterar, costando $O(i)$.
4. Mantener punteros a `head` y `tail` permite apilar, encolar y desencolar en $O(1)$.
5. Falla en `removeLast()` porque sin puntero `prev`, hallar el penúltimo nodo cuesta $O(n)$.
6. Circulariza la lista y elimina casos borde (ej. lista vacía), asegurando que siempre existan `prev` y `next` válidos.
7.  Evalúa si $i < n/2$ para iterar desde el inicio (`dummy.next`) o desde el final (`dummy.prev`), recorriendo máximo la mitad.
8. Agrupa datos en bloques (BDeque) para reducir la cantidad de punteros, bajando el desperdicio a $O(\sqrt{n})$.
9.  Se requieren desplazamientos rápidos ($O(1)$ amortizado) en ambos extremos de cada bloque para las redistribuciones (`spread`/`gather`).
10. Añade una capa de algoritmos de alto nivel (`sort`, `dedup`). No reemplaza a Morin porque las estructuras base deben mantenerse ligeras.

#### Bloque 2
| Archivo | Observable | Idea estructural | Argumento |
| :--- | :--- | :--- | :--- |
| `sllist` | `pop` y `remove` rápidos | Nodos con enlace simple | $O(1)$ en extremos (LIFO/FIFO) |
| `dllist` | Inserción intermedia fácil | Enlace doble + `dummy` | $O(1)$ en actualización local |
| `selist` | Impresión continua | Bloques anidados | Reduce sobrecarga de punteros |
| `deng_list` | `sort()` integrado | ADT algorítmico rico | Foco en manipulación avanzada |
| `bridge` | Uso de `dedup` en `DLList` | Patrón Adapter/Bridge | Reutilización de algoritmos |
| `min_*` | Rastreo del mínimo | Estado extendido | $O(1)$ al recuperar el mínimo |
| `linked_ad`| `push`, `addFirst` | Encapsulamiento (Wrapper) | Reutiliza `SLList`/`DLList` |
| `cont_vs_l`| Acceso vs inserción | Arreglo vs Nodos | Localidad caché vs $O(1)$ local |

1. Llamar a `push` y `pop` (pila), seguido de `add` y `remove` (cola) sobre la misma instancia.
2. `d.add(1, 30)` demuestra inserción en el centro actualizando enlaces locales.
3. El bucle de impresión muestra la secuencia lógica ignorando la fragmentación en bloques.
4. Llamadas directas a transformaciones complejas como `lista.sort()`.
5. Uso de `stable_sort_with_deng` sobre una `DLList` sin modificar la clase original.
6. Almacenar pares `{valor, minimo}` gasta más memoria pero logra consultas $O(1)$.
7. `LinkedDeque`, porque mapea su API directamente a los extremos de una `DLList` existente.
8. El arreglo dinámico domina en lectura por índice (caché), la lista domina en inserciones sin desplazar elementos.

#### Bloque 3
1. Valida inserción, extracción en extremos y tamaño (`add`, `push`, `pop`, `remove`).
2.  Valida inserción central `add(i,x)`, lectura `get(i)` y borrado central `remove(i)`.
3. Valida creación de bloques `add(i,x)`, lectura y manipulación de tamaño.
4.  Operaciones auxiliares como `reverse()`, `rotate()`, palindromía y chequeo de invariantes.
5. Garantiza que se respete estrictamente la semántica LIFO, FIFO y de doble extremo.
6. Confirma que la conversión bidireccional entre estructuras no corrompe los datos.
7. Estresa las funciones `spread/gather` con bajo/sobre flujo de bloques.
8. Correctitud funcional básica en casos comunes.
9. Complejidad asintótica, fugas de memoria o estabilidad en casos masivos.
10. Pasar un test es empírico; el invariante garantiza matemáticamente que la lógica no fallará en ningún estado.

#### Bloque 4
1. `head` (entrada/salida rápida), `tail` (entrada rápida al final), `n` (conteo lógico $O(1)$).
2. `push`/`pop` alteran `head` y el `next` del nodo. `add` altera `tail`.
3. `secondLast` itera desde `head` buscando `u->next == tail`. Imposible en $O(1)$ sin puntero `prev`.
4. `reverse` invierte los punteros `next` in-place usando 3 punteros temporales.
5. `checkSize()` previene corrupción al verificar que recorrer los punteros coincida con la variable `n`.
6. Porque compara $i$ con $n/2$, reduciendo a la mitad el recorrido en el peor caso.
7. Modifica 4 punteros (del nuevo, del previo y del original). El `dummy` evita validaciones de `if (head == null)`.
8. `rotate` solo reconecta el `dummy` con los nuevos extremos y vincula los antiguos. No mueve datos.
9. Usa dos punteros que avanzan en direcciones opuestas hacia el centro.
10. `Location` indica físicamente el nodo (`BDeque`) y el offset (`j`) del elemento.
11. `spread()` redistribuye hacia adelante si hay overflow. `gather()` compacta hacia atrás si hay underflow.
12. Un $b$ grande acerca la SEList a un Arreglo. Un $b$ pequeño la acerca a una DLList.

#### Bloque 5
1. Envuelve a `SLList`, limitando la API a operar solo en `head` (`push`, `pop`, `top`).
2. Encola en `tail` (`add`) y desencola en `head` (`remove`).
3. Un `Deque` exige `removeLast()` en $O(1)$, algo posible en `DLList` (vía `prev`) pero imposible en `SLList`.
4. El caching del mínimo permite `min()` en $O(1)$ al retroceder en la pila (pop).
5. Se encola en `in_` y se desencola de `out_`. El mínimo es simplemente comparar el top de ambas.
6. Evita el vaciamiento de una pila. Si una queda vacía, `rebalance()` redistribuye mitad y mitad en $O(1)$ amortizado.
7. "Implementar" es gestionar memoria y punteros (ej. `DLList`). "Adaptar" es restringir una interfaz usando una estructura ya hecha (ej. `LinkedStack`).
8. Constantes: `push`/`pop`. Amortizadas: Las consultas en `MinDeque` (por posibles llamadas a `rebalance()`).

#### Bloque 6
1. Búsqueda secuencial, ordenamiento (`sort`), deduplicación y reverso.
2. Principio de Responsabilidad Única: Morin queda rápido y ligero; Deng añade poder algorítmico solo si se requiere.
3. `to_deng` copia datos a un vector y los inyecta en `DengList`. `assign_from_deng` hace lo inverso.
4. Exporta temporalmente los datos a `DengList`, usa su método y los importa de vuelta.
5. Elimina exhaustivamente elementos repetidos no adyacentes ($O(n^2)$), a diferencia de `uniquify()`.
6. Permite que `DLList` y `SEList` compartan la misma lógica de inversión mediante un puente estándar (vector).
7. Costo espacial $O(n)$ temporal. Vale la pena cuando la ganancia algorítmica y la limpieza del código lo justifican.

#### Bloque 7
1. `ArrayDeque` usa un buffer circular ($O(n)$ en corrimientos). `LinkedDeque` usa punteros dobles ($O(1)$ en extremos).
2. Los datos físicos en RAM están juntos, por lo que el hardware carga bloques contiguos rápidamente en la Caché.
3. Actualizaciones locales (inserción/borrado) donde el puntero ya está ubicado.
4. Acceso aleatorio: `random_get_arraydeque` vs `dllist`. Operaciones extremas: `deque_contiguo` vs `enlazado`.
5. Está atado a la arquitectura de hardware (caché L1) y obvia los costos asintóticos a escalas teóricas mayores.
6. Simula doble enlace usando un solo puntero de memoria gracias a la operación XOR bit a bit.
7. Impide recolectores de basura, es más lento de calcular y no permite instanciar iteradores desde la mitad de la lista.

#### Bloque 8
Pasar de arreglos a nodos implica cambiar la representación contigua por una red de punteros distribuidos. El acceso por rango se vuelve costoso ($O(n)$), pero el acceso por posición es inmediato, permitiendo inserciones y eliminaciones locales en tiempo constante ($O(1)$) al evitar desplazamientos de memoria. En cuanto a complejidad, la SLList domina operaciones en extremos, la DLList reduce el recorrido a $O(\min(i, n-i))$ y la SEList equilibra el espacio mediante bloques. Esta arquitectura facilita la reutilización mediante adaptadores (Wrappers) que imitan Pilas o Colas sin duplicar lógica. En conclusión: lo contiguo prioriza la velocidad de la caché y el cálculo matemático, mientras lo enlazado prioriza la flexibilidad y la edición local eficiente.

#### Autoevaluación breve
- La diferencia teórica entre acceso por índice vs. acceso por enlace, y cómo el nodo centinela simplifica la DLList.
- La matemática exacta detrás del rebalanceo fraccionario dentro del `spread` y `gather` de la SEList.
- El archivo `demo_contiguous_vs_linked.cpp` para demostrar la brecha entre acceso aleatorio y las operaciones en los extremos.