# Actividad 4-CC232

### Estudiante
- **Nombre completo:** Alfredo Sebastián De la Cruz Guanilo


#### Bloque 1

1. LIFO (Last-In, First-Out) atiende primero lo más reciente (como una pila de platos). FIFO (First-In, First-Out) atiende en orden de llegada (como una cola de banco).
2. La pila es ideal para tareas anidadas; permite pausar una tarea, resolver la nueva (última pendiente) y luego retomar la anterior.
3. La cola modela procesos donde el tiempo de llegada dicta la prioridad, garantizando un orden justo y secuencial.
4. Es usar un `ods::Stack` manual en lugar de dejar que el sistema operativo use su propia memoria (Call Stack). Esto evita errores de memoria como el Stack Overflow.
5. Para reconstruir una ruta, la pila debe guardar al menos la posición actual (coordenadas) y la dirección que se intentará después.
6. Ambas versiones usan divisiones y residuos. La recursiva usa el retorno de funciones para imprimir, mientras que la iterativa usa una pila para invertir los datos manualmente.
7. Se guardan las aperturas para saber, al encontrar un cierre, si corresponden al tipo correcto y al orden LIFO.
8. El evaluador usa una pila para números (operandos) y otra para signos (operadores) para poder aplicar la jerarquía matemática correctamente.
9. N-Reinas y Laberinto usan backtracking porque exploran un camino hasta fallar y luego "retroceden" (pop) al último punto seguro para probar otra opción.
10. Requiere colas (FIFO) porque el servicio debe ser por orden de llegada; una pila (LIFO) sería injusta con los primeros clientes.
11. La estructura impone la regla (LIFO/FIFO) y el estado guardado permite que el algoritmo no se pierda, asegurando un resultado válido.
12. Resolver busca una respuesta específica (ej. la salida); simular observa cómo se comporta un sistema en el tiempo (ej. qué tan larga es la cola).

#### Bloque 2 

| Archivo | Salida u observable | Técnica central | Concepto defendido |
| :--- | :--- | :--- | :--- |
| `demo_stack_queue.cpp` | 9 (pila), 10 (cola) | LIFO / FIFO | Reglas de acceso restringido |
| `demo_base_conversion.cpp`| 30071 (base 8) | Inversión con Stack | Equivalencia recursivo-iterativo |
| `demo_paren_rpn.cpp` | RPN: 0! 1 + ... | Pilas duales | Prioridad de operadores |
| `demo_nqueens.cpp` | Soluciones para N=4 | Backtracking | Búsqueda exhaustiva |
| `demo_maze.cpp` | Lista de coordenadas | Backtracking | Exploración de rutas |
| `demo_bank.cpp` | Estados t=0 a t=10 | FIFO (Queues) | Flujo temporal de servicio |
| `demo_panorama.cpp` | Resumen de todo | ADTs integrados | ADT como herramienta algorítmica |

**Respuestas:**
1. El `pop` de la pila da el último valor (9), el `dequeue` de la cola da el primero (10).
2. Ambas funciones retornan la cadena `"30071"`, validando que hacen lo mismo.
3. El balanceo asegura que la RPN se genere sin errores y el valor final sea matemáticamente exacto.
4. Solutions son éxitos; Checks son todos los intentos. Los checks miden el esfuerzo real del CPU.
5. Muestra que el camino es continuo: cada paso está al lado del anterior.
6. Representa el tiempo que le falta a cada cliente en esa cola para ser atendido.
7. Muestra que con Pilas y Colas se cubren desde operaciones básicas hasta lógica de IA.

#### Bloque 3 - Pruebas y Correctitud

1. Valida `push`, `pop`, `top` y si está vacía.
2. Valida `enqueue`, `dequeue`, `front` y orden FIFO.
3. Valida el resultado exacto en base 8.
4. Prueba anidamientos válidos, inválidos y cruzados (`[)]`).
5. Verifica el valor final y la cadena RPN de una expresión compleja.
6. Asegura que para N=4 solo existan 2 soluciones.
7. Valida que el camino empiece en el inicio y termine en la meta.
8. Confirma que el cliente elija siempre la cola más corta.
9. Cubre el número 0, bases inválidas (excepciones) y laberintos sin salida.
10. Pasar pruebas no asegura que el código sea eficiente o funcione con millones de datos; la teoría sí.
11. Un algoritmo que no marque celdas como "visitadas" pasaría pruebas en laberintos simples, pero se trabaría en bucles en laberintos complejos.

#### Bloque 4 - Recursivo vs Iterativo

1. El cociente reduce el problema, el residuo es el dígito y la pila invierte el orden para leerlo bien.
2. El primer residuo es el último dígito del número; apilarlos permite sacarlos al revés (del primero al último).
3. La versión iterativa usa la memoria "Heap" (más grande), evitando el colapso que sufre el "Call Stack" en problemas gigantes.
4. Busca el cierre que le corresponde a la primera apertura para dividir el problema en dos partes más chicas.
5. La recursiva provista solo entiende `()`; la iterativa maneja `()`, `[]` y `{}` fácilmente con una pila de tipos.
6. Si el cierre que aparece no coincide con lo último que se abrió (tope de la pila), el error es inmediato.
7. La iterativa es mejor para procesos matemáticos (base); la recursiva es más clara para estructuras tipo árbol (paréntesis).

**Experimento 1: Conversión**
| Número | Base | Salida Rec | Salida Iter | Coinciden |
| :--- | :--- | :--- | :--- | :--- |
| 15 | 2 | 1111 | 1111 | Sí |
| 100 | 16 | 64 | 64 | Sí |
| 50 | 3 | 1212 | 1212 | Sí |
| 0 | 8 | 0 | 0 | Sí |

**Experimento 2: Paréntesis**
| Expresión | Rec | Iter | Explicación |
| :--- | :--- | :--- | :--- |
| `(a+b)` | True | True | Simple |
| `[a+b]` | False*| True | *Rec solo soporta () |
| `(a[b])`| False*| True | Anidado mixto |
| `((a))` | True | True | Doble |


#### Bloque 5 - Evaluación de Expresiones

1. Guarda el resultado numérico (`double`) y la expresión en formato máquina (`RPN`).
2. Se borran para que el código solo lea números y signos sin confundirse.
3. Se detecta si el `-` está al principio o justo después de un signo u apertura `(`.
4. Es unario (afecta a un solo número). El código exige que sea un entero positivo.
5. Se construye cada vez que un signo sale de la pila de operadores por tener mayor prioridad.
6. Si el signo nuevo es más importante que el del tope, se guarda (push); si es menos, se opera lo que ya estaba (pop).
7. Una expresión mal escrita no debe dar un número falso, debe avisar que está mal para no causar cálculos peligrosos.
8. Obtener ambos permite verificar que el resultado es correcto y entender cómo lo calculó la computadora.

**Experimento 3: Evaluación**
| Expresión | RPN | Valor | Comentario |
| :--- | :--- | :--- | :--- |
| `1+2*3` | 1 2 3 * + | 7 | Multiplica primero |
| `(1+2)*3` | 1 2 + 3 * | 9 | Paréntesis primero |
| `-5+10` | -5 10 + | 5 | Unario detectado |
| `2++2` | - | Error | Error sintáctico |

#### Bloque 6 - Backtracking

1. Dos reinas se atacan si están en la misma fila, columna o diagonal.
2. Guarda las posiciones de las reinas que ya están puestas de forma segura.
3. Avanzar es poner reina en la fila siguiente. Retroceder es quitar la actual e intentar la siguiente casilla de la fila anterior.
4. Es el conteo de comparaciones. Indica cuánto "trabajó" el procesador para hallar la solución.
5. Si es falso, el código solo cuenta soluciones sin gastar memoria en guardarlas.
6. `AVAILABLE` (libre), `ROUTE` (camino), `BACKTRACKED` (camino muerto), `WALL` (pared).
7. `Incoming` dice de dónde vine; `Outgoing` dice qué dirección (N, S, E, O) estoy probando ahora.
8. Se marca para no caminar en círculos y no volver a intentar caminos que ya sabemos que fallan.
9. Ambos usan una pila para recordar el camino. N-Reinas busca todas las formas; Laberinto busca una ruta de A a B.

**Experimento 4: N-Queens**
| N | Soluciones | Checks | Crecimiento |
| :--- | :--- | :--- | :--- |
| 4 | 2 | 114 | Base |
| 6 | 4 | 930 | Rápido |
| 8 | 92 | 15720 | Exponencial |

**Experimento 5: Laberintos Propios**
1. Grilla simple, salida directa en 3 pasos. Cero retrocesos.
2. Grilla cerrada por paredes. La pila se vacía totalmente y el algoritmo retorna "no encontrado".
3. Laberinto con una "trampa" (camino largo que se corta). Se evidencia retroceso cuando el algoritmo marca la trampa como `BACKTRACKED` y busca la ruta real.

#### Bloque 7 - Simulación Bancaria

1. Cada cola representa la fila física de personas esperando en una ventanilla.
2. Elige la cola con menos personas. Si empatan, elige la primera que vea.
3. Permite repetir exactamente la misma llegada de "clientes aleatorios" para comparar resultados.
4. llegadas siempre serán mayores o iguales. Los que no se atendieron se quedan en la cola final.
5. Es un registro minuto a minuto de cuánta gente había en cada cola.
6. Son necesarias porque el banco debe respetar quién llegó primero (justicia FIFO).
7. Asume que todos los cajeros son igual de rápidos y que nadie se va del banco por cansancio.
8. Si fuera "ventanilla al azar", las colas estarían desbalanceadas y la espera sería mayor.

**Experimento 6: Variación de Parámetros**
| Ventanillas | Tiempo | Seed | Atendidos | Observación |
| :--- | :--- | :--- | :--- | :--- |
| 3 | 20 | 100 | 14 | Flujo estable y colas cortas. |
| 1 | 20 | 100 | 4 | Gran congestión (cuello de botella). |
| 3 | 20 | 500 | 12 | Diferente semilla, diferente flujo de gente. |

#### Bloque 8 - Cierre

Al pasar de usar Pilas y Colas como simples cajones de datos a usarlas como mecanismos de control, el programador toma el mando de la lógica del problema. 

- LIFO/FIFO** dictan si el algoritmo retrocede (Stack) o espera (Queue). 
- La pila explícita protege la memoria del sistema y permite resolver problemas más grandes. 
- En expresiones, las pilas traducen el lenguaje humano al de la máquina. 
- En backtracking, la pila es una memoria de decisiones que permite explorar miles de opciones sin perderse. 
- En simulación, la cola modela el paso del tiempo y la justicia. 

En conclusión: pasamos de guardar información a diseñar el comportamiento dinámico del software.

#### Autoevaluación
- Entiendo el uso de la pila para retroceder en laberintos y N-reinas.
- A veces cuesta visualizar la RPN de expresiones con muchos paréntesis anidados sin papel.
- El experimento de N-Reinas mostró cómo el esfuerzo (checks) crece muchísimo más rápido que las soluciones.
- Usaría la comparación de `toBaseRecursive` vs `Iterative` para explicar por qué las estructuras explícitas son más seguras.