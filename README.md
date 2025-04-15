# Metody Obliczeniowe w Nauce i Technice
## Laboratorium 4 - Symulowane wyżarzanie

### **1.** TSP
Wygeneruj chmurę n losowych punktów w 2D, a następnie zastosuj algorytm symulowanego
wyżarzania do przybliżonego rozwiązania problemu komiwojażera dla tych punktów.<br/><br/>
a) Przedstaw wizualizację otrzymanego rozwiązania dla 3 różnych wartości n oraz 3
różnych układów punktów w 2D (rozkład jednostajny, rozkład normalny z czterema
różnymi grupami parametrów, dziewięć odseparowanych grup punktów).<br/><br/>
b) Zbadaj wpływ sposobu generacji sąsiedniego stanu (consecutive swap vs. arbitrary
swap) oraz funkcji zmiany temperatury na zbieżność procesu optymalizacji.<br/><br/>
c) Przedstaw wizualizację (saoptimset) działania procedury minimalizującej funkcję
celu.<br/>

### **1.** Rozwiązanie
Moje rozwiązanie składa się z takich funkcji jak:
- distance - która liczy odległość, korzystając z metryki Euklidesowej
- toSwapped2opt - zamienia dwie krawędzie miejscami (kopiuje tablicę do 1. wierzhołka, następnie odwraca częśc tablicy pomiędzy 1. i 2. wierzchołkiem, po czym kopiuje do końca bez zmian)
- calculateLength - oblicza długość wszystkich krawędzi
- getNextNeighbor - zwraca toSwapped2opt zamieniając dany wierzchołek i jego następnego sąsiada
- getRandomNeighbor - zwraca toSwapped2opt od dwóch losowuch wierzchołków
- annealing - wykonuje symulowane wyżarzanie
- visualizeGraph - wizualizuje graf i zapisuje go do pliku
- *_graph - 3 funkcje, które zwracają stworzony graf w zależności od nazwy(\*)

#### Funkcja zad1 bierze argumenty: rodzaj grafu, temperatura początkowa, zmiana temperatury, maksymalne ilość powtórzeń, czy losowy sąsiad, wielkość wierzchołka na rysunku.

##### **1.** Rozkład jednostajny, 1414.0, 0.99993, 100000.0, losowy sąsiad, 20.0

![uni_random](img/uni_random.svg)
![uni_random](img/post_uni_random.svg)
![uni_random](img/uni_random_function.svg)

##### **2.** Rozkład jednostajny, 1414.0, 0.99993, 100000.0, następny wierzchołek w grafie, 20.0

![uni_next](img/uni_next.svg)
![uni_next](img/post_uni_next.svg)
![uni_next](img/uni_next_function.svg)

##### **3.** Rozkład noramlny, 1414.0, 0.99993, 100000.0, losowy sąsiad, 40.0

![normal1](img/normal1.svg)
![normal1](img/post_normal1.svg)
![normal1](img/normal1_function.svg)

##### **4.** Rozkład normalny, 1414.0, 0.99993, 100000.0, true, 40.0

![normal2](img/normal2.svg)
![normal2](img/post_normal2.svg)
![normal2](img/normal2_function.svg)

##### **5.** Rozkład normalny, 1414.0, 0.99993, 100000.0, true, 40.0

![normal3](img/noraml3.svg)
![normal3](img/post_noraml3.svg)
![normal3](img/noraml3_function.svg)

##### **6.** Rozkład normalny, 1414.0, 0.99993, 100000.0, true, 40.0

![normal4](img/normal4.svg)
![normal4](img/post_normal4.svg)
![normal4](img/normal4_function.svg)

##### **7.** 9 osobnych klastrów, 1414.0, 0.9999, 100000.0, true, 40.0

![9_section](img/9_section.svg)
![9_section](img/post_9_section.svg)
![9_section](img/9_section_function.svg)

### **2.** Obraz binarny
Wygeneruj losowy obraz binarny o rozmiarze n×n i wybranej gęstości δ czarnych punktów δ = 0.1, 0.3, 0.4. Korzystając z różnego typu sąsiedztwa (4-sąsiadów, 8-sąsiadów, 8-16-sąsiadów) zaproponuj funkcję energii (np. w bliskiej odległości te same kolory przyciągają się, a w dalszej odpychają się, funkcja energii może być również adaptacją modelu Isinga) i dokonaj jej minimalizacji za pomocą algorytmu symulowanego wyżarzania. W jaki sposób można generować stany sąsiednie? Jak różnią się uzyskane wyniki w zależności od rodzaju sąsiedztwa, wybranej funkcji energii i szybkości spadku temperatury?

### **2.** Rozwiązanie

W moim rozwiązaniu przyjąłem rozmiar 300 x 300 bitów, napisałem funkcje dla 8 różnych sąsiedztw, a jako funckję energii zaadaptowałem model Isinga. Stan sąsiedni generuję zamieniając miejscami dwa bity (oczywiście wtedy tylko kiedy są one różne, bo gdy są takie same energia się nie zmienia).

#### Funkcja zad2 bierze argumenty: gęstość, temperatura początkowa, zmiana temperatury, maksymalne ilość powtórzeń, rodzaj sąsiedztwa

##### **1.1.** 0.1, 5000, 0.999995, 2 000 000, mały krzyżyk

![small_cross_0.1](img/small_cross_0.1.bmp)
![small_cross_0.1](img/post_small_cross_0.1.bmp)
![small_cross_0.1](img/small_cross_0.1_function.svg)

##### **1.2.** 0.1, 5000, 0.999995, 2 000 000, mały krzyżyk

![small_cross_0.3](img/small_cross_0.3.bmp)
![small_cross_0.3](img/post_small_cross_0.3.bmp)
![small_cross_0.3](img/small_cross_0.3_function.svg)

##### **1.3.** 0.1, 5000, 0.999995, 2 000 000, mały krzyżyk

![small_cross_0.4](img/small_cross_0.4.bmp)
![small_cross_0.4](img/post_small_cross_0.4.bmp)
![small_cross_0.4](img/small_cross_0.4_function.svg)

##### **2.1.** 0.1, 5000, 0.999995, 2 000 000, mały x

![small_x_0.1](img/small_x_0.1.bmp)
![small_x_0.1](img/post_small_x_0.1.bmp)
![small_x_0.1](img/small_x_0.1_function.svg)

##### **2.2.** 0.1, 5000, 0.999995, 2 000 000, mały x

![small_x_0.3](img/small_x_0.3.bmp)
![small_x_0.3](img/post_small_x_0.3.bmp)
![small_x_0.3](img/small_x_0.3_function.svg)

##### **2.3.** 0.1, 5000, 0.999995, 2 000 000, mały x

![small_x_0.4](img/small_x_0.4.bmp)
![small_x_0.4](img/post_small_x_0.4.bmp)
![small_x_0.4](img/small_x_0.4_function.svg)

##### **3.1.** 0.1, 5000, 0.999995, 2 000 000, x

![x_0.1](img/x_0.1.bmp)
![x_0.1](img/post_x_0.1.bmp)
![x_0.1](img/x_0.1_function.svg)

##### **3.2.** 0.1, 5000, 0.999995, 2 000 000, x

![x_0.3](img/x_0.3.bmp)
![x_0.3](img/post_x_0.3.bmp)
![x_0.3](img/x_0.3_function.svg)

##### **3.3.** 0.1, 5000, 0.999995, 2 000 000, x

![x_0.4](img/x_0.4.bmp)
![x_0.4](img/post_x_0.4.bmp)
![x_0.4](img/x_0.4_function.svg)

##### **4.1.** 0.1, 5000, 0.999995, 2 000 000, duży x

![big_x_0.1](img/big_x_0.1.bmp)
![big_x_0.1](img/post_big_x_0.1.bmp)
![big_x_0.1](img/big_x_0.1_function.svg)

##### **4.2.** 0.1, 5000, 0.999995, 2 000 000, duży x

![big_x_0.3](img/big_x_0.3.bmp)
![big_x_0.3](img/post_big_x_0.3.bmp)
![big_x_0.3](img/big_x_0.3_function.svg)

##### **4.3.** 0.1, 5000, 0.999995, 2 000 000, duży x

![big_x_0.4](img/big_x_0.4.bmp)
![big_x_0.4](img/post_big_x_0.4.bmp)
![big_x_0.4](img/big_x_0.4_function.svg)

##### **5.1.** 0.1, 5000, 0.999995, 2 000 000, duży krzyżyk

![big_cross_0.1](img/big_cross_0.1.bmp)
![big_cross_0.1](img/post_big_cross_0.1.bmp)
![big_cross_0.1](img/big_cross_0.1_function.svg)

##### **5.2.** 0.1, 5000, 0.999995, 2 000 000, duży krzyżyk

![big_cross_0.3](img/big_cross_0.3.bmp)
![big_cross_0.3](img/post_big_cross_0.3.bmp)
![big_cross_0.3](img/big_cross_0.3_function.svg)

##### **5.3.** 0.1, 5000, 0.999995, 2 000 000, duży krzyżyk

![big_cross_0.4](img/big_cross_0.4.bmp)
![big_cross_0.4](img/post_big_cross_0.4.bmp)
![big_cross_0.4](img/big_cross_0.4_function.svg)

##### **6.1.** 0.1, 5000, 0.999995, 2 000 000, pionowa kreska nad punktem

![long_0.1](img/long_0.1.bmp)
![long_0.1](img/post_long_0.1.bmp)
![long_0.1](img/long_0.1_function.svg)

##### **6.2.** 0.1, 5000, 0.999995, 2 000 000, pionowa kreska nad punktem

![long_0.3](img/long_0.3.bmp)
![long_0.3](img/post_long_0.3.bmp)
![long_0.3](img/long_0.3_function.svg)

##### **6.3.** 0.1, 5000, 0.999995, 2 000 000, pionowa kreska nad punktem

![long_0.4](img/long_0.4.bmp)
![long_0.4](img/post_long_0.4.bmp)
![long_0.4](img/long_0.4_function.svg)

##### **7.1.** 0.1, 5000, 0.999995, 2 000 000, ukośnik

![slash_0.1](img/slash_0.1.bmp)
![slash_0.1](img/post_slash_0.1.bmp)
![slash_0.1](img/slash_0.1_function.svg)

##### **7.2.** 0.1, 5000, 0.999995, 2 000 000, ukośnik

![slash_0.3](img/slash_0.3.bmp)
![slash_0.3](img/post_slash_0.3.bmp)
![slash_0.3](img/slash_0.3_function.svg)

##### **7.3.** 0.1, 5000, 0.999995, 2 000 000, ukośnik

![slash_0.4](img/slash_0.4.bmp)
![slash_0.4](img/post_slash_0.4.bmp)
![slash_0.4](img/slash_0.4_function.svg)

##### **8.1.** 0.1, 5000, 0.999995, 2 000 000, losowy kształt
![weird_0.1](img/weird_0.1.bmp)
![weird_0.1](img/post_weird_0.1.bmp)
![weird_0.1](img/weird_0.1_function.svg)

##### **8.2.** 0.1, 5000, 0.999995, 2 000 000, losowy kształt

![weird_0.3](img/weird_0.3.bmp)
![weird_0.3](img/post_weird_0.3.bmp)
![weird_0.3](img/weird_0.3_function.svg)

##### **8.3.** 0.1, 5000, 0.999995, 2 000 000, losowy kształt

![weird_0.4](img/weird_0.4.bmp)
![weird_0.4](img/post_weird_0.4.bmp)
![weird_0.4](img/weird_0.4_function.svg)

### 3. Sudoku
Napisz program poszukujący rozwiązania łamigłówki Sudoku za pomocą symulowanego
wyżarzania. Plansza 9×9 ma zostać wczytana z pliku tekstowego, w którym pola puste
zaznaczone są znakiem x. Jako funkcję kosztu przyjmij sumę powtórzeń cyfr występujących
w wierszach bloku 9 × 9, kolumnach bloku 9 × 9 oraz blokach 3 × 3. Zaproponuj
metodę generacji stanu sąsiedniego. Przedstaw zależność liczby iteracji algorytmu od
liczby pustych miejsc na planszy. Czy Twój program jest w stanie znaleźć poprawne
rozwiązanie dla każdej z testowanych konfiguracji wejściowych?