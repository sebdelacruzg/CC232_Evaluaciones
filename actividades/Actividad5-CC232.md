# Actividad 5 - CC232

### Estudiante
- **Nombre:** Alfredo Sebastián De la Cruz Guanilo

#### Bloque 1 

1. El enlazado usa punteros a memoria dinámica para conectar nodos dispersos; el implícito usa un arreglo continuo donde las relaciones se calculan aritméticamente.
2. Almacena el valor, un puntero al padre, punteros a los hijos izquierdo y derecho, y la distancia máxima hacia una hoja (altura).
3. Permite navegar hacia la raíz, facilitando encontrar ancestros inmediatos para sucesores y actualizar alturas en cascada tras una modificación.
4. `BinTree` administra la raíz, el tamaño total y las operaciones sobre subárboles completos, mientras `BinNode` gestiona solo su entorno inmediato.
5. Agrega algoritmos de navegación como cálculo de profundidad, tamaño de subárbol, iteradores y dibujo en consola (ASCII).
6. El orden total: para todo nodo, el subárbol izquierdo contiene valores menores y el derecho, mayores.
7. El orden parcial vertical: todo padre tiene un valor menor o igual al de sus hijos.
8. El BST impone un orden lateral estricto ideal para búsquedas; el Heap impone un orden vertical para ubicar el extremo en la raíz.
9. Al visitar izquierda (menores), raíz (medio) y derecha (mayores), se replica el invariante de inserción matemáticamente.
10. El heap no ordena a los hermanos entre sí; solo extrae extremos mediante eliminaciones que destruyen la estructura original.


#### Bloque 2 - Navegación, altura y profundidad

1. Verifican existencia de hijos, si no tiene padre, si no tiene hijos, o su posición relativa izquierda/derecha respecto al padre.
2. Ocurre al tener hijo derecho: el siguiente valor es el nodo más a la izquierda de dicho subárbol.
3. Al no tener hijo derecho, sube por los ancestros hasta encontrar el primero del cual se descienda por la izquierda.
4. Simétricamente: busca el nodo más a la derecha del subárbol izquierdo; si no existe, sube hasta descender por la derecha.
5. En un BST con `[1,2,3,4,5,6,7]` (raíz 4): el sucesor de 2 es 3, su predecesor es 1. El sucesor de 4 es 5.
6. Cuenta aristas hasta la raíz subiendo por el puntero `parent`.
7. Cuenta aristas hasta la hoja más lejana bajando recursivamente sumando 1 al máximo de los hijos.
8. Cuenta todos los nodos dependientes del nodo actual, incluyéndolo a él.
9. Sumando la distancia a la raíz y a la hoja más lejana de un nodo se obtiene un camino que jamás superará la altura máxima global.
10. Se cumple exclusivamente si el nodo pertenece al camino más largo del árbol (ruta crítica).

#### Bloque 3 - Recorridos y trazado guiado

| Recorrido | Versión | Estructura Auxiliar | Secuencia (Demo) | Argumento de Correctitud y Costo |
| :--- | :--- | :--- | :--- | :--- |
| Preorden | Recursiva | Pila de llamadas | 7 3 1 5 4 6 10 8 12 | O(n), visita la raíz antes que los hijos. |
| Preorden | Iterativa | `std::stack` | 7 3 1 5 4 6 10 8 12 | O(n), emula la recursión apilando derechos primero. |
| Inorden | Recursiva | Pila de llamadas | 1 3 4 5 6 7 8 10 12 | O(n), procesa orden lateral estricto. |
| Inorden | Iterativa 1 | `std::stack` | 1 3 4 5 6 7 8 10 12 | O(n), baja a la izquierda y desapila. |
| Inorden | Iterativa 2 | Puntero `parent` | 1 3 4 5 6 7 8 10 12 | O(n), usa procedencia para decidir el giro. |
| Inorden | Iterativa 3 | Método `succ()` | 1 3 4 5 6 7 8 10 12 | O(n), linealiza siguiendo el orden matemático. |
| Postorden | Recursiva | Pila de llamadas | 1 4 6 5 3 8 12 10 7 | O(n), procesa hijos antes que la raíz. |
| Postorden | Iterativa | Dos `std::stack` | 1 4 6 5 3 8 12 10 7 | O(n), invierte un preorden modificado. |
| Niveles | Iterativa | `std::queue` | 7 3 10 1 5 8 12 4 6 | O(n), procesa por capas de profundidad. |

1. Analizar el nodo antes de explorar sus ramas.
2. Analizar el subárbol menor, luego el nodo, y luego el mayor.
3. Procesar completamente toda la descendencia antes de analizar al padre.
4. Explorar horizontalmente todos los nodos a una misma distancia de la raíz.
5. Visitan cada nodo un número constante de veces realizando operaciones O(1).
6. Porque en los bucles, cada nodo entra y sale de la estructura auxiliar una sola vez.
7. O(log n), proporcional a la altura del árbol en la pila.
8. O(n), dado que la profundidad máxima contiene a todos los nodos.
9. La explícita usa memoria del Heap, salvando al programa de un Stack Overflow en árboles inmensos.
10. Porque el nivel más profundo de un árbol completo concentra a la mitad de sus nodos, encolándolos simultáneamente.

#### Bloque 4 - Demostración: evidencia observable

| Archivo | Observable | Idea Estructural | Argumento |
| :--- | :--- | :--- | :--- |
| `demo_binary_tree` | Igualdad de recorridos | Navegación | Valida enlaces `left`, `right` y `parent`. |
| `demo_bst` | Inorden ascendente | Propiedad de búsqueda | Operaciones eficientes O(h). |
| `demo_heap` | Mínimo en raíz | Propiedad de prioridad | Restauración vertical O(log n). |
| `panorama` | Consolidación de demos | ADT Base | Comparación de aplicaciones arbóreas. |

1. La coincidencia idéntica entre las salidas de las versiones recursivas e iterativas.
2. La "Iteración por sucesor" genera la misma cadena ordenada que el inorden clásico.
3. Permite validar visualmente las rotaciones y el desbalance estructural.
4. El vector rotulado como "BST inorden" es estrictamente ascendente.
5. `lowerBound` y `upperBound`, al ubicar el siguiente mayor o igual, no solo coincidencias.
6. La extracción repetida genera una secuencia ordenada ascendente desde el tope.
7. `add()` inserta valores uno a uno; `heapify()` estructura un vector desordenado de forma masiva.
8. El BST, porque conjuga la jerarquía base con la utilidad de la búsqueda eficiente.


#### Bloque 5 - Pruebas públicas e invariantes

1. Inserción de claves, rechazo de duplicados, inorden ascendente, búsquedas y borrado estructural.
2. El assert `expect(!bst.add(5))` falla si la estructura permite ingresar el dato preexistente.
3. Que sin importar el mecanismo de memoria subyacente, el recorrido respete la matemática del árbol.
4. Que devuelva un puntero no nulo al nodo que aloja exactamente el 8.
5. Ambos deben retornar un puntero al valor 10.
6. Que para cada nodo, la rama izquierda sea estrictamente menor y la derecha estrictamente mayor.
7. Que el tamaño baje, la clave no exista y el orden del recorrido inorden permanezca intacto.
8. Que todas las relaciones padre-hijo sean bidireccionales, evitando fugas de memoria o ciclos.
9. La construcción masiva (`heapify`), la inserción individual (`add`) y la extracción (`remove`).
10. La validez del algoritmo HeapSort, sacando siempre el mínimo global actual.
11. La transferencia de ramas enteras sin destruir datos y la eliminación segura de subárboles.
12. La correcta preservación estructural post-rotación y el reacomodo vertical `bubbleUp/trickleDown`.
13. Que las funcionalidades básicas responden correctamente a escenarios estándar.
14. No garantizan eficiencia de tiempo en casos degenerados ni ausencia de bugs en lógicas matemáticas complejas.
15. Las pruebas validan muestras aisladas; los invariantes demuestran la solidez teórica universal del algoritmo.


#### Bloque 6 - Lectura cercana de código

1. `u->left->parent == u` y `u->right->parent == u`.
2. Evita sobrescribir el puntero y generar una fuga de memoria irrecuperable.
3. Suma 1 más el tamaño recursivo de sus ramas izquierda y derecha.
4. Avanzan iterativamente usando solo punteros `left` o `right` hasta topar con nulo.
5. Con hijo derecho, devuelve su `leftmost`. Sin él, sube hasta dejar de ser hijo derecho.
6. Con hijo izquierdo, devuelve su `rightmost`. Sin él, sube hasta dejar de ser hijo izquierdo.
7. `root_` es el ancla de memoria; `size_` permite retornar el conteo en O(1).
8. Recalcula la altura de un nodo mirando a sus hijos inmediatos..
9. Sube por `parent` repitiendo la actualización de alturas hasta la raíz para propagar cambios estructurales.
10. Enlazan la raíz destino al padre fuente y anulan los punteros del árbol original vaciándolo.
11. `removeSubtree` destruye la memoria (delete); `secede` la corta y envuelve en un nuevo árbol independiente.
12. Para reutilizar la estructura desprendida en otro lugar del programa.
13. Para prevenir fugas de RAM al desechar ramas.
14. Recorre validando que el `parent` de cada nodo apunte exactamente al nodo que lo invocó.
15. Mapean a `leftmost()`, `rightmost()`, `succ()` y `pred()` respectivamente.
16. El inorden es, por definición, visitar desde el menor absoluto iterando hacia su sucesor matemático.
17. Dibuja el árbol en consola para validar jerarquías sin requerir un depurador.


#### Bloque 7 - BST

1. Para todo nodo, los valores del subárbol izquierdo son menores y los del derecho son mayores.
2. Al visitar menores, luego raíz, y luego mayores, se extraen los datos en orden aritmético estricto.
3. `findEQ` busca exactitud; `lowerBound` mínimo; `upperBound` mínimo; `find` es alias de `lowerBound`.
4. Si el valor no existe, `findEQ` falla, pero `lowerBound` devuelve el siguiente candidato válido superior.
5. Raíz 7. Izq: 3 (hijos: 1, 5). Hijos de 5: 4, 6. Der: 10 (hijos: 8, 12).
6. In: `1 3 4 5 6 7 8 10 12`. Pre: `7 3 1 5 4 6 10 8 12`. Post: `1 4 6 5 3 8 12 10 7`. Nivel: `7 3 10 1 5 8 12 4 6`.
7. `lowerBound(9)`: 7(der)->10(izq)->8(der)->null, retorna 10. `upperBound(8)`: 7(der)->10(izq)->8(falla por igualdad, der)->null, retorna 10.
8. Hoja: borrar directo. 1 hijo: puentea al padre. 2 hijos: copiar valor del sucesor inorden y borrar dicho sucesor.
9. Función auxiliar que desconecta un nodo con máximo un hijo y conecta al nieto directamente con el abuelo.
10. La propiedad BST lateral y la consistencia de todos los punteros bidireccionales `parent`.
11. Los subárboles se reconectan preservando la estricta relación menores a la izquierda y mayores a la derecha.
12. Sube el hijo derecho como padre y degrada al padre original como su hijo izquierdo.
13. Sube el hijo izquierdo como padre y degrada al padre original como su hijo derecho.
14. Los nodos transferidos quedan entre el viejo y nuevo padre, respetando sus cotas superior e inferior.
15. Garantiza una altura O(log n) evitando búsquedas lentas O(n) en ramas largas.
16. Balanceado: O(log n). Degenerado: O(n) (equivalente a lista enlazada).


#### Bloque 8 - Heap binario

1. Por su forma de árbol completo sin huecos, las posiciones padre-hijo son calculables aritméticamente sobre los índices.
2. En nivel k hay 2^k nodos; al desdoblar, el hijo izquierdo se desfasa i posiciones resultando en 2i+1.
3. El valor de todo padre es estrictamente menor o igual al de sus hijos.
4. La regla de dominancia empuja ineludiblemente el menor valor absoluto al índice cero.
5. El último elemento se compara con su padre; si es menor, intercambian. Repite hasta topar con un padre menor o la raíz.
6. La raíz se intercambia con su hijo menor. Repite hasta ser menor que ambos hijos o llegar a una hoja.
7. Conserva la integridad estructural del arreglo (árbol completo) antes de restaurar el orden vertical bajándolo.
8. Recorre el arreglo validando que ningún padre supere matemáticamente a sus hijos calculados.
9. Insertar usa `bubbleUp` repetidamente; `heapify` baja subárboles optimizando desde las ramas inferiores.
10. Son n inserciones que en el peor caso trepan la altura máxima O(log n) cada una.
11. La mayoría de los nodos (hojas) bajan distancia nula, y pocos nodos (raíz) bajan distancia máxima, sumando O(n) en progresión.
12. 1, 2, 3, 5, 7, 8, 10. Porque cada `remove()` asegura extraer el mínimo global restante en la cima antes de reestructurar.
13. Para extraer el mínimo constante: Heap (O(1)). Para búsquedas por valor: BST (O(log n)).

#### Bloque 9 - Cierre comparativo

- La representación enlazada aporta flexibilidad para trasladar ramas mediante punteros, mientras la implícita maximiza caché operando índices aritméticos.
- La propiedad estructural exige árboles completos sin huecos (Heap), la de orden exige distribución matemática (BST).
- Los recorridos linealizan el árbol, siendo el inorden la prueba de que el árbol respeta la búsqueda binaria.
- El control de alturas y enlaces `parent` permite auto-diagnóstico local constante tras operaciones estructurales dinámicas.
- El BST prioriza la búsqueda lateral ordenada, mientras el Heap asegura la extracción extrema vertical ultra-rápida.
- La correctitud se defiende validando invariantes y probando la complejidad asintótica, evidenciando teóricamente que las pruebas prácticas nunca fallarán.

### Autoevaluación breve

- Qué puedo defender con seguridad: Las diferencias de complejidad entre operaciones de reestructuración `bubbleUp` y `trickleDown`.
- Qué todavía confundo: Trazar manualmente inserciones profundas en BST sin papel de apoyo.
- Qué evidencia usaría en una sustentación: Las funciones validadoras de invariantes y los resultados ordenados en los demos de consola.
- Qué parte del código me parece más importante: Los algoritmos de rotación y las reasignaciones en `splice`.