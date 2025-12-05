# **Optymalizacja Kombinatoryczna**

# **Szukanie grafow calkowitych (integral graphs)**
n=15, k=66
--> Jezeli chcemy inne, to podajemy jako pierwszy i drugi argument przy odpaleniu

## Kompilacja
W głównym katalogu (tym z Makefile) wpisać w terminal "make all". Stworzy to plik "main" w tym samym katalogu ktory wystarczy odpalić ("./main"). 

Parametry "./main a b c d", (opcjonalne):
- a - liczba wierzcholkow
- b - liczba krawedzi
- c - konfiguracja losowosci algorytmu zachlannego, najlepiej dac 0 - wtedy algorytm sam sobie dobierze liczbe
- d - ile chcemy znalezc grafow calkowitych algorytmem zachlannym ulosowionym

Mogą się wyświetlać błędy z plikami header, ale jak się korzysta z Makefile'a to wszystko jest ok

## Miscellaneous
- System: Linux (Windows WSL)

- If you add/delete files, remember to also change Makefile
- Komentarze i nazwy zmiennych są połączeniem polskiego i angielskiego. You have been warned.
- draw(&graph) will create  file graph.dot in graph_visual folder, compile it with "make image" and you get .png
(Graphviz needed)