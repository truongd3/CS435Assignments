According to my program's output, the key-comparisons counts collected are reasonably proportional to the theoretical values (in terms of `n`).

## 1. SMALL-SIZE ARRAY, n = 32

(1) **Worst-case** input of insertion sort algorithm is a reverse sorted array. I populated an array from 32 to 1 and received 496 for `COMPCOUNT`. This exactly equals $\frac{n^2 - n}{2} = \frac{32^2 - 32}{2} = 496$.

(2) **Best-case** input of any sort algorithm is obviously an already sorted array. I populated an array from 1 to 32 and received 31 for `COMPCOUNT`. This makes sense
because we run from the second element, and as array is already sorted, comparison is
performed once each iterations.

(3) **Worst-case** input of insertion sort algorithm is a random array. I never received a result of exactly $\frac{n^2 - n}{4}$ but all could be accepted.

## 2. INCREASING ARRAY SIZES, n = 100, n = 1000, n = 10000

I populated an array with elements from 1 to 10000 randomly. The results of `COMPCOUNT` are always proportional to $\frac{n^2 - n}{4}$ so I'm confident
that my code implement is good.