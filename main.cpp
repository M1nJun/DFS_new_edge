#include "DFS_hack.h"
#include <iostream>

int main() {
    // Initialize the graph from a file
    graph<int> myGraph("graph.txt"); // Assuming "graph.txt" contains the graph data
    
    // Choose two vertices for DFS
    int startVertexKey = 1; // Change to the appropriate vertex key
    int endVertexKey = 5;   // Change to the appropriate vertex key

    // Get pointers to the start and end vertices
    vertex<int>* startVertex = myGraph.V[startVertexKey];
    vertex<int>* endVertex = myGraph.V[endVertexKey];

    // Perform DFS
    edge<int> maxEdge = myGraph.DFS_Visit(startVertex, endVertex);

    // Print the result
    if (maxEdge.weight != 0) {
        std::cout << "Max weight edge found: " << maxEdge.u->key << " -> " << maxEdge.v->key << ", weight: " << maxEdge.weight << std::endl;
    } else {
        std::cout << "No path found from vertex " << startVertexKey << " to vertex " << endVertexKey << std::endl;
    }

    return 0;
}