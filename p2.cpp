#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <cstdio>

using namespace std;

class MakeSet
{
	int *p;
	int *rank;

public:
	MakeSet(int n)
	{
		p = (int*) malloc(n * sizeof(int));
		rank = (int*) malloc(n * sizeof(int));

		for (int i = 1; i < n; i++)
		{
			p[i] = i;
			rank[i] = 0;
		}
	}

	int FindSet(int u)
	{
		if (p[u] != u)
		{
			p[u] = FindSet(p[u]);
		}
		return p[u];
	}

	void Link(int u, int v)
	{
		if (rank[u] > rank[v]) {
			p[v] = u;
		} else{
			p[u] = v;
			if (rank[u] == rank[v]) {
				rank[v] = rank[v] + 1;
			}
		}
	}

	void Union(int u, int v)
	{
		Link(FindSet(u), FindSet(v));
	}

	~MakeSet()
	{
		free(p);
		free(rank);
	}
};

class Graph
{
	vector<array<int, 3>> edges;
	int V;

public:
	Graph(int V)
	{
		this->V = V;
	}

	void addEdge(int u, int v, int w)
	{
		edges.push_back({u, v, -w});
	}

	void fillGraph(int e)
	{
		for (int a = 0; a < e; a++)
		{
			int u, v, w;
			if (scanf("%d%d%d", &u, &v, &w) == 0)
			{
				break;
			}
			addEdge(u, v, w);
		}
	}

	int MSTKruskal()
	{
		sort(edges.begin(), edges.end(), [](const array<int, 3> &w1, const array<int, 3> &w2)
				 { return w1[2] < w2[2]; });
		MakeSet set(V + 1);
		int ans = 0;
		for (array<int, 3> edge : edges)
		{
			int u = edge[0];
			int v = edge[1];
			int w = edge[2];
			if (set.FindSet(u) != set.FindSet(v))
			{
				set.Union(u, v);
				ans += w;
			}
		}

		return ans;
	}
};

int main()
{
	int V;
	int E;
	if (scanf("%d", &V) == 0)
	{
		return 0;
	}
	if (scanf("%d", &E) == 0)
	{
		return 0;
	}
	Graph G(V);
	G.fillGraph(E);
	int ans = G.MSTKruskal();
	printf("%d\n", abs(ans));
	return 0;
}