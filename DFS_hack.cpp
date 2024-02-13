#include <string>
#include <list>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

template <typename T> class edge;
// This version of bfs uses a pointer representation.
// Each vertex contains within it a list of pointers
// to the other vertices the vertex is connected to.
template <typename T> class vertex
{
public:
	T key;
    bool visited;
    vertex<T> *prev;
    int w;
	std::list<edge<T> > edges;

	vertex() {}
	vertex(const T& v) { key = v; prev = NULL;}
};

template <typename T> class edge
{
public:
	vertex<T> *u, *v;
	int weight;

    //default constructor
    edge() : u(nullptr), v(nullptr), weight(0) {}

	edge(vertex<T>* a, vertex<T>* b, int w)
	{
		u = a; v = b; weight = w;
	}
};

template <typename T> class graph
{
public:
	graph();
	~graph();

	edge<T> DFS(vertex<T> *u, vertex<T> *v);
    edge<T> DFS_Visit(vertex<T> *u, vertex<T> *v);
    vertex<T>* getVertex(const T& key);
private:
	// Since the edges are stored in the vertices, we only need
	// a list of vertices in the graph. For convenience, this is
	// stored as a map.
	std::map<T,vertex<T>*> V;
};

template <typename T>
graph<T>::graph()
{
	std::ifstream in;
    in.open("graph.txt");
    
    int nV;
    in >> nV;
    int key;
        
    for(int n = 0;n < nV;n++) {
        in >> key;
        V[key] = new vertex<T>(key);
    }
    
    int nE;
    in >> nE;
    int from, to, w;
    for(int n = 0;n < nE;n++) {
        in >> from >> to >> w;
        vertex<T> *u = V[from];
        vertex<T> *v = V[to];
        //says to give template arguments to this edge() function here. But why should I give it a template argument when it constructs an edge?
        u->edges.push_back(edge<T>(u, v, w));
        v->edges.push_back(edge<T>(v, u, w));
    }
    in.close();
}

template <typename T>
graph<T>::~graph() {
	auto itr = V.begin();
	while(itr != V.end()) {
		delete itr->second;
		itr++;
	}
}

template <typename T>
edge<T> graph<T>::DFS(vertex<T> *u, vertex<T> *v) {
    auto itr = V.begin();
    while (itr != V.end()) {
        itr->second->visited = false;
        ++itr;
    }
    return DFS_Visit(u, v);
}

template <typename T>
edge<T> graph<T>::DFS_Visit(vertex<T> *u, vertex<T> *v){
    u->visited = true;
    if (u == v){
        return edge<T>(u->prev,u,u->w);
    }
    edge<T> winner;
    winner.weight = 0;
    for (auto itr = u->edges.begin();itr != u->edges.end();itr++) {
        if (itr->v->visited == false){
            // check if you went to the same edge you came from
            if (itr->v == u->prev){
                continue;
            }
            edge<T> currentEdge = DFS_Visit(itr->u, v);
            if(currentEdge.weight > winner.weight)
                winner = currentEdge;
        }
    }
    return winner;
}

template <typename T>
vertex<T>* graph<T>::getVertex(const T& key) {
        if (V.find(key) != V.end()) {
            return V[key];
        } else {
            return nullptr; // Key not found
        }
    }

int main() {
    // Create an instance of the graph
    graph<int> G;
    bool case1 = false;
    // Prompt the user for input for the new edge
    int u, v, weight;
    cout << "Enter the vertices (u v) and weight of the new edge: ";
    cin >> u >> v >> weight;

    // Create a new edge with the user input
    vertex<int>* uVertex = G.getVertex(u);
    vertex<int>* vVertex = G.getVertex(v);
    edge<int> newEdge(uVertex, vVertex, weight);

    auto itr = uVertex->edges.begin();
    while (itr != uVertex->edges.end()) {
        if(itr->u == newEdge.u && itr->v == newEdge.v){
            case1 = true;
            if(itr->weight < newEdge.weight){
                cout << "You created an edge where there's already an edge. The new edge will make the spanning tree more expensive. Should ignore the new edge and keep the original tree.";
            }
            else if(itr->weight > newEdge.weight){
                cout << "You created an edge where there's already an edge. The new edge will make the spanning tree cheaper. Should use the new edge and drop the original edge between " << u << " and " << v;
            }
            else{
                cout << "You created an edge where there's already an edge. Since the new and the old one has the same weight, the new edge does not make the tree cheaper. Should ignore the new edge and keep the original tree.";
            }
        }
        ++itr;
    }
    

    if(!case1){
        edge<int> mostExpensiveEdge = G.DFS(uVertex, vVertex);
        if(mostExpensiveEdge.weight < newEdge.weight){
            cout << "The new edge will make the spanning tree more expensive. Should ignore the new edge and keep the original tree.";
        }
        else if(mostExpensiveEdge.weight > newEdge.weight){
            cout << "The new edge will make the spanning tree cheaper. Should use the new edge and drop the original edge between " << mostExpensiveEdge.u << " and " << mostExpensiveEdge.v;
        }
        else{
            cout << "The new edge does not make the tree cheaper. Should ignore the new edge and keep the original tree.";
        }
    }

    return 0;
}
