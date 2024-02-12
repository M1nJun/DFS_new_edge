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
    int w;
	std::list<vertex<T>*> edges;

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

	void dfs(const vertex<T> *u, const vertex<T> *v)
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
	in.open(filename.c_str());
	
	int vertex_count = 0;
	in >> vertex_count;
	for(int n = 0;n < vertex_count;n++) {
		T key;
		in >> key;
		V[key] = new vertex<T>(key);
	}

	int edge_count = 0;
	in >> edge_count;
	for(int n = 0;n < edge_count;n++) {
		T first, second;
		in >> first >> second;
		V[first]->edges.push_back(V[second]);
	}
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
void graph<T>::dfs(const vertex<T> *u, const vertex<T> *v) {

}
