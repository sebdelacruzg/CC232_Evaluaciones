# Benchmark y Rendimiento Teórico

Debido a la naturaleza del problema (reconstrucción de un Skew Heap), no se requiere un análisis de rendimiento contra otras estructuras, sino una justificación de la complejidad asintótica.

La operación de un-swap destructiva tiene un costo amortizado de $O(\log N)$ por nodo. Para $N$ elementos, la complejidad total de reconstrucción es $O(N \log N)$. 

Esta eficiencia garantiza que para el límite máximo del problema ($N = 200,000$), el tiempo de ejecución se mantendrá en el orden de los milisegundos, superando el Time Limit de 2.0 segundos establecido por el ICPC.