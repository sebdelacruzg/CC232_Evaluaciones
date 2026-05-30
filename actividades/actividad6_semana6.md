## Actividad 6
### Bloque 1
**1. ¿Qué targets de demostraciones o pruebas aparecen para Semana 6?**

**2. ¿Qué archivos se incluyen desde `Capitulo6.h`?**
* Capitulo10.h
...

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