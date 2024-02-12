// C++ program to print DFS traversal from
// a given vertex in a given graph
#include <iostream>
#include <list>
#include <map>
using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
class Graph {
public:
	map<int, bool> visited;
	map<int, list<int> > adj;
    map<pair<int, int>, int> weight;
    // this is for keeping track of path from u to v
    list<int> record;

	// Function to add an edge to graph
	void addEdge(int u, int v, int w);

	// DFS traversal of the vertices
	// reachable from v
	void DFS(int u);
};

void Graph::addEdge(int u, int v, int w)
{
	// Add w to v’s list.
	adj[u].push_back(v);
    weight[make_pair(u, v)] = w;
}

void Graph::DFS(int u)
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
	Graph g;
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);

	cout << "Following is Depth First Traversal"
			" (starting from vertex 2) \n";

	// Function call
	g.DFS(2);

	return 0;
}

// improved by Vishnudev C
