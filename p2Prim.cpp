#include <iostream>
#include <cstring>
using namespace std;


class Graph {
   private:
  int** adjMatrix;
  int V;

   public:
  Graph(int V) {
    this->V = V;
    adjMatrix = new int*[V];
    for (int i = 0; i < V; i++) {
      adjMatrix[i] = new int[V];
      for (int j = 0; j < V; j++)
        adjMatrix[i][j] = 0;
    }
  }

  void addEdge(int u, int v, int w) {
    adjMatrix[u-1][v-1] = w;
    adjMatrix[v-1][u-1] = w;
  }

  int findMaxVertex(bool visited[], int weights[])
  {

    int index = -1;
    int maxW = -300000000;
    for (int i = 0; i < V; i++) {
      if (visited[i] == false && weights[i] > maxW) {

        maxW = weights[i];
        index = i;
      }
    }
    return index;
  }

  int maximumSpanningTree()
  {

    bool visited[V];
    int weights[V];
    int parent[V];
    for (int i = 0; i < V; i++) {
      visited[i] = false;
      weights[i] = -300000000;
    }
    weights[0] = 300000000;
    parent[0] = -1;
    for (int i = 0; i < V - 1; i++) {
      int maxVertexIndex = findMaxVertex(visited, weights);
      visited[maxVertexIndex] = true;
      for (int j = 0; j < V; j++) {
        if (adjMatrix[j][maxVertexIndex] != 0 && visited[j] == false) {
          if (adjMatrix[j][maxVertexIndex] > weights[j]) {
            weights[j] = adjMatrix[j][maxVertexIndex];
            parent[j] = maxVertexIndex;
          }
        }
      }
    }
    
    int MST = 0;

    for (int i = 1; i < V; i++) {

      MST += adjMatrix[i][parent[i]];
    }
    return MST;
  }

  ~Graph() {
    for (int i = 0; i < V; i++)
      delete[] adjMatrix[i];
    delete[] adjMatrix;
  }
};

Graph fillGraph(int v, int e){
  Graph g(v);
	for (int a = 0; a < e; a++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g.addEdge(u, v, w);
	}
	return g;
}

int main() {
  int V;
	int E;
	cin >> V >> E;
  Graph g = fillGraph(V, E);
  int a = g.maximumSpanningTree();
  cout << a << endl;

}

