## Actividad 2 - CC232

### Integrantes
- Alfredo Sebastián De la Cruz Guanilo

#### Bloque 1 
1. Significa que los elementos se almacenan en direcciones de memoria adyacentes, sin fragmentación física entre ellos. Esto permite que el hardware acceda de forma extremadamente rápida al bloque completo.
2. Gracias a la contigüidad, el acceso es una simple operación aritmética: `Dirección = Inicio + (Índice * Tamaño)`. No requiere recorridos, solo un cálculo instantáneo.
3. `Size` es la cantidad de elementos que realmente contienen información útil (lógico), mientras que `Capacity` es el tamaño total del bloque de memoria reservado en la RAM (físico).
4. Como el arreglo es contiguo, si no hay espacio libre justo al final del bloque actual, no se puede "estirar". Es obligatorio pedir un bloque nuevo a la RAM y mudar todos los datos.
5.  Al duplicar la capacidad en lugar de sumarle una constante, garantizamos que el costo de copiar $n$ elementos se reparta entre $n$ inserciones futuras, resultando en un costo constante por operación en promedio.
6. Comparten el uso de arreglos contiguos. `ArrayStack` se enfoca en la implementación de la interfaz `List` de Morin, mientras que `DengVector` enfatiza el manejo de recursos de C++ como la gestión de memoria y el concepto de "rango" de Deng.
7. Optimiza el rendimiento usando funciones de sistema como `std::copy` o `memmove` para desplazar bloques de memoria, lo que es mucho más rápido que un bucle `for` manual, aunque la complejidad asintótica no cambie.
8. Minimiza el desperdicio de memoria dividiendo la estructura en múltiples bloques de tamaño creciente (1, 2, 3...), logrando un desperdicio de solo $O(\sqrt{n})$.
9. Se usan para que el número de bloques crezca lentamente. Con $r$ bloques, la capacidad total es la suma de los primeros $r$ enteros, lo que permite un mapeo matemático preciso.
10. Las estructuras contiguas ofrecen velocidad de acceso pero sufren por desplazamientos en inserciones. `Rootish` mejora el uso de espacio, pero añade complejidad matemática al cálculo de índices.

#### Bloque 2 

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo o espacio |
| :--- | :--- | :--- | :--- |
| `demo_array_basico.cpp` | Transferencia de ownership en `b = a`. | Arreglo contiguo estático. | Acceso $O(1)$ por cálculo de dirección. |
| `demo_arraystack_explicado.cpp` | Visualización de desplazamientos. | Arreglo dinámico lineal. | $O(n-i)$ por movimientos de elementos. |
| `demo_fastarraystack.cpp` | Velocidad de copia de bloques. | Optimización de bajo nivel. | Reduce la constante del tiempo lineal. |
| `demo_rootisharraystack_explicado.cpp` | Mapeo de `i` a `(bloque, offset)`. | Estructura de bloques. | Desperdicio espacial de $O(\sqrt{n})$. |
| `demo_deng_vector.cpp` | Log de crecimiento de capacidad. | Crecimiento geométrico. | Justifica el costo amortizado $O(1)$. |
| `demo_stl_vector_contraste.cpp` | Similitud con `DengVector`. | Estándar de la industria. | Validación de los conceptos de clase. |

1. Muestra que en esta implementación la asignación transfiere el control del puntero, dejando al objeto original sin el arreglo.
2. La operación `add(1, 15)` ilustra perfectamente el costo de desplazar el sufijo hacia la derecha.
3. Demuestra que usar funciones de biblioteca optimizadas es la forma correcta de implementar estructuras basadas en arreglos en la práctica.
4. El mapeo del índice 5 al bloque 2 muestra cómo la estructura fragmenta los datos físicamente pero los mantiene unidos lógicamente.
5. El seguimiento de `capacity` demuestra que la memoria se reserva de forma anticipada para optimizar las futuras inserciones.
6. Confirma que las estructuras estudiadas siguen la misma lógica de `std::vector`.
7. Usaría `demo_deng_vector` para **amortización** y `demo_rootisharraystack_explicado` para **uso de espacio**.

#### Bloque 3 
1. Valida inserción, lectura y borrado básico.
2. Valida la integridad de los datos tras usar copias rápidas.
3. Valida el cálculo de bloques en índices arbitrarios.
4. Demuestran que la interfaz del ADT funciona correctamente para casos estándar.
5. No detectan fugas de memoria sutiles ni garantizan que la complejidad sea la correcta en escalas masivas.
6. Evalúa la estabilidad de la estructura ante ciclos agresivos de `expand()` y `shrink()`, verificando que no haya corrupción de punteros.
7. Pasar una prueba es evidencia empírica, pero el invariante es una garantía lógica de que la estructura se mantiene válida en cualquier estado posible.

#### Bloque 4 
1. `_size` es el tamaño lógico, `_capacity` el físico y `_elem` el puntero al bloque de memoria.
2. Se ejecuta solo cuando el factor de carga llega al 100% (`_size == _capacity`).
3. Requiere desplazamientos para mantener la **memoria contigua**, moviendo todos los sucesores para abrir un hueco.
4. `remove(r)` es un caso particular que delega a `remove(lo, hi)`, el cual desplaza el bloque de datos una sola vez para ser eficiente.
5. Se evidencia en el constructor por copia, donde se reserva nueva memoria para que dos vectores no compartan el mismo puntero.
6. Permite aplicar una acción uniforme sin exponer los punteros internos, protegiendo el encapsulamiento.
7. Ayuda a entender conceptos vitales como el ciclo de vida de los objetos y el costo de redimensionamiento que suelen estar ocultos en `std::vector`.

#### Bloque 5 
1.  Se distribuyen en arreglos de tamaño 1, 2, 3... hasta $r$.
2.  Porque la capacidad total es la suma de los tamaños de los bloques: $1+2+3...+r = r(r+1)/2$.
3. Resuelve la posición del bloque mediante la fórmula cuadrática derivada de la suma de los primeros $n$ enteros.
4.  Devuelve las coordenadas físicas exactas del dato en la matriz de bloques.
5.  Se gana eficiencia al reducir el desperdicio máximo a $O(\sqrt{n})$, a diferencia del desperdicio lineal de los vectores tradicionales.
6. Se conserva idéntica a una lista, lo cual es la esencia del ADT: ocultar la complejidad interna tras métodos conocidos.
7. El **mapeo matemático** es el reto principal, pues requiere explicar la relación entre la suma de Gauss y la posición del elemento.

#### Bloque 6 
1. Permite que el ADT se comporte como un arreglo nativo, facilitando su integración en algoritmos existentes.
2. Supone que el tipo de dato almacenado tiene implementado el operador de igualdad (`==`).
3. Muestra que la estructura es capaz de procesar sus elementos de forma iterativa y genérica.
4. Conecta la teoría de ADT con la implementación concreta de redimensionamiento que trabajamos en el código.

#### Bloque 7 
Diseñar una estructura dinámica implica pasar de un contenedor estático a uno que gestiona su propio ciclo de vida.
- El uso de memoria contigua es la base de la eficiencia en el acceso directo.
-  El invariante de contigüidad asegura que el acceso por rango sea siempre válido.
- Las políticas de crecimiento geométrico garantizan que la estructura sea eficiente en el tiempo a largo plazo.
-  Estructuras como `Rootish` demuestran que se puede optimizar la memoria física sin sacrificar la interfaz lógica.
-  `ArrayStack` es la base, `FastArrayStack` la optimización práctica y `RootishArrayStack` la optimización arquitectónica del espacio.

#### Autoevaluación breve
- La lógica de redimensionamiento, el análisis amortizado de $O(1)$ y el costo de los desplazamientos.
- Algunos detalles de la aritmética modular en deques circulares.
-  El trazado de capacidad del `DengVector` y el layout de bloques del `RootishArrayStack`.
