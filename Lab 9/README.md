# Lab 9

RB-Trees are binary search trees in which each node has a non-negative integral rank (rank is 0,1,2,...) such that

- Rank of failure nodes is zero
- Rank of parent of failure node is one
- If "x" is any node and p(x) is parent of x, then rank(x) < rank(p(x)) < rank(x)+1
- If g(x) is p(p(x)), the grand parent of x, then rank(x) < rank(g(x))-1

Implement following operations on RB-trees (ranks have to be explicitly mantained).

1. Search
2. Insert
3. Delete

Try to insert 500 random numbers one by one. Then, repeatedly find, print and delete the minimum item (for 100 times)
