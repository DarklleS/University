#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

#define INF INT_MAX

using namespace std;

typedef unsigned int Vertex;

template<class T>
struct Edge
{
    Vertex source;
    Vertex target;
    T capacity;
    T flow;

    Edge() : 
        source(0),
        target(0),
        capacity(0),
        flow(0) {}

    Edge(const Vertex& source, const Vertex& target, const T& capacity) :
        source(source),
        target(target),
        capacity(capacity),
        flow(capacity) {}

    Edge(const Edge<T>& edge) :
        source(edge.source),
        target(edge.target),
        capacity(edge.capacity),
        flow(edge.capacity) {}

    template<class T> friend ostream& operator<< (ostream&, const Edge<T>&);
    template<class T> friend istream& operator>> (istream&, Edge<T>&);
};

template<class T> 
ostream& operator<< (ostream& ustream, const Edge<T>& obj)
{
    ustream << obj.weight;

    return ustream;
}

template<class T>
istream& operator>> (istream& ustream, Edge<T>& obj)
{
    ustream >> obj.source >> obj.target >> obj.weight;

    return ustream;
}

template<class T>
class Graph
{
public:
    Graph() : _size(0) {}

    Graph(const size_t& size) : _size(size)
    {
        _matrix.resize(_size, vector<Edge<T>>(_size));
        _parent.resize(_size);
        _level.resize(_size);
    }

    Graph(const vector<vector<Edge<T>>>& matrix) :
        _size(matrix.size()),
        _matrix(matrix)
    {
        _parent.resize(_size);
        _level.resize(_size);
    }

    Graph(const Graph<T>& graph) :
        _size(graph._size),
        _matrix(graph._matrix),
        _parent(graph._parent),
        _level(graph._level) {}

    void addEdge(const Edge<T>& edge) // Метод добавления ребра в матрицу смежности
    {
        if (edge.source >= 0 && edge.target >= 0) // Проверка на корректность введенных данных
        {
            if (edge.source >= _size || edge.target >= _size) // Проверка размера матрицы смежности
            {
                _size = max(edge.source, edge.target) + 1; // Устанавливаем новый размер

                for (size_t i = 0; i < _size; ++i)
                {
                    if (_matrix.size() > i)
                        _matrix[i].resize(_size); // Увеличиваем размер строчки матрицы смежности
                    else
                        _matrix.resize(_size, vector<Edge<T>>(_size)); // Увеличиваем кол-во строчек матрицы смежности
                }
            }

            _matrix[edge.source][edge.target] = edge; // Вставка добавляемого элемента в матрицу смежности
            _parent.resize(_size);
            _level.resize(_size);
        }
    }

    T bfs(const Vertex& source, const Vertex& target) // Реализация алгоритма поиска в ширину
    {
        T flow = INF; // Переменная счета потока на найденном пути
        queue<unsigned> q;

        fill(_parent.begin(), _parent.end(), -INF);
        fill(_level.begin(), _level.end(), -INF);
        _parent[source] = 0;
        _level[source] = 0;
        q.push(source);

        while (!q.empty())
        {
            Vertex node = q.front();
            q.pop();

            for (Edge<T> next : _matrix[node])
            {
                if (_parent[next.target] == -INF && _level[next.target] == -INF && _matrix[node][next.target].flow && next.flow)
                {
                    _parent[next.target] = node;
                    _level[next.target] = _level[node] + 1;

                    T newFlow = min(flow, _matrix[node][next.target].flow);

                    if (next.target == target)
                        return newFlow;

                    q.push(next.target);
                    flow = newFlow;
                }
            }
        }

        return 0;
    }

    T dfs(const Vertex& source, const Vertex& target, T flow) // Реализация алгоритма поиска в глубину / Вычисление потока в остаточной сети на найденном пути
    {
        if (source == target)
            return flow;

        for (size_t i = 0; i < _size; i++)
        {
            if (_matrix[source][i].flow && _level[source] < _level[_matrix[source][i].target])
            {
                if (T newFlow = dfs(_matrix[source][i].target, target, min(flow, _matrix[source][i].flow)))
                {
                    _matrix[source][i].flow -= newFlow;
                    _matrix[i][source].flow += newFlow;

                    return newFlow;
                }
            }
        }

        return 0;
    }

    T fordFulkerson(const Vertex& source, const Vertex& target) // Реализация алгоритма Форда-Фалкерсона
    {
        T maxFlow = 0;

        while (bfs(source, target))
        {
            T pathFlow = INF;

            for (size_t i = target; i != source; i = _parent[i])
            {
                Vertex node = _parent[i];

                pathFlow = min(pathFlow, _matrix[node][i].flow);
            }

            for (size_t i = target; i != source; i = _parent[i])
            {
                Vertex node = _parent[i];

                _matrix[node][i].flow -= pathFlow;
                _matrix[i][node].flow += pathFlow;
            }

            maxFlow += pathFlow;
        }

        _updateFlow();

        return maxFlow;
    }

    T edmondsKarp(const Vertex& source, const Vertex& target) // Реализация алгоритма Эдмондса-Карпа
    {
        T maxFlow = 0;

        while (T flow = bfs(source, target))
        {
            maxFlow += flow;

            Vertex curNode = target;

            while (curNode != source)
            {
                Vertex prevNode = _parent[curNode];

                _matrix[prevNode][curNode].flow -= flow;
                _matrix[curNode][prevNode].flow += flow;

                curNode = prevNode;
            }
        }

        _updateFlow();

        return maxFlow;
    }

    T dinic(const Vertex& source, const Vertex& target)
    {
        T flow = 0;

        while (bfs(source, target))
        {
            while (T newFlow = dfs(source, target, INF))
            {
                flow += newFlow;
            }
        }

        _updateFlow();

        return flow;
    }

    Graph& operator= (const Graph<T>& obj)
    {
        _size = obj._size;
        _matrix = obj._matrix;

        return *this;
    }

    Graph& operator= (const vector<vector<T>>& temp)
    {
        _size = temp.size();
        _matrix = temp;

        return *this;
    }

    template<class T> friend ostream& operator<< (ostream& ustream, const Graph<T>& obj);

    template<class T> friend istream& operator>> (istream& ustream, Graph<T>& obj);

private:
    size_t _size; // Поле со значением размера матрицы
    vector<vector<Edge<T>>> _matrix; // Матрица смежности ориентированный графа
    vector<int> _parent;
    vector<int> _level;

    void _updateFlow() // Метод обновления матрицы остаточной сети
    {
        for (size_t i = 0; i < _size; ++i)
        {
            for (size_t j = 0; j < _size; ++j)
            {
                _matrix[i][j].flow = _matrix[i][j].capacity;
            }
        }
    } 
};

template<class T>
ostream& operator<< (ostream& ustream, const Graph<T>& obj)
{
    for (size_t i = 0; i < obj._size; ++i)
    {
        for (size_t j = 0; j < obj._size; ++j)
        {
            ustream << obj._matrix[i][j].capacity;
            
            if (j != obj._size - 1)
                ustream << "\t";
        }

        if (i != obj._size - 1)
            ustream << endl;
    }

    return ustream;
}

template<class T>
istream& operator>> (istream& ustream, Graph<T>& obj)
{
    Edge<T> edge;

    ustream >> edge;
    obj.addEdge(edge);

    return ustream;
}

template<class T>
void result(const vector<Edge<T>>& matrix, const Vertex& source, const Vertex& target)
{
    Graph<T> graph;

    for (auto i : matrix)
        graph.addEdge(i);

    cout << endl << "------------------------------------------------------------" << endl;

    cout << graph;

    cout << endl << "------------------------------------------------------------" << endl;

    cout << "Max flow (Ford-Fulkerson):\t" << graph.fordFulkerson(source, target) << endl << endl
         << "Max flow (Edmonds-Karp):\t" << graph.edmondsKarp(source, target) << endl << endl 
         << "Max flow (Dinic):\t\t" << graph.dinic(source, target);

    cout << endl;
}

int main()
{
    vector<Edge<int>> intEdges =
    {
        Edge<int>(0, 1, 19),
        Edge<int>(0, 2, 5),
        Edge<int>(0, 3, 11),
        Edge<int>(1, 0, 4),
        Edge<int>(1, 2, 18),
        Edge<int>(2, 0, 13),
        Edge<int>(2, 1, 9),
        Edge<int>(2, 3, 1),
        Edge<int>(3, 0, 3),
        Edge<int>(3, 1, 13),
        Edge<int>(3, 2, 14)
    };

    vector<Edge<double>> doubleEdges =
    {
        Edge<double>(0, 1, 22.943),
        Edge<double>(0, 3, 9.8433),
        Edge<double>(1, 0, 38.48943),
        Edge<double>(1, 3, 81.4878),
        Edge<double>(1, 6, 68.121),
        Edge<double>(2, 3, 31.9435),
        Edge<double>(3, 1, 25.31),
        Edge<double>(3, 5, 34.0),
        Edge<double>(5, 2, 566.92),
        Edge<double>(5, 3, 27.823),
        Edge<double>(4, 3, 13.2),
        Edge<double>(4, 5, 20.001),
        Edge<double>(4, 6, 93.6)
    };

    cout << "============================================================" << endl;
    cout << "Int Graph:";
    result(intEdges, 0, 1);
    cout << "============================================================" << endl;
    cout << "Double Graph:";
    result(doubleEdges, 1, 3);
    cout << "============================================================" << endl;
}
