
// A C++ program to find single source longest distances
// in a DAG
#include <bits/stdc++.h>
#define NINF INT_MIN
using namespace std;

class AdjListNode {
	int v;
	int weight;

public:
	AdjListNode(int _v, int _w)
	{
		v = _v;
		weight = _w;
	}
	int getV() { return v; }
	int getWeight() { return weight; }
};


class Graph {
	int V; 

	list<AdjListNode>* adj;

	void topologicalSortUtil(int v, bool visited[],
							stack<int>& Stack);

public:
	Graph(int V); // Constructor
	~Graph(); // Destructor

	void addEdge(int u, int v, int weight);

	void longestPath(int s);
};

Graph::Graph(int V) // Constructor
{
	this->V = V;
	adj = new list<AdjListNode>[V];
}

Graph::~Graph() // Destructor
{
	delete [] adj;
}


void Graph::addEdge(int u, int v, int weight)
{
	AdjListNode node(v, weight);
	adj[u].push_back(node); // Add v to u's list
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
	visited[v] = true;
	list<AdjListNode>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		AdjListNode node = *i;
		if (!visited[node.getV()])
			topologicalSortUtil(node.getV(), visited, Stack);
	}

	Stack.push(v);
}

void Graph::longestPath(int s)
{
	stack<int> Stack;
	int dist[V];

	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	for (int i = 0; i < V; i++)
		dist[i] = NINF;
	dist[s] = 0;
	while (Stack.empty() == false) {
		int u = Stack.top();
		Stack.pop();
		list<AdjListNode>::iterator i;
		if (dist[u] != NINF) {
			for (i = adj[u].begin(); i != adj[u].end(); ++i){
			
				if (dist[i->getV()] < dist[u] + i->getWeight())
					dist[i->getV()] = dist[u] + i->getWeight();
			}
		}
	}

	for (int i = 0; i < V; i++)
		(dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";
	
	delete [] visited;
}

// Driver program to test above functions
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input1.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
	#endif 
	Graph g(6);
	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 5);
	g.addEdge(1, 5, 2);
	g.addEdge(1, 2, 2);
	g.addEdge(2, 4, 1);
	g.addEdge(2, 3, 1);
	g.addEdge(2, 1, -3);
	g.addEdge(4, 5, -4);
	g.addEdge(4, 3, -1);
	g.addEdge(5, 4, 4);

	int s = 0;
	cout << "Following are longest distances from "
			"source vertex "
		<< s << " \n";
	g.longestPath(s);

	return 0;
}
