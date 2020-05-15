## O zadaniu 8 z listy 2

Zakładamy, że zbiór monet to $\{1, a, b\}$ oraz $1 < a < b$.

Dla dowolnej liczby $x$ oznaczmy:

1. G(x) - ile monet użyje zachłanny algorytm aby wydać $x$
2. M(x) - ile monet użyje optymalny algorytm aby wydać $x$

Chcemy umieć sprawdzić czy dla danych liczb $a$ oraz $b$ istnieje takie $x$, że $M(x) < G(x)$.

## Dwa przydatne lematy

Lemat 1
    : Jeśli istnieje $x$ takie, że $M(x) < G(x)$, to najmniejsze takie $x$ jest w przedziale $b + 1 < x < a + b$.

Jak to udowodnić? 

1. Oczywiste jest, że każdy kontrprzykład spełnia warunek $b + 1 < x$. 
2. Aby pokazać, że najmniejszy kontrprzykład spełnia $x < a + b$ można przeprowadzić dowód nie wprost. Tzn. zakładamy, że mamy pewną liczbę $x \geq a + b$ oraz, że $G(y) = M(y)$ dla wszystkich $y < x$ i $M(x) < G(x)$.
3. Okazuje się, że przy tych założeniach można udowodnić, że $G(x) = M(x)$ i dostać sprzeczność. Dowód - indukcja + lemat 2.

Lemat 2
    : Dla każdej liczby $x > 1$ oraz dla każdej monety $y \in \{1, a, b\}$ zachodzi $M(x) \leq M(x - y) + 1$, gdzie równość zachodzi wtedy i tylko wtedy kiedy istnieje optymalny sposób wydania liczby $x$, który używa monety y.

Powyższy lemat jest bardzo prosto udowodnić.

## Algorytm

Oznaczmy 
$$b = qa + r$$
gdzie
$$0 \leq r < a$$

Okazuje się, że zachodzi następujące twierdzenie, z którego dostajemy już algorytm 

Twierdzenie
    : Istnieje takie $x \in \mathbb{N}$, że zachodzi $M(x) < G(x)$ wtedy i tylko wtedy kiedy $0 < r < a - q$.
    
Na wcześniejszych zajęciach pokazaliśmy dowód ($\Leftarrow$). Tzn. powiedzieliśmy, że jak zastanowimy się nad wydaniem reszty dla liczby $a + b - 1$, to dostaniemy trójki
$$(a - 1, 0, 1)$$
oraz 
$$(r - 1, q + 1, 0)$$

Pierwsza trójka odpowiada monetom wydanym przez zachłanny algorytm, a druga wydanym przez algorytm optymalny.


Jeśli $a > r + q$ to $M(a + b - 1) < G(a + b - 1)$, bo $(a - 1) + b = r - 1 + a(q + 1)$.

Dowód ($\Rightarrow$) można uzyskać dość prosto z lematów 1 oraz 2.