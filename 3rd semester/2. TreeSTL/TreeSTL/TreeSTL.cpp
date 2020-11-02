#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>

using namespace std;

template<typename K, typename V>
void print(const map<K, V>& inputMap) // Функция вывода элементов контейнера map
{
    auto i = inputMap.begin();

    for (; i != inputMap.end(); ++i)
    {
        cout << "Key:\t" << i->first << endl
             << "Value:\t" << i->second;
        
        if (i != --inputMap.cend())
            cout << endl << "---------------" << endl;
    }

    cout << endl;
}

template<typename K, typename V>
bool findItem(const map<K, V>& inputMap, const K& key, const V& value) // Функция поиска элемента в контейнере map
{
    for (auto i : inputMap)
        if (i.first == key && i.second == value)
        {
            cout << "Item: ["
                 << "Key: " << key << " | "
                 << "Value: " << value
                 << "] - was found!";

            return true;
        }

    cout << "Item: ["
         << "Key: " << key << " | "
         << "Value: " << value
         << "] - was not found!";

    return false;
}

template<typename V>
bool threshold(const V& value) // Предикат проверки порога численности населения
{ 
    return value > 100;
}

template<typename K, typename V>
map<K, V> filter(const map<K, V>& inputMap, bool (*f)(const V&)) // Функция записи элементов контейнера map с определенным условием
{
    map<K, V> newMap;

    for (auto i : inputMap)
    {
        if (f(i.second))
            newMap[i.first] = i.second;
    }

    return newMap;
}

template<typename K, typename V>
class MapPriorityQueue // Класс реализации очереди с приоритетом
{
public:
    void push(map<K, V> inputMap)
    {
        for (auto i : inputMap)
        {
            if (_q.empty())
                _q.push_back(i);
            else
            {
                auto j = _q.cbegin();

                if (_q.back().second > i.second) // Если вводимый элемент меньше, чем последний элемент очереди
                    _q.push_back(i);
                else if (_q.front().second < i.second) // Если вводимый элемент больше, чем первый элемент очереди
                    _q.push_front(i);
                else
                {
                    for (; j != _q.cend(); ++j)
                    {
                        if (j->second < i.second)  // Если значение численности населения вводимого элемента больше, чем значение текущего элеманта очереди
                        {
                            _q.insert(j, i);

                            break;
                        }
                        else if (j->second == i.second) // Если значения численности населения элементов одинаковые
                        {
                            if (j->first < i.first) // Если имя вводимого элемента больше, чем имя текущего элеманта очереди
                                _q.insert(++j, i);
                            else if (j->first > i.first) // Если имя вводимого элемента мельше, чем имя текущего элеманта очереди
                                _q.insert(j, i);

                            break;
                        }
                    }
                }
            }
        }
    }

    void push(pair<K, V> inputPair)
    {
        if (_q.empty())
            _q.push_back(inputPair);
        else
        {
            auto j = _q.cbegin();

            if (_q.back().second > inputPair.second) // Если вводимый элемент меньше, чем последний элемент очереди
                _q.push_back(inputPair);
            else if (_q.front().second < inputPair.second) // Если вводимый элемент больше, чем первый элемент очереди
                _q.push_front(inputPair);
            else
            {
                for (; j != _q.cend(); ++j)
                {
                    if (j->second < inputPair.second)  // Если значение численности населения вводимого элемента больше, чем значение текущего элеманта очереди
                    {
                        _q.insert(j, inputPair);

                        break;
                    }
                    else if (j->second == inputPair.second) // Если значения численности населения элементов одинаковые
                    {
                        if (j->first < inputPair.first) // Если имя вводимого элемента больше, чем имя текущего элеманта очереди
                            _q.insert(++j, inputPair);
                        else if (j->first > inputPair.first) // Если имя вводимого элемента мельше, чем имя текущего элеманта очереди
                            _q.insert(j, inputPair);

                        break;
                    }
                }
            }
        }
    }

    void pop()
    {
        if (!_q.empty())
            _q.pop_front();
    }

    void print()
    {
        for (pair<K, V> i : _q)
        {
            cout << "Key:\t" << i.first << endl
                 << "Value:\t" << i.second;

            if (i != _q.back())
                cout << endl << "---------------" << endl;
        }

        cout << endl;
    }

    pair<K, V>* top() { return &_q.front(); }

private:
	list<pair<K, V>> _q;
};

template<class T>
struct Node
{
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
	T data;
	int height;

	Node<T>() :
		left(nullptr),
		right(nullptr),
		parent(nullptr),
		data(NULL),
		height(1) {}

	Node<T>(T data) :
		left(nullptr),
		right(nullptr),
		parent(nullptr),
		data(data),
		height(1) {}
};

template<class T>
class AVL_Tree
{
public:
	AVL_Tree() : _root(nullptr) {}

	Node<T>* getRoot() { return _root; }

	virtual void insert(T& key) { _insert(_root, new Node<T>(key)); }

	virtual void remove(T& key) { _remove(_root, key); }

	Node<T>* min() { return _min(_root); }

	Node<T>* max() { return _max(_root); }

	Node<T>* find(T& key)
	{
		if (!_root)
			return nullptr;

		Node<T>* current = _root;

		while (true)
		{
			if (key == current->data)
				return current;
			else if (!(current->left || current->right))
				return nullptr;

			if (key < current->data && current->left)
				current = current->left;
			else if (key > current->data && current->right)
				current = current->right;
			else
				return nullptr;
		}
	}

	void inorder() { _inorder(_root); }

	void preorder() { _preorder(_root); }

	void postorder() { _postorder(_root); }

protected:
	Node<T>* _root;

	Node<T>* _insert(Node<T>* current, Node<T>* node)
	{
		if (!current)
			current = node;

		if (!_root)
			_root = node;

		if (node->data < current->data && current)
		{
			current->left = _insert(current->left, node);
			current->left->parent = current;
		}
		else if (node->data > current->data && current)
		{
			current->right = _insert(current->right, node);
			current->right->parent = current;
		}

		return _balance(current);
	}

	Node<T>* _remove(Node<T>* current, T& key)
	{
		Node<T>* temp = current;

		if (!current)
			return nullptr;

		if (key < current->data)
			current->left = _remove(current->left, key);
		else if (key > current->data)
			current->right = _remove(current->right, key);

		if (key != current->data)
			return current;

		if (!current->left && !current->right && _root == current)
		{
			delete _root;
			_root = nullptr;

			return _root;
		}
		else if (!current->left)
		{
			if (_root == current)
			{
				current->right->parent = nullptr;
				_root = current->right;

				delete current;
				current = nullptr;

				return _root;
			}

			if (current->right)
				current->right->parent = current->parent;

			temp = current->right;

			delete current;
			current = nullptr;

			return temp;
		}
		else if (!current->right)
		{
			if (_root == current)
			{
				current->left->parent = nullptr;
				_root = current->left;

				delete current;
				current = nullptr;

				return _root;
			}

			if (current->left)
				current->left->parent = current->parent;

			temp = current->left;

			delete current;
			current = nullptr;

			return temp;
		}
		else
		{
			temp = _min(current->right);
			current->data = temp->data;
			current->right = _remove(current->right, temp->data);
		}

		return _balance(current);
	}

	Node<T>* _min(Node<T>* node)
	{
		Node<T>* current = node;

		while (current && current->left)
			current = current->left;

		return current;
	}

	Node<T>* _max(Node<T>* node)
	{
		Node<T>* current = node;

		while (current && current->right)
			current = current->right;

		return current;
	}

	void _inorder(Node<T>* node)
	{
		if (!node)
			return;

		_inorder(node->left);
		cout << node->data << " ";
		_inorder(node->right);
	}

	void _preorder(Node<T>* node)
	{
		if (!node)
			return;

		cout << node->data << " ";
		_preorder(node->left);
		_preorder(node->right);
	}

	void _postorder(Node<T>* node)
	{
		if (!node)
			return;

		_postorder(node->left);
		_postorder(node->right);
		cout << node->data << " ";
	}

	int _balanceFactor(Node<T>* node)
	{
		int heightLeft = 0;
		int heightRight = 0;

		if (node->left)
			heightLeft = node->left->height;

		if (node->right)
			heightRight = node->right->height;

		return heightRight - heightLeft;
	}

	void _fixHeight(Node<T>* node)
	{
		int heightLeft = 0;
		int heightRight = 0;

		if (node->left)
			heightLeft = node->left->height;

		if (node->right)
			heightRight = node->right->height;

		node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	}

	Node<T>* _rotateRight(Node<T>* p)
	{
		Node<T>* q = p->left;

		p->left = q->right;
		q->right = p;

		q->parent = p->parent;
		p->parent = q;

		if (p->left)
			p->left->parent = p;

		if (p == _root)
			_root = q;

		_fixHeight(p);
		_fixHeight(q);

		return q;
	}

	Node<T>* _rotateLeft(Node<T>* q)
	{
		Node<T>* p = q->right;

		q->right = p->left;
		p->left = q;

		p->parent = q->parent;
		q->parent = p;

		if (q->right)
			q->right->parent = q;

		if (q == _root)
			_root = p;

		_fixHeight(q);
		_fixHeight(p);

		return p;
	}

	Node<T>* _balance(Node<T>* node)
	{
		_fixHeight(node);

		if (_balanceFactor(node) == 2)
		{
			if (_balanceFactor(node->right) < 0)
			{
				node->right = _rotateRight(node->right);
				node->right->parent = node;
			}

			return _rotateLeft(node);
		}
		if (_balanceFactor(node) == -2)
		{
			if (_balanceFactor(node->left) > 0)
			{
				node->left = _rotateLeft(node->left);
				node->left->parent = node;
			}

			return _rotateRight(node);
		}

		return node;
	}
};


template<typename T>
class TreeIterator : public std::iterator<std::input_iterator_tag, T>
{
public:
	TreeIterator() :
		_node(nullptr), 
		_tree(nullptr) {}

	TreeIterator(Node<T>* node, AVL_Tree<T>* tree) :
		_node(node), 
		_tree(tree) {}

	TreeIterator(const TreeIterator& i) : 
		_node(i._node),
		_tree(i._tree) {}

	TreeIterator& operator=(const TreeIterator& i) 
	{
		_node = i._node;
		_tree = i._tree;
	}

	TreeIterator<T>& operator=(Node<T>* temp) { _node = temp; }

	bool operator!=(const TreeIterator<T> const& other) const { return _node != other._node; }

	bool operator==(const TreeIterator<T> const& other) const { return _node == other._node; }

	bool operator!() const { return !_node; }

	Node<T>& operator*() const { return _node; }

	TreeIterator<T>& operator++()
	{
		if (_node->right)
			_node = _tree->min(_node->right);

		return *this;
	}

	TreeIterator<T>& operator++(int temp)
	{
		if (_node->right)
			_node = _tree->min(_node->right);

		return *this;
	}

	TreeIterator<T>& operator--()
	{ 
		if (_node->right)
			_node = _tree->max(_node->left);

		return *this;
	}

	TreeIterator<T>& operator--(int temp)
	{
		if (_node->right)
			_node = _tree->max(_node->left);

		return *this;
	}


private:
	Node<T>* _node;
	AVL_Tree<T>* _tree;
};

template<class T>
class IteratedTree : public AVL_Tree<T>
{
public:
	IteratedTree<T>() : AVL_Tree<T>() {}

	TreeIterator<T> begin() { auto it = TreeIterator<T>(this, this->min()); }
	TreeIterator<T> end() { auto it = TreeIterator<T>(this, this->max()); }
};

class State // Класс реализации структуры "Государство" 
{
public:
	State() :
		_name("NaN"),
		_capital("NaN"),
		_language("NaN"),
		_population(0),
		_area(0) {}

	State(string name, string capital, string language, unsigned population, unsigned area) :
		_name(name),
		_capital(capital),
		_language(language),
		_population(population),
		_area(area) {}

	string getName() { return _name; }
	string getCapital() { return _capital; }
	string getLanguage() { return _language; }
	unsigned getPopulation() { return _population; }
	unsigned getArea() { return _area; }

	bool operator ==(const State& temp) { return _name == temp._name; }

	bool operator !=(const State& temp) { return _name != temp._name; }

	bool operator >(const State& temp) { return _name < temp._name; }

	bool operator <(const State& temp) { return _name > temp._name; }

	bool operator >=(const State& temp) { return _name <= temp._name; }

	bool operator <=(const State& temp) { return _name >= temp._name; }

	friend ostream& operator<< (ostream& ustream, State& obj);

private:
	string _name;
	string _capital;
	string _language;
	unsigned _population;
	unsigned _area;
};

ostream& operator<< (ostream& ustream, State& obj) // Вывод объекта класса State
{
	if (&obj)
	{
		cout << "State:\t\t" << obj._name << endl
			 << "Capital:\t" << obj._capital << endl
			 << "Language:\t" << obj._language << endl
			 << "Population:\t" << obj._population << endl
			 << "Area:\t\t" << obj._area << endl;
	}

	return ustream;
}

class StateTree : public IteratedTree<State>
{
public:
	StateTree() : IteratedTree<State>() {}

	void printNode(Node<State>* node)
	{
		cout << "Key:\t\t" << node->data.getName() << endl
			 << "Data: " << endl << node->data << endl;

		cout << "-------------------------------" << endl;
	}

	Node<State>* print(TreeIterator<State>* i)
	{
		auto d = (*i);

	}

	string first(Node<State>* node) { return node->data.getName(); }
	State second(Node<State>* node) { return node->data; }
};

int main()
{
	setlocale(LC_ALL, "Russian");

	vector<string> name =
	{
		"Russia",
		"France",
		"USA",
		"Germany",
		"Japan",
		"China"
	};

	vector<unsigned> population =
	{
		144,
		67,
		328,
		83,
		126,
		1393
	};

	map<string, unsigned> states;
	for (size_t i = 0; i < name.size(); ++i)
		states[name[i]] = population[i];

	{
		cout << "|--------------------------------|" << endl;
		cout << "|========= ЗАДАНИЕ 1.1. =========|" << endl;
		cout << "|--------------------------------|" << endl;

		cout << endl;

		cout << "====================================" << endl;
		cout << "Вывод элементов | Функция - print():" << endl;
		cout << "====================================" << endl;
		print(states);

		cout << endl;

		cout << "=================================================" << endl;
		cout << "Поиск элемента | Функция findItem(): " << endl;
		cout << "=================================================" << endl;
		findItem(states, (string)"Russia", (unsigned)144);
		cout << endl << "-------------------------------------------------" << endl;
		findItem(states, (string)"China", (unsigned)83);
		cout << endl << "-------------------------------------------------" << endl;
		findItem(states, (string)"Brazil", (unsigned)126);
		cout << endl << "-------------------------------------------------" << endl;
		findItem(states, (string)"Italy", (unsigned)837);

		cout << endl << endl;

		cout << "================================" << endl;
		cout << "Фильтрация | Функция - filter(): " << endl;
		cout << "================================" << endl;
		map<string, unsigned> filteredStates = filter(states, threshold);
		print(filteredStates);

		cout << endl;
	}

	{
		cout << "|--------------------------------|" << endl;
		cout << "|========= ЗАДАНИЕ 1.2. =========|" << endl;
		cout << "|--------------------------------|" << endl;

		cout << endl;

		cout << "========================================================" << endl;
		cout << "Очередь с пиоритетом | Класс - MapPriorityQueue<>: " << endl;
		cout << "========================================================" << endl;
		MapPriorityQueue<string, unsigned> q;
		pair<string, unsigned> tempPair("Brazil", 209);
		q.push(states);
		q.push(tempPair);
		q.print();

		cout << endl;

		cout << "========================================================" << endl;
		cout << "Первый элемент | Класс - MapPriorityQueue<> (top()): " << endl;
		cout << "========================================================" << endl;
		cout << "Key:\t" << q.top()->first << endl
			<< "Value:\t" << q.top()->second << endl;

		cout << endl;

		cout << "========================================================" << endl;
		cout << "Удаление элементов | Класс - MapPriorityQueue<> (pop()): " << endl;
		cout << "========================================================" << endl;
		q.pop();
		q.pop();
		q.print();

		cout << endl;
	}

	cout << "|--------------------------------|" << endl;
	cout << "|========= ЗАДАНИЕ 1.3. =========|" << endl;
	cout << "|--------------------------------|" << endl;

	cout << endl;

	StateTree newStates;
	vector<State> vStates =
	{
	   State("Russia", "Moscow", "Russian", 144, 17100),
	   State("France", "Paris", "French", 67, 643),
	   State("USA", "Washington DC", "English", 328, 9843),
	   State("Germany", "Berlin", "German", 83, 357),
	   State("Japan", "Tokyo", "Japanese", 126, 377),
	   State("China", "Beijing", "Chinese", 1393, 9597)
	};

	for (auto i : vStates)
		newStates.insert(i);

	newStates.printNode(newStates.max());
	newStates.printNode(newStates.min());
	newStates.printNode(newStates.getRoot());
}