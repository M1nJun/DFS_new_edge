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
    void DFS(T u); // T v

};

template<typename T>
void Graph<T>::addEdge(T u, T v, int w)
{
    // Add w to v’s list.
    adj[u].push_back(v);
    weight[make_pair(u, v)] = w;
}

template<typename T>
void Graph<T>::DFS(T u) //T v
{
    // Mark the current node as visited and
    visited[u] = true;
    // update the record of DFS from u to v
    record.push_back(u);
    cout << static_cast<char>(u) << " ";

    // // as soon as DFS finds v, stop
    // if(visited[u] == v)
    //     return

    // Recur for all the vertices adjacent
    // to this vertex
    // question: would the iterator be bothered? Because I added one more argument v to the function?
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

    //question: 
    Edge<char> newEdge;
    std::cout << "Enter the start and end vertex, and the weight of the new edge each separated by a space: ";
    cin >> newEdge.u >> newEdge.v >> newEdge.w;

    cout << "Following is Depth First Traversal"
            " (starting from vertex C) \n";

    // Call DFS first to secure the path from u to v
    // If you call DFS after adding the edge, you cannot guarantee
    // that DFS will follow the path to the old part of the cycle.
    g.DFS(newEdge.u);

    //check if user added already existing edge:
    //should I access the weight data structure?


    // problem while trying to iterate record, a process to check if record works.
    // auto itr = record.begin();
	// while(itr != record.end()) {
	// 	cout << itr << " "
	// 	itr++;
	// }
    // std::cout << std::endl;

    // initialize int max as 0
    // set up a loop that does this:
    // record list: grab the last and the second to last element
    // and access the weight data structure to grab the weight
    // compare and update max
    // next iteration, go down one index for both indices
    // do the same until you reach vertex u as the second index.

    // all you have to do now is comparing the max and the weight of the new Edge.
    // throw away or keep

    // question: How will you know which vertex has that weight? can you access the key using the value in a map?

    return 0;
}
