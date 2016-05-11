# Frogpuzzle #

1) Question: 

M frogs are at the most left and N toads are at the most right. How many minium steps to completely switch positions of frogs and toads? 

2) Solution:

The solution applied BFS(Breadth First Search) idea to find all possible positions at each move and stop moving when frogs and toads are completely switched. Therefore, the minimum depth is found and the other branches are ignored.  

3) Comments:

Modify FrogAndToad.cpp to use <algorithm> functions instead of writing own functions such as converting to uppercase characters, finding the empty positions, and calculating numbers of frogs and toads etc. Even though applying STL functions will scan the position array several times compared to scanning only once in current implementation, it's better to use STL which gurantees validality and readility of codes.  
