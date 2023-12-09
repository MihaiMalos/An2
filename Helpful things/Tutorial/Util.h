#pragma once

#include <vector>
#include <fstream>

using namespace std;


template <typename T>
vector<vector<T>> ReadMatrix(std::string fileName)
{

	ifstream fin(fileName);
	int rows, columns;
	fin >> rows >> columns;

	vector<vector<T>> matrix(rows);

	for (int row = 0; row < rows; row++)
	{
		matrix[row].resize(columns);

		for (int column = 0; column < columns; column++)
		{
			fin >> matrix[row][column];
		}
	}

	return matrix;
}

template <typename T>
void DisplayMatrix(vector<vector<T>> matrix) 
{
	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix[0].size(); column++)
		{
			cout << matrix[row][column] << " ";
		}
		cout << endl;
	}
}

vector<vector<int>> Eye(int n)
{
	vector<vector<int>> matrix(n);

	for (int row = 0; row < n; row++)
	{
		matrix[row].resize(n);
	}

	for (int index = 0; index < n; index++)
	{
		matrix[index][index] = 1;
	}

	return matrix;
}
