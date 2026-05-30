# Análisis Técnico - Number of Atoms

## Preguntas Propuestas
1. **¿Cómo detectas un nombre de átomo?** 
Se identifica mediante el primer carácter en mayúscula (`isupper`). Luego, se consumen todos los caracteres en minúscula siguientes (`islower`) para formar el símbolo químico completo.

2. **¿Cómo procesas un número después de un átomo o grupo?** 
Al detectar un dígito (`isdigit`), se lee secuencialmente hasta que el siguiente carácter no sea un número, convirtiendo la subcadena a un entero. Si no hay dígitos, se asume 1.

3. **¿Qué guarda cada contexto en la pila?** 
Cada elemento de la pila es un `std::map<string, int>`. Representa el conteo acumulado de los átomos dentro de un nivel específico de paréntesis.   

4. **¿Cómo combinas los conteos?** 
Al cerrar un paréntesis, el mapa en el tope se extrae (pop), se multiplica por el subíndice externo y se suma al mapa que ahora quedó en el tope (el nivel anterior).

## Complejidad
- **Temporal:** O(N²), donde N es la longitud de la fórmula, debido a que en cada cierre de paréntesis se itera sobre el mapa para fusionar elementos.
- **Espacial:** O(N), para almacenar la pila de contextos y el mapa de frecuencias.