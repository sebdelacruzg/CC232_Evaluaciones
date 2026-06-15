# Actividad 7 - CC232

### Estudiante
- **Nombre:** Alfredo Sebastián De la Cruz Guanilo

#### Bloque 1 

1. `sem7_demo_avl_deng_core`, `sem7_demo_avl_compact_rotations`, `sem7_demo_bst_deng_vs_avl`, `sem7_demo_redblack_morin`, `sem7_demo_redblack_llrb`, `sem7_demo_compare_avl_vs_redblack`, `sem7_demo_compare_with_semana5`, `sem7_demo_capitulo7_panorama`.

2. `sem7_test_public.exe` y `sem7_test_internal.exe`
3. Todos los headers base `Entry.h`, `BinNode.h`, `BinTree.h`, `BST.h`, `BinaryTree.h`, `BinarySearchTree.h` y las estructuras balanceadas `AVL.h`, `RedBlackTree.h`, `AVLTreeCompact.h`, `RedBlackTreeLLRB.h`.
4.  Semana 5 crea la base enlazada y el BST. Semana 6 implementa prioridades y balanceo (Treap). Semana 7 introduce rebalanceo (AVL, Red-Black).
5. La herencia es un concepto entre clases en el código, no un sistema de archivos. 
6. AVL hereda de BST. RedBlackTree hereda de BinarySearchTree.
7. Ejecución de 100% (2/2 Passed)

#### Bloque 2

1. Para cualquier nodo, todos los elementos en su subárbol izquierdo son menores y todos los del derecho son mayores.

2. Porque visita el subárbol izquierdo (menores), luego la raíz (el valor intermedio), y luego el subárbol derecho (mayores).

3. Porque cada nueva clave es mayor que la anterior, insertándose siempre como el hijo derecho de la hoja actual, formando una lista recta.

4. 
```
    10
      \
       20
         \
          30
            \
             40
               \
                50
                  \
                   60
                     \
                      70
```


#### Bloque 3

1. Que la diferencia de alturas entre su subtree izquierdo y su subtree derecho sea -1, 0 o 1.

2. Restando la altura del subtree derecho a la altura del subtree izquierdo.

3. La altura de cada nodo en la ruta desde la posición modificada ascendiendo hacia la raíz.

4. Almacena el puntero al padre lógico donde la búsqueda falló, siendo este el punto exacto de inserción.

5. Porque un AVL es esencialmente un BST que simplemente aplica metodos de corrección geométricas post-inserción/borrado.

6. Las rotaciones simples y dobles

7. Porque únicamente reasignan punteros locales preservando que el subtree izquierdo siga siendo menor y el derecho mayor.



