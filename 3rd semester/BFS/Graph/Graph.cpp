#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;
    size_t size;
    vector<vector<int>> matrix;
    vector<int> used;
    queue<int> q;
    int start, end, front;

    fin.open("input.txt");
    fout.open("output.txt");

    fin >> size;

    used.resize(size);
    matrix.resize(size, vector<int>(size));

    for (size_t i = 0; i < size; ++i)
    {
        used[i] = INT_MAX;

        for (size_t j = 0; j < size; ++j)
            fin >> matrix[i][j];
    }

    fin >> start >> end;

    start--;
    end--;

    used[start] = 0;

    q.push(start);

    while (!q.empty())
    {
        front = q.front();
        q.pop();

        for (size_t i = 0; i < size; ++i)
        {
            if (matrix[front][i] && used[i] > used[front] + 1)
            {
                used[i] = used[front] + 1;
                q.push(i);
            }
        }
    }

    if (used[end] < INT_MAX)
        fout << used[end];
    else
        fout << -1;

    fin.close();
    fout.close();

    return 0;
}


