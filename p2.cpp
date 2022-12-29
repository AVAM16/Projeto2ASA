#include<algorithm>
#include <iostream>
#include <vector>
#include <array>

using namespace std;

class MakeSet
{
	int *parent;
	int *rank;

public:
	MakeSet(int n)
	{
		parent = new int[n];
		rank = new int[n];

		for (int i = 0; i < n; i++)
		{
			parent[i] = -1;
			rank[i] = 1;
		}
	}

	int FindSet(int i)
	{
		if (parent[i] == -1)
		{
			return i;
		}
		return parent[i] = FindSet(parent[i]);
	}

	void Union(int u, int v)
	{
		int s1 = FindSet(u);
		int s2 = FindSet(v);

		if (s1 != s2)
		{
			if (rank[s1] < rank[s2])
			{
				parent[s1] = s2;
			}
			else if (rank[s1] > rank[s2])
			{
				parent[s2] = s1;
			}
			else
			{
				parent[s2] = s1;
				rank[s1] += 1;
			}
		}
	}
};

class Graph
{
	vector<array<int, 3>> edgelist;
	int V;

public:
	Graph(int V)
	{
		this->V = V;
	}

	void addEdge(int u, int v, int w)
	{
		edgelist.push_back({u, v, w});
	}

	int MSTKruskal()
	{
		sort(edgelist.begin(), edgelist.end(), [](const array<int, 3> &w1, const array<int, 3> &w2)
				 { return w1[2] > w2[2]; });
		MakeSet s(V);
		int ans = 0;
		for (array<int, 3> edge : edgelist)
		{
			int u = edge[0];
			int v = edge[1];
			int w = edge[2];
			if (s.FindSet(u) != s.FindSet(v))
			{
				s.Union(u, v);
				ans += w;
			}
		}

		return ans;
	}
};

Graph fillGraph(int v, int e)
{
	Graph g(v);
	for (int a = 0; a < e; a++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g.addEdge(u, v, w);
	}
	return g;
}

int main()
{
	int V;
	int E;
	cin >> V >> E;
	Graph G = fillGraph(V, E);
	int ans = G.MSTKruskal();
	cout << ans << endl;
	return 0;
}
