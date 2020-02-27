- [Kopce](#kopce)
  - [Kopce opis](#kopce-opis)


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
1. $\Omicron(1)$ **min** : zwracamy korzeń czyli H[1]
2. $\Omicron(\lg(n))$ **insert**: Dodajemy element jako kolejny liść stosujemy przesuń-wyżej, aż nie będzie żadnych zaburzeń. Po zamianie zaburzenie nie wystąpi na synie, ponieważ wcześniej była zachowana zależność - porządek kopcowy.
3. $\Omicron(\lg(n))$ **delete min**: Usuwamy korzeń, który jest minimum i wkładamy tam wartość z ostatniego liścia (do ulepszenia!). Następnie przesuwamy-niżej (wyżej dajemy mniejszą wartość bo inaczej powstanie zaburzenie! - ojciec większy od syna!)

Wysokość węzła w kopcu to liczba krawędzi na najdłuższej ścieżce prostej prowadzącej od tego węzła do liścia, a wysokość kopca to wysokość jego korzenia. Ponieważ kopiec mający n elementów ma kształt pełnego drzewa binarnego, jego wysokość to $\Theta(\lg(n))$. Podstawowe operacje na kopcach działają w czasie proporcjonalnym do co najwyżej wysokości drzewa, czyli $\Omicron(n)$.
