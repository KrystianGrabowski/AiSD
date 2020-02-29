- [Kopce](#kopce)
  - [Kopce opis](#kopce-opis)
  - [Procedury dla kopca](#procedury-dla-kopca)
  - [Budowa kopca](#budowa-kopca)
  - [Zastosowania kopca](#zastosowania-kopca)
    - [Heapsort](#heapsort)
    - [Priority queue](#priority-queue)
    - [Double-ended priority queue](#double-ended-priority-queue)


# Kopce

## Kopce opis
![HeapDataStructure](https://lh5.googleusercontent.com/proxy/DHWvPCAs-tdh9hKI2NqQXUkqOUhOD_E4TFZokx8s-OHgW1Ss14TsWBW2l_xLDOhEU_x9_bbc4KW0CA5t-R3VrjWbDIzeZiu7zyGFddPYncgg9_uzpjgJrZa5tK32aoAYGyQS_BK650CmKMEb)

Kopiec jest to drzewo binarne. Wartości węzłów tego drzewa należą do jakiegoś ustalonego Uniwersum. Drzewo musi być pełne na wszystkich poziomach z wyjątkiem najniższego, który wypełniamy od lewej do prawej strony. Kopce bardzo wygodnie jest reprezentować jako zwykłe tablice.


**Pełne drzewo binarne** - rodzaj drzewa binarnego, w którym każdy węzeł ma 0 lub 2 dzieci (czyli albo liść albo ma dwóch synów).

**Kompletne drzewo binarne** - rodzaj drzewa binarnego, w którym wszystkie poziomy z wyjątkiem ostatniego są całkowicie wypełnione. Natomiast ostatni poziom jest wypełniony od lewej do prawej.

Tablica reprezentująca kopiec(H) powinna mieć dwa atrybuty
1. length[H] - rozmiar tablicy
2. heapsize[H] - liczba elementów kopca w tablicy

Oznacza to, że żaden element kopca występujący po $H[heapsize[H]]$ gdzie $heapsize[H] \leq length[H]$ nie jest elementem kopca. Korzeniem jest $H[1]$, a mając indeks możemy łatwo obliczyć pozycję ojca lub prawego/lewego syna danego elementu.

```python
    def parent(i):
        return floor(i/2)

    def left(i):
        return (2 * i) # (2 * i) + 1 jeśli od 0

    def right(i):
        return (2 * i) + 1 # (2 * i) + 2 jeśli od 0 
```
Szybkość bazuje na tym, że komputer działa w systemie dwójkowym i możemy powyższe opracje wykonywać za pomocą shiftów.

W drzewie obowiązuje porządek kopcowy (min lub max)
$$\forall_{v\not= root} {el(v) \geq el(ojciec(v))}$$
Oznacza to tyle, że dowolny wierzchołek v, który nie jest korzeniem ma większą wartość od swojego ojca (na zdjęciu powyżej jest kopiec typu max czyli odwrotny).

Operacje na naszym kopcu
1. $O(1)$ **min** : zwracamy korzeń czyli H[1]
2. $O(\lg(n))$ **insert**: Dodajemy element jako kolejny liść stosujemy przesuń-wyżej, aż nie będzie żadnych zaburzeń. Po zamianie zaburzenie nie wystąpi na synie, ponieważ wcześniej była zachowana zależność - porządek kopcowy.
3. $O(\lg(n))$ **delete min**: Usuwamy korzeń, który jest minimum i wkładamy tam wartość z ostatniego liścia (do ulepszenia!). Następnie przesuwamy-niżej (wyżej dajemy mniejszą wartość bo inaczej powstanie zaburzenie! - ojciec większy od syna!)

Wysokość węzła w kopcu to liczba krawędzi na najdłuższej ścieżce prostej prowadzącej od tego węzła do liścia, a wysokość kopca to wysokość jego korzenia. Ponieważ kopiec mający n elementów ma kształt pełnego drzewa binarnego, jego wysokość to $\Theta(\lg(n))$. Podstawowe operacje na kopcach działają w czasie proporcjonalnym do co najwyżej wysokości drzewa, czyli $O(n)$. Wiemy również, że w każdym kopcu jest co najwyżej $ceil(\frac{n}{2^{h+1}})$ węzłów o wysokości h.

## Procedury dla kopca

```python
def restoreOrder(arr, index, newElem):
    old = arr[index]
    arr[index] = newElem
    if newElem < old:
        moveDown(arr, index)
    else:
        moveUp(arr, index)
```
```python
def moveDown(arr, index):
    maxVal = index
    while True:
        curr = maxVal
        if 2 * curr <= n and arr[2 * curr] > arr[maxVal]:
            maxVal = 2 * curr
        if 2 * curr < n and arr[2 * curr + 1] > arr[maxVal]:
            maxVal = 2 * curr + 1
        if (curr == maxVal): break
        swap(arr[curr], arr[maxVal])
```
Przesuwając element w dół musimy sprawdzić który z trzech elementów (ojciec, lewy/prawy syn) jest elementem o największej/najmniejszej wartości. Wtedy ten spośród nich staje się ojcem. W kopcu z max w korzeniu szukamy maksimum i zamieniamy je z pozycją ojca. Następnie sprawdzamy czy zaburzenie nie wystąpiło na niższym poziomie.

Złożoność $O(\lg(n))$ z czego $\Theta(1)$ na poprawę zależności między elementem a synami. Czas potrzebny na rekurencyjne wywołanie na poddrzewie zaczepionym w jednym z synów węzła. Każde z poddrzew ma co najwyżej $\frac{2}{3}n$ - najgorszy przypadek gdy ostatni rząd wypełniony do połowy. Zatem taki czas można opisać rekursją
$$ T(n) <= T(\frac{2}{3}n) + \Theta(1)$$
A to zgodnie z przypadkiem 2 twierdzenia o rekursji uniwersalnej
$$T(n) = \lg(n)$$
czyli czas na węźle wysokości h to O(h)


```python
def moveUp(arr, index):
    ptr = index
    while true:
        curr = ptr
        if curr > 1 and arr[floor(curr / 2)] < arr[ptr]:
            ptr = floor(curr / 2)
        if (curr == ptr): break
        swap(arr[curr], arr[ptr])
```
Przesuwając element w górę sprawdzamy jedynie czy zachodzi prawidłowa zależność między nim a jego ojcem. Jeśli nie jest zachowany porządek zamieniamy te dwa elementy pozycjami. Zaburzenie mogło się przenieść jedynie na wyższy poziom. Dzieje się tak dlatego, że zakładamy że przed zamianą obowiązywał w drzewie porządek kopcowy(zał. max). Stąd też wiemy,że:
* Ojciec był wcześniej większy od swoich synów, więc po przesunięciu go w dół ta zależność nie ulegnie zmianie i kolejne dzieci będą od niego mniejsze. 
* Nasz element był większy od ojca, więc również drugi z synów musi zachować zależność, gdyż nowy element jest większy od ojca więc tym bardziej od jego poprzedniego syna.

## Budowa kopca
1. Metoda naiwna polegająca na wykonaniu n razy operacji insert (wstawiamy liść i wywołujemy moveUp). Koszt $O(n\lg(n))$.
2. Budować kopiec możemy również w sposób wstępujący (bottom-up). Wiemy, że elementy podtablicy `arr[ceil(n/2)..n]` są liśćmi, więc możemy je traktować jako jednoelementowe kopce. Możemy teraz przejść przez elementy `arr[floor(n/2)..1]` i wywołać na nich moveDown. Idąc do góry za każdym razem tworzymy z dwóch kopców $2^k - 1$ elementowych i jednego nowego elementu kopiec $2^{k+1} - 1$ elementowy.

```python
def buildHeap(arr):
    for i in reversed(range(1, floor(len(arr)/2)):
        moveDown(arr, i)
```

Można zaobserwować, że moveDown weźmie $O(1)$ dla wierzchołków, które są 1 poziom nad poziomiem liści. Oraz $O(m)$ czasu dla wierzchołków, ktore są m poziomów wyżej. Mamy więc:
* $\frac{n}{4}$ wierzchołków na poziomie 1 (licząc od dołu rzecz jasna)
* $\frac{n}{8}$ wierzchołków na poziomie 2
* $\frac{n}{16}$ ...
* $1$ wierzchołek na poziomie $\lg n$

c - pewna stała liczba operacji
$$\frac{n}{4}(1 \times c) + \frac{n}{8}(2 \times c) + \frac{n}{16}(3 \times c) + ... + 1 (\lg n \times c)$$

Podstawiamy $\frac{n}{4} = 2^k$

$$2^k(1 \times c) + 2^{k-1}(2 \times c) + 2^{k-2}(3 \times c) + ... + 1 (\lg (2^{k+2}) \times c)$$
$$2^kc(1 + \frac{2}{2^1} + \frac{3}{2^2} + ... + \frac{k+2}{2^k})$$

Wszystko w nawiasie jest mniejsze niż 3, więc traktujemy to jako stałą. Zostało nam $2^k$ które jest $\frac{n}{4}$ oraz c które jest stałą. Złożoność więc $O(n)$.

## Zastosowania kopca
### Heapsort
```python
def heapsort(arr):
    buildHeap(arr)
    for i in reversed(range(2, n)):
        swap(arr[1], arr[i])
        heap-size = heap-size - 1
        moveDown(arr, 1)
```
Algorytm sortowania w miejscu. Rozpoczyna się od procedury budującej kopiec (tutaj typu max). Skoro największy element znajduje się w korzeniu arr[1] to może on zostać umieszczony na miejscu, które powinien zajmować po posortowaniu czyli arr[n]. Następnie powinniśmy zmniejszyć heap-size, czyli wskazującą ile elementów jest obecnie w kopcu. Po zamianie miejsc musimy przywrócić porządek kopcowy w korzeniu. Powtarzamy ten proces do uzyskania kopca o rozmiarze 2.

* Złożoność $O(n\lg(n))$
  * Budowa kopca $O(n)$
  * N-1 wywołań moveDown, każde koszt $O(\lg(n))$

Standardowo przesuwając element w dół wykonujemy 2 porównania na poziom. Mamy więc 2 * wysokość kopca porównań. Możemy przyspieszyć heapsort stosując metodę polegającą na przesuwaniu "dziury" w dół kopca. Na dole wstawiamy element, a następnie używając moveUp przesuwamy go wyżej w odpowiednie miejsce. Oszczędność wynika z faktu, że do przesuwania w dół stosujemy tylko 1 porównanie na każdy poziom. Z kolei w średnim przypadku moveUp przesunie element o nie więcej niż 2 poziomy. Dzieje się tak dlatego, że z bardzo dużym prawdopodobieństwem element jest mały, skoro znajdował się wcześniej na samym dole.
### Priority queue
Kolejka priorytetowa to struktura danych do reprezentowania zbioru S elementów, z których każdy ma przyporządkowaną wartość, zwaną kluczem. Na kolejce priorytetowej **typu max**(np. szeregowanie zadań z priorytetami) można wykonać następujące operacje.
1. Insert(S, x) - wstawia element do zbioru S.
2. Maximum(S) - zwraca element zbioru S o najwyższym kluczu.
3. Extract-max(S) - usuwa i zwraca element zbioru S o największym kluczu.
4. Increase-key(S, x, k) - zmienia wartość klucza elementu x na nową wartość k, o której zakłada się, że jest nie mniejsza niż aktualna wartość klucza x

Na kolejce typu min: {Insert, Minimum, Extract-min, Decrease-key} (np. zdarzenia z czasem wystąpienia).

```python
def maximum(arr)
    return arr[1]
```
Złożoność: $O(1)$

```python
def extractMax(arr):
    if len(arr) < 1: raise Exception("Empty list") 
    maximum = arr[1]
    arr[1] = arr[heapsize[arr]]
    heapsize[A] = heapsize[A] - 1
    moveDown(arr, 1) 
    return maximum
```
Złożoność: $O(\lg(n))$

```python
def increaseKey(arr, elem, newVal):
    if newVal < arr[elem]: raise Exception("New value is smaller")
    arr[elem] = newVal
    moveUp(arr, elem)
```
Złożoność: $O(\lg(n))$

```python
def insert(arr, elem):
    heapsize[arr] = heapsize[arr] + 1
    arr[heap-size[arr]] = elem
    moveUp(arr, elem)
```
Złożoność: $O(\lg(n))$

### Double-ended priority queue
![DoubleEndedPriorityQueue](https://upload.wikimedia.org/wikipedia/commons/thumb/e/ec/Interval_heap_depq.jpg/330px-Interval_heap_depq.jpg)
Idea:
1. Wykorzystujemy dwa kopce L i H.
2. W kopcu H pamiętamy $\lceil \frac{n}{2} \rceil$ elementów, a w kopcu L $\lfloor \frac{n}{2} \rfloor$ elementów.
3. Kopiec L jest uporządkowany malejąco, a H rosnąco.
4. Na uporządkowanie z poprzedniego punktu nakładamy dodatkowy warunek. Otóż w kopcach L i H w naturalny sposób zedfiniowane są ścieżki biegnące od korzenia kopca L do korzenia kopca H. Chcemy, aby na każdej takiej ścieżce klucze były uporządkowane niemalejąco.

* **Insert**: Jeżeli nasza kolejka ma parzystą liczbę elementów, element wstawiamy do kopca H, wpp L. Wstawiamy element do pierwszego wolnego liścia. Teraz jednak, zanim będziemy chcieli przesunąć wyżej, musimy sprawdzić, w którą stronę należy przesunąć wstawiony element (w stronę korzenia kopca H czy L). Załóżmy, że został wstawiony do kopca H (przypadek z L symetryczny). Niech y będzie poprzednikiem x-a na drodze do korzenia kopca L (l jest liściem kopca L). Porównujemy x oraz y. Jeśli $x<y$ przestawiamy te elementy, a następnie procedurą moveUp przesuwamy x w odpowiednie miejsce w kierunku korzenia L. Przesunięcie y-ka z kopca L do H nie mogło zaburzyć porządku w tym kopcu. Odwołujemy się tu do punktu 4, czyli mamy zdefiniowane niemalejące ścieżki z L do H. Skoro tak, to jeśli przed zamianą y był w dobrym miejscu na ścieżce, to będzie w dobrym również po przestawieniu z mniejszym x-em. Jeśli $x \geq y$, używamy procedury moveUp do ewentualnego naprawienia porządku w H.
* **DeleteMin**: Usuwamy element z korzenia kopca L. W jego miejsce wstawiamy y, czyli ostatni element kopca L (jeśli przed operacją L i H były równoliczne) albo ostatni element kopca H (jeśli L zawierał 1 element mniej niż H). Następnie procedurą moveDown przywracamy porządek w L. Jeśli moveDown przesunęła y na sam dół kopca L, wówczas porównujemy go z odpowiednim (znajdującym się na tej samej pozycji) elementem kopca H. Jeśli y jest od niego większy, zamieniamy te elementy miejscami, a następnie procedurą moveUp przesuwamy y na odpowiednie miejsce kopca H.
* **DeleteMax**: analogicznie do DeleteMin
