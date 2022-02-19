# API-project-2021
Final project for the "Algorithm and Principles of Computer Science" course at Politecnico di Milano, A.Y. 2020-2021.  
Implementation in C of GraphRanker, a system to rank directed graphs based on the weight of their edges.

## Parameters and commands
d: number of nodes  
k: length of the ranking  
AggiungiGrafo: add a graph to the ranking, it is followed by the adjacency matrix
```Text
AggiungiGrafo
3, 7, 42
0, 7, 2
7, 4, 3
```
TokK: print the best k graphs which have the lowest value of the following metric, sum of the shortest paths between node 0 and all other nodes reachable from 0. If there are multiple graphs with the same value a FIFO policy is followed.  
More details can be found on the specification.

## Execution example
```Text
3,2  // number of nodes = 3, length of the ranking = 2
AggiungiGrafo  // add first graph (index = 0, sum of the shortest path = 7)
0, 4, 3
0, 2, 0
2, 0, 0
AggiungiGrafo  // add second graph (index = 1, sum of the shortest path = 5)
0, 0, 2
7, 0, 4
0, 1, 0
AggiungiGrafo  // add third graph (index = 2, sum of the shortest path = 7)
3, 1, 8
0, 0, 5
0, 9, 0
TopK  // print 0 1 or 1 0
```

## Software & Tools used
Clion  
Valgrind  
AddressSanitizer
