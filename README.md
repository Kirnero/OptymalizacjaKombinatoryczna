# **Optymalizacja Kombinatoryczna**

# **Szukanie grafow calkowitych (integral graphs)**
n=15, k=66
--> zadeklarowane w misc.h jako number_of_vertices i number_of_edges.
Tak, jest hardcoded

## Kompilacja
W głównym katalogu (tym z Makefile) wpisać w terminal "make all". Stworzy to plik "main" w tym samym katalogu ktory wystarczy odpalić ("./main"). Może dodam do niego parametry później.

Mogą się wyświetlać błędy z plikami header, ale jak się korzysta z Makefile'a to wszystko jest ok

## Miscellaneous
- System: Linux (Windows WSL)

- If you add/delete files, remember to also change Makefile
- Komentarze i nazwy zmiennych są połączeniem polskiego i angielskiego. You have been warned.
- draw(&graph) will create  file graph.dot in graph_visual folder, compile it with "make image" and you get .png
(Graphviz needed)