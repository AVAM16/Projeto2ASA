#include <vector>
#include <iostream>

using namespace std;

unsigned int V, E;

void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt)
{
  adj[u].push_back(make_pair(v, wt));
  adj[v].push_back(make_pair(u, wt));
}

void readVE(){
  cin >> V >> E;
}

void readGraph(vector <pair<int, int> > adj[]){
  for (int a = 0; a < E; a++){
    int u, v, wt;
    cin >> u >> v >> wt;
    addEdge(adj, u, v, wt);
  }
}

int main(){
  readVE();
  vector <pair<int, int> > adj[V];
  readGraph(adj);
  return 0;
}