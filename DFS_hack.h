#include <string>
#include <list>
#include <map>
#include <fstream>

#define INFINITY 100000

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
	std::list<edge<T>> edges;

	vertex() {}
	vertex(const T& v) { key = v; c = white; d = INFINITY; p = NULL; }
};

template <typename T> class edge
{
public:
	vertex *u, *v;
	int weight;

	edge(vertex* a,vertex* b,int w)
	{
		u = a; v = b; weight = w;
	}
};

template <typename T> class graph
{
public:
	graph(const std::string& fileName);
	~graph();

	void DFS(const vertex<T> *u, const vertex<T> *v);
    edge<T> DFS_Visit(const vertex<T> *u, const vertex<T> *v);
private:
	// Since the edges are stored in the vertices, we only need
	// a list of vertices in the graph. For convenience, this is
	// stored as a map.
	std::map<T,vertex<T>*> V;
};

template <typename T>
graph<T>::graph(const std::string& filename)
{
	std::ifstream in;
    in.open("graph.txt");
    
    int nV;
    in >> nV;
    int key;
        
    for(int n = 0;n < nV;n++) {
        in >> key;
        V[key] = new vertexOG(key);
    }
    
    int nE;
    in >> nE;
    int from, to, w;
    for(int n = 0;n < nE;n++) {
        in >> from >> to >> w;
        vertexOG *u = V[from];
        vertexOG *v = V[to];
        u->edges.push_back(edgeOG(u, v, w));
        v->edges.push_back(edgeOG(v, u, w));
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
void graph<T>::DFS(const vertex<T> *u, const vertex<T> *v) {
    auto itr = V.begin();
    while (itr != V.end()) {
        itr->visited = false;
        ++itr;
    }
    DFS_Visit(u, v);
}

template <typename T>
edge<T> graph<T>::DFS_Visit(const vertex<T> *u, const vertex<T> *v){
    u->visited = true;
    if (u == v){
        return edge<T>(u->prev,u,u->w);
    }
    edge<T> winner;
    winner.weight = 0;
    for (auto itr = u->edges.begin();itr != u->edges.end();itr++) {
        if (itr->v->visted == false){
            // check if you went to the same edge you came from
            if (itr->v == u->prev){
                continue;
            }
            edge<T> currentEdge = DFS_Visit(itr, v);
            if(currentEdge.weight > winner.weight)
                winner = currentEdge;
        }
    }
    return winner;
}
