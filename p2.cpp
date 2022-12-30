#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <cstdio>

using namespace std;

class MakeSet
{
	int *predecessor;
	int *rank;

public:
	MakeSet(int n)
	{
		predecessor = new int[n];
		rank = new int[n];

		for (int i = 0; i < n; i++)
		{
			predecessor[i] = -1;
			rank[i] = 1;
		}
	}

	int FindSet(int i)
	{
		if (predecessor[i] == -1)
		{
			return i;
		}
		return predecessor[i] = FindSet(predecessor[i]);
	}

	void Union(int u, int v)
	{
		int s1 = FindSet(u);
		int s2 = FindSet(v);

		if (s1 != s2)
		{
			if (rank[s1] < rank[s2])
			{
				predecessor[s1] = s2;
			}
			else if (rank[s1] > rank[s2])
			{
				predecessor[s2] = s1;
			}
			else
			{
				predecessor[s2] = s1;
				rank[s1] += 1;
			}
		}
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
		MakeSet s(V + 1);
		int ans = 0;
		for (array<int, 3> edge : edges)
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