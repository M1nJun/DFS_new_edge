#include <iostream>
#include <list>
#include <map>
using namespace std;

// This struct is for the purpose of saving the data of the new edge
template<typename T>
struct Edge {
    T u;
    T v;
    int w;
};

// Graph class represents a directed graph
// using adjacency list representation
template<typename T>
class Graph {
public:
    map<T, bool> visited;
    map<T, list<T> > adj;
    map<pair<T, T>, int> weight;
    // this is for keeping track of path from u to v when performing the DFS from u
    list<T> record;

    // Function to add an edge to graph
    void addEdge(T u, T v, int w);

    // DFS traversal of the vertices
    // reachable from v
    void DFS(T u);
};

template<typename T>
void Graph<T>::addEdge(T u, T v, int w)
{
    // Add w to v’s list.
    adj[u].push_back(v);
    weight[make_pair(u, v)] = w;
}

template<typename T>
void Graph<T>::DFS(T u)
{
    // Mark the current node as visited and
    // print it
    visited[u] = true;
    record.push_back(u);
    cout << u << " ";

    // Recur for all the vertices adjacent
    // to this vertex
    list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
		if (!visited[*i])
			DFS(*i);
}

// Driver code
int main()
{
    // Create a graph given in the above diagram
    Graph<int> g;
    g.addEdge('A', 'C', 3);
    g.addEdge('C', 'B', 4);
    g.addEdge('C', 'D', 6);
    g.addEdge('D', 'E', 2);

    Edge<string> newEdge;
    std::cout << "Enter the start and end vertex, and the weight of the new edge each separated by a space: ";
    cin >> newEdge.u >> newEdge.v >> newEdge.w;

    cout << "Following is Depth First Traversal"
            " (starting from vertex C) \n";

    // Function call
    g.DFS('C');

    return 0;
}
