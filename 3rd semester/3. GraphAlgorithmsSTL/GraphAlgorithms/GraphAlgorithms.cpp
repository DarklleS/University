#include <iostream>
#include <vector>
#include <queue>

#define INF INT_MAX

using namespace std;

template<class T>
class Graph
{
public:
    Graph() : _size(0) {}

    Graph(const size_t& size) : _size(size)
    {
        _matrix.resize(size, vector<T>(size));
    }

    Graph(const vector<vector<T>>& matrix) :
        _size(matrix.size()),
        _matrix(matrix) {}

    vector<vector<T>> mst()
    {
        _matrixMST.resize(_size, vector<T>(_size));
        vector<int> parent(_size);
        vector<int> value(_size, INF);
        vector<bool> setMST(_size);

        parent[0] = -INF;
        value[0] = 0;

        for (size_t i = 0; i < _size - 1; ++i)
        {
            int min = INT_MAX;
            unsigned node;

            for (size_t i = 0; i < _size; ++i)
            {
                if (!setMST[i] && value[i] < min)
                {
                    node = i;
                    min = value[i];
                }
            }

            setMST[node] = true;

            for (size_t j = 0; j < _size; ++j)
            {
                if (_matrix[node][j] && !setMST[j] && _matrix[node][j] < value[j])
                {
                    value[j] = _matrix[node][j];
                    parent[j] = node;
                }
            }
        }

        cout << "Weight of MST: " << _outputMST(parent) << endl << endl;

        return _matrixMST;
    }

    vector<unsigned> dfs(const unsigned& source)
    {
        vector<bool> used(_size);
        vector<unsigned> result;

        _dfs(source, used, result);

        cout << "DFS travel: ";

        for (auto i : result)
            cout << i << " ";
            
        cout << endl << endl;

        return result;
    }

    vector<pair<unsigned, T>> dijkstra(const unsigned& source)
    {
        vector<T> distance(_size, INF);
        vector<int> used(_size);
        vector<pair<unsigned, int>> result(_size);
        distance[source] = 0;

        for (size_t i = 0; i < _size; ++i)
        {
            T min = INF;
            unsigned index;

            for (size_t j = 0; j < _size; ++j)
            {
                if (!used[j] && distance[j] <= min)
                {
                    min = distance[j];
                    index = j;
                }
            }

            used[index] = true;

            for (int j = 0; j < _size; ++j)
            {
                if (!used[j] && _matrix[index][j] && distance[index] != INF && distance[index] + _matrix[index][j] < distance[j])
                    distance[j] = distance[index] + _matrix[index][j];
            }
        }

        return _outputDijkstra(source, distance);
    }

    unsigned degree() 
    {
        vector<unsigned> result = _bfs();
        double avg = 0;

        for (size_t i = 0; i < _size; ++i)
            avg += result[i];

        avg /= _size;

        cout << "Verteces|     Degree" << endl
             << "--------|--------------------------------" << endl;

        for (size_t i = 0; i < _size; ++i)
        {
            cout << i << "\t|\t" << result[i] << endl;
        }

        cout << "-----------------------------------------" << endl;
        cout << "Average degree: " << avg;

        return avg;
    }

private:
    size_t _size; // Поле со значением размера матрицы
    vector<vector<T>> _matrix; // Матрица смежности
    vector<vector<T>> _matrixMST; // Матрица минимального оставного дерева

    void _dfs(const unsigned& source, vector<bool>& used, vector<unsigned>& result)
    {
        result.push_back(source);
        used[source] = true;

        for (size_t i = 0; i < _size; i++)
        {
            if (_matrixMST[source][i] && !used[i])
                _dfs(i, used, result);
        }
    }

    unsigned _minVertex(vector<int>& value, vector<bool>& setMST)
    {
        int min = INT_MAX;
        unsigned vertex;

        for (size_t i = 0; i < _size; ++i)
        {
            if (!setMST[i] && value[i] < min)
            {
                vertex = i;
                min = value[i];
            }
        }

        return vertex;
    }

    int _outputMST(const vector<int>& parent) 
    {
        int weightMST = 0;

        cout << "     Verteces\t\t|     Weight" << endl
             << "------------------------|----------------" << endl;

        for (size_t i = 1; i < _size; ++i)
        {
            cout << parent[i] << "\t-\t" << i << "\t|\t" << _matrix[parent[i]][i] << endl;

            weightMST += _matrix[parent[i]][i];

            _matrixMST[parent[i]][i] = _matrix[parent[i]][i];
            _matrixMST[i][parent[i]] = _matrix[i][parent[i]];
        }

        cout << "-----------------------------------------" << endl;
        cout << "Matrix of MST: " << endl;
        cout << "-----------------------------------------" << endl;

        for (size_t i = 0; i < _size; ++i)
        {
            for (size_t j = 0; j < _size; ++j)
            {
                if (j == 0)
                    cout << "| ";

                cout << _matrixMST[i][j] << " ";

                if (j == _size - 1)
                    cout << "|";
            }

            cout << endl;
        }
        cout << "-----------------------------------------" << endl;

        return weightMST;
    }

    vector<pair<unsigned, T>> _outputDijkstra(const unsigned& source, const vector<int>& distance) 
    {
        vector<pair<unsigned, T>> result(_size);
        cout << "Verteces|"
             << "Distance from " << source << endl
             << "--------|--------------------------------" << endl;

        for (int i = 0; i < _size; ++i)
        {
            result[i] = pair<unsigned, int>(i, distance[i] != INF ? distance[i] : 0);
            cout << result[i].first << "\t|\t" << result[i].second << endl;
        }

        return result;
    }

    vector<unsigned> _bfs() // Метод реализация подсчета степени вершин дерева с помощью поиска в ширину
    {
        vector<bool> used(_size);
        queue<unsigned> q;
        vector<unsigned> result(_size);

        used[0] = true;
        q.push(0);

        while (!q.empty())
        {
            unsigned node = q.front();
            unsigned count = 0;

            q.pop();

            for (size_t i = 0; i < _size; ++i)
            {
                if (_matrixMST[i][node])
                {
                    count++;

                    if (!used[i])
                    {
                        used[i] = true;
                        q.push(i);
                    }
                }
            }

            result[node] = count;
        }

        return result;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    vector<vector<int>> matrix = 
    {
        { 0, 9, 7, 9, 6, 9, 5, 5, 6, 3, 6 },
        { 9, 0, 2, 3, 7, 6, 5, 6, 7, 7, 0 },
        { 7, 2, 0, 5, 0, 0, 6, 8, 0, 5, 6 },
        { 9, 3, 5, 0, 6, 2, 5, 1, 1, 2, 2 },
        { 6, 7, 0, 6, 0, 0, 1, 0, 5, 8, 3 },
        { 9, 6, 0, 2, 0, 0, 4, 2, 8, 3, 0 },
        { 5, 5, 6, 5, 1, 4, 0, 5, 9, 7, 4 },
        { 5, 6, 8, 1, 0, 2, 5, 0, 9, 2, 6 },
        { 6, 7, 0, 1, 5, 8, 9, 9, 0, 1, 0 },
        { 3, 7, 5, 2, 8, 3, 7, 2, 1, 0, 4 },
        { 6, 0, 6, 2, 3, 0, 4, 6, 0, 4, 0 }
    };

    Graph<int> graph(matrix);

    {
        cout << "|----------------------------------------|" << endl;
        cout << "|============= ЗАДАНИЕ 3.1. =============|" << endl;
        cout << "|----------------------------------------|" << endl;

        vector<vector<int>> mst = graph.mst();
    }

    {
        cout << "|----------------------------------------|" << endl;
        cout << "|============= ЗАДАНИЕ 3.2. =============|" << endl;
        cout << "|----------------------------------------|" << endl;

        vector<unsigned> dfs = graph.dfs(0);
    }

    {
        cout << "|----------------------------------------|" << endl;
        cout << "|============= ЗАДАНИЕ 3.3. =============|" << endl;
        cout << "|----------------------------------------|" << endl;

        vector<pair<unsigned, int>> dijkstra = graph.dijkstra(10);
    }

    {
        cout << "|----------------------------------------|" << endl;
        cout << "|============= ЗАДАНИЕ 3.4. =============|" << endl;
        cout << "|----------------------------------------|" << endl;

        double degree = graph.degree();
    }

    cout << endl;

    return 0;
}