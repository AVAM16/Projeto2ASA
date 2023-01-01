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
			p[i] = -1;
			rank[i] = 1;
		}
	}

	int FindSet(int i)
	{
		if (p[i] == -1)
		{
			return i;
		}
		return p[i] = FindSet(p[i]);
	}

	void Union(int u, int v)
	{
		int set1 = FindSet(u);
		int set2 = FindSet(v);

		if (set1 != set2)
		{
			if (rank[set1] < rank[set2])
			{
				p[set1] = set2;
			}
			else if (rank[set1] > rank[set2])
			{
				p[set2] = set1;
			}
			else
			{
				p[set2] = set1;
				rank[set1] += 1;
			}
		}
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