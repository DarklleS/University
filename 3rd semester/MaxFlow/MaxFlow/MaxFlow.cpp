#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

bool BFS(const vector<vector<int>>& matrix, int s, int t, vector<int>& parent)
{
    vector<bool> used(matrix.size());
    queue<int> q;

    q.push(s);
    used[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int f = q.front();
        q.pop();

        for (int i = 0; i < matrix.size(); ++i)
            if (!used[i] && matrix[f][i] > 0)
            {
                q.push(i);
                parent[i] = f;
                used[i] = true;
            }
    }

    return used[t];
}

int fordFulkerson(const vector<vector<int>>& matrix, int s, int t)
{
    vector<vector<int>> rMatrix = matrix;
    vector<int> parent(matrix.size());
    int maxFlow = 0;


    while (BFS(rMatrix, s, t, parent))
    {
        int pathFlow = INT_MAX;

        for (int i = t; i != s; i = parent[i])
        {
            int f = parent[i];
            pathFlow = min(pathFlow, rMatrix[f][i]);
        }

        for (int i = t; i != s; i = parent[i])
        {
            int f = parent[i];
            rMatrix[f][i] -= pathFlow;
            rMatrix[i][f] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    ifstream fin;
    ofstream fout;
    size_t size;
    vector<vector<int>> matrix;

    fin.open("input.txt");
    fout.open("output.txt");

    fin >> size;

    matrix.resize(size, vector<int>(size));

    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            fin >> matrix[i][j];

    cout << "Max Flow: " << fordFulkerson(matrix, 0, 1);
}
