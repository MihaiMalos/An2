#include "DisjointSet.h"

DisjointSet::DisjointSet(int n)
{
	parent.resize(n);
	rank.resize(n);
	for (int index = 0; index < n; index++)
	{
		parent[index] = index;
		rank[index] = 0;
	}
}

int DisjointSet::Find(int node)
{
	int root = node;
	while (parent[root] != root)
		root = parent[root];

	while (node != root)
	{
		int next = parent[node];
		parent[node] = root;
		node = next;
	}

	return root;
}

void DisjointSet::Merge(int x, int y)
{
	x = Find(x);
	y = Find(y);
	if (x != y) {
		if (rank[x] < rank[y])
			std::swap(x, y);
		parent[y] = x;
		if (rank[x] == rank[y])
			rank[x]++;
	}
}
