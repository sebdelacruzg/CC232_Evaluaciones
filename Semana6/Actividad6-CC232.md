## Actividad 6
### Bloque 1
**1. ¿Qué targets de demostraciones o pruebas aparecen para Semana 6?**

**2. ¿Qué archivos se incluyen desde `Capitulo6.h`?**
* Capitulo10.h

**3. ¿Qué diferencia práctica hay entre `Capitulo6.h` y `Capitulo10.h`?**
Capitulo6.h es el header real de la semana 6. Incluye directamente todos los módulos de la semana. Mientras que el Capitulo10.h es un alias de compatibilidad solo reexporta el Capitulo6.h 


**4. ¿Qué partes de Semana 6 dependen conceptualmente de Semana 5?**
**5. ¿Qué estructura se usa para prioridad pura?**
**6. ¿Qué estructura se usa para búsqueda ordenada?**
**7. ¿Qué estructura mezcla búsqueda ordenada con prioridad?**
**8. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?.**

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








