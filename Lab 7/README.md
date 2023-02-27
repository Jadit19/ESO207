# Lab 7

1. Implement O(n2) time algorithm for closest pair: find distances between each pair of points and return the one having minimum distance.

2. Implement O(nlog n) time algorithm for closest pair. You may resuse sorting routine(s) of earlier lab(s).

3. Compare running time of above programs for 10,100,5000,25000,50000 pairs.

## Note
Since this involves computing euclidean distance, I've used the `math.h` header for the `sqrt()` function implementation. For compilation:

```sh
gcc min_dist.c -lm
```

This includes the math header while compilation and dosen't produce any errors.