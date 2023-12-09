#pragma once

#include <vector>

class DisjointSet {

public:
	DisjointSet(int n);
	int Find(int node);
	void Merge(int x, int y);

private:
	std::vector<int> parent, rank;
};