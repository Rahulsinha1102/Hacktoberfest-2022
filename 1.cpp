/*#include <bits/stdc++.h>
using namespace std;

long int fastPower(int a, int b)
{
	long int res = 1;
	while(b > 0)
	{
		if(b & 1 == 1) res *= a;
		a = a * a;
		b = b >> 1;
	}
	return res;
}

int maxSubArraySum(vector<int> &a,int start, int end)
{
    int max_so_far = INT_MIN, max_ending_here = 0, s = 0;
 
    for (int i = start; i <= end; i++) {
        cout << a[i] << ":" ;
        max_ending_here += a[i];
 
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
 
        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
        cout << max_ending_here << endl;
    }
    return max_so_far;
}

int sum(vector<int> &arr, int n, int k)
{
	int ans = INT_MIN, max = INT_MIN;
	for(int i = 0; i<n-k; i++)
	{
		max = (arr, i, i+k);
		if(max > ans) ans = max;
	}
	return ans;
}

int secondLargest(vector<int> arr, int n)
{
	int largest = INT_MIN, sLargest = INT_MIN;
	for(int i = 0; i<n; i++)
	{
		if(arr[i] > largest)
		{
			sLargest = largest;
			largest = arr[i];

		}
		else if((arr[i] > sLargest) && (arr[i] < largest))
		{
			sLargest = arr[i];
		}
		cout << largest << " " << sLargest << endl;
	}
	return sLargest;
}

void rshift(vector<int> &arr, int n)
{
	n = n % arr.size();
	while(n--)
	{
		int prev = arr[arr.size()-1], next = arr[0];
		for(int i = 0; i<arr.size(); i++)
		{
			next = arr[i];
			arr[i] = prev;
			prev = next;
		}
	}
}
*/
//Vaishnavi

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


/*int main()
{
		
	#ifndef ONLINE_JUDGE
	freopen("input1.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
	#endif 

	vector<int> arr = {1,2,3,4,5,6,7,8,9,0};
	/*int max = INT_MIN, sum = 0;
	for(int i : arr)
	{
		sum += i;
		if(sum > max) max = sum;
		if(sum < 0) sum = 0;
	}
	cout << max;

	int x,y;
	cin>>x>>y;
	rshift(arr, 109);
	//cout << "Ans is: " << x;
    for(int i : arr)
	{
		cout << i << " ";
	}
    return 0;
 }
*/