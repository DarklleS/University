#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>

using namespace std;

template<typename K, typename V>
void print(const map<K, V>& inputMap) // Функция вывода элементов контейнера map
{
    for (auto i : inputMap)
    {
        cout << "Key:\t" << i.first << endl
             << "Value:\t" << i.second;
        
        if (i != *(--inputMap.cend()))
            cout << endl << "---------------" << endl;
    }

    cout << endl;
}

template<typename K, typename V>
bool findByKey(const map<K, V>& inputMap, const K& key) // Функция поиска элемента в контейнере map
{
	try
	{
		inputMap.at(key);

		cout << "Item with key: " << key << " was found!" << endl
			 << "Value is: " << inputMap.at(key);

		return true;
	}
	catch (const exception& ex)
	{
		cout << "Item with key: " << key << " was not found!";

		return false;
	}

}

template<typename K, typename V>
bool findByValue(const map<K, V>& inputMap, const V& value) // Функция поиска элемента в контейнере map
{
	bool flag = false;

	for (auto i : inputMap)
	{
		if (i.second == value)
		{
			cout << "Item with value: " << value << " was found!" << endl
				 << "Key is: " << i.first << endl;

			flag = true;
		}
	}

	if (!flag)
		cout << "Item with value: " << value << " was not found!";

	return flag;
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
			newMap.emplace(i);
    }

    return newMap;
}

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

	bool operator==(const State& temp) { return _name == temp._name; }

	bool operator!=(const State& temp) { return _name != temp._name; }

	bool operator>(const State& temp) { return _name < temp._name; }

	bool operator<(const State& temp) { return _name > temp._name; }

	bool operator>=(const State& temp) { return _name <= temp._name; }

	bool operator<=(const State& temp) { return _name >= temp._name; }

	friend ostream& operator<<(ostream& ustream, State& obj);

private:
	string _name;
	string _capital;
	string _language;
	unsigned _population;
	unsigned _area;
};

ostream& operator<<(ostream& ustream, State& obj) // Вывод объекта класса State
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

template<typename K, typename V> 
class MapPriorityQueue // Класс реализации очереди с приоритетом
{
public:
	MapPriorityQueue() {}

	MapPriorityQueue(map<K, V>& temp) : _priorityMap(temp) {}

	void push(const pair<const K, V>& temp) // Метод вставки нового элемента
	{ 
		_priorityMap.emplace(temp);

		cout << "push() - " << temp.first << endl;

		if (_priorityMap.size() != 1)
			cout << "---------------------------" << endl;
	}

	void push(const K& key, const V& value) // Метод вставки нового элемента
	{
		_priorityMap.emplace(key, value);

		cout << "push() - " << key << endl;
		
		if (_priorityMap.size() != 1)
			cout << "---------------------------" << endl;
	}

	void pop() // Метод удаления элемента
	{

		if (!_priorityMap.size())
			cout << "---------------------------" << endl;

		cout << "pop() - " << (*(_priorityMap.cbegin())).first << endl;

		if (_priorityMap.size())
			cout << "---------------------------" << endl;

		_priorityMap.erase(_priorityMap.cbegin());
	}

	void printTop() // Метод вывода верхнего элемента
	{
		auto temp = this->top().second;

		cout << "Key: " << this->top().first << endl << endl
			 << "Data: " << endl << temp;

		if (_priorityMap.size() != 1)
			cout << "---------------------------" << endl;
	}

	void print() // Метод вывода элементов
	{
		while (_priorityMap.size())
		{
			this->printTop();
			this->pop();
		}
	}

	const pair<const string, State> top() { return *(_priorityMap.cbegin()); }

private:
	map<K, V> _priorityMap;
};

template<class T>
struct Node // Структура реализации узла бирного дерева 
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
class AVL_Tree // Класс реализации АВЛ дерева
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

	Node<T>* successor(Node<T>* node) { return _successor(node); }

	Node<T>* predcessor(Node<T>* node) { return _predcessor(node); }

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
		else if (node->data > current->data&& current)
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

	Node<T>* _successor(Node<T>* node)
	{
		if (!node)
			return nullptr;

		if (node->right)
			return _min(node->right);
		else
		{
			Node<T>* successor = nullptr;
			Node<T>* ancestor = _root;

			while (ancestor != node)
			{
				if (node->data < ancestor->data)
				{
					successor = ancestor;
					ancestor = ancestor->left;
				}
				else
					ancestor = ancestor->right;
			}

			return successor;
		}
	}

	Node<T>* _predcessor(Node<T>* node)
	{
		Node<T>* temp = node;

		if (!node)
			return nullptr;
		else if (node == _root && !node->left)
			return nullptr;
		else if (node->left)
			return _max(node->left);
		else
		{
			while (temp->parent && temp->parent->right != temp)
				temp = temp->parent;

			return temp->parent;
		}
	}
};

template<typename T>
class TreeIterator : public iterator<input_iterator_tag, T>
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

	TreeIterator<T>& operator=(const TreeIterator& i) 
	{
		_node = i._node;
		_tree = i._tree;

		return *this;
	}

	TreeIterator<T>& operator=(Node<T>* temp) 
	{
		_node = temp;

		return *this;
	}

	bool operator!=(const TreeIterator<T> const& other) const { return _node != other._node; }

	bool operator==(const TreeIterator<T> const& other) const { return _node == other._node; }

	bool operator!() const { return !_node; }

	Node<T>& operator*() const { return *(_node); }

	TreeIterator<T>& operator++()
	{
		_node = _tree->successor(_node);

		return *this;
	}

	TreeIterator<T>& operator++(int temp)
	{
		_node = _tree->successor(_node);

		return *this;
	}

	TreeIterator<T>& operator--()
	{ 
		_node = _tree->predcessor(_node);

		return *this;
	}

	TreeIterator<T>& operator--(int temp)
	{
		_node = _tree->predcessor(_node);

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
	IteratedTree() : AVL_Tree<T>() {}

	IteratedTree(const AVL_Tree<T>& tree) { this->_root = tree._root; }

	void printNode(Node<State>* node) // Метод вывода элемента дерева
	{
		cout << "Key:\t\t" << node->data.getName() << endl << endl
			 << "Data: " << endl << node->data;
	}

	void print(TreeIterator<State> it)
	{
		while (&(*(it))) // Пока не дошли до конца
		{
			auto current = it; 

			if (!(&(*(++current)))) // Если элемент поддерева является максимальным
			{
				do // Проходим по поддереву
				{
					printNode(&(*it));

					if (this->min() != &(*it))
						cout << "----------------------------" << endl;
				} while (&(*(--it)));
			}
			else // Если элемент поддерева не максимальный, то идем дальше 
				it++;
		}
	}

	string first(Node<State>* node) { return node->data.getName(); }
	State second(Node<State>* node) { return node->data; }

	TreeIterator<T> begin() { return TreeIterator<T>(this, this->min()); }
	TreeIterator<T> end() { return TreeIterator<T>(this, this->max()); }
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
		"Austria",
		"Japan",
		"China"
	};

	vector<unsigned> population =
	{
		144,
		67,
		328,
		83,
		83,
		126,
		1393
	};
	
	map<string, unsigned> states;

	for (size_t i = 0; i < name.size(); ++i)
		states.emplace(name[i], population[i]);

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

		findByKey(states, (string)"Russia");
		cout << endl << "-------------------------------------------------" << endl;
		findByValue(states, (unsigned)83);
		cout << endl << "-------------------------------------------------" << endl;
		findByKey(states, (string)"Brazil");
		cout << endl << "-------------------------------------------------" << endl;
		findByValue(states, (unsigned)101);

		cout << endl << endl;

		cout << "================================" << endl;
		cout << "Фильтрация | Функция - filter(): " << endl;
		cout << "================================" << endl;

		map<string, unsigned> filteredStates = filter(states, threshold);

		print(filteredStates);

		cout << endl;
	}

	vector<State> vStates =
	{
		State("Russia", "Moscow", "Russian", 144, 17100),
		State("France", "Paris", "French", 67, 643),
		State("USA", "Washington DC", "English", 328, 9843),
		State("Germany", "Berlin", "German", 83, 357),
		State("Japan", "Tokyo", "Japanese", 126, 377),
		State("Canada", "Ottawa", "English, French", 38, 9985),
		State("Brazil", "Brasilia", "Portuguese", 210, 8516),
		State("Italy", "Rome", "Italian", 60, 301),
		State("China", "Beijing", "Chinese", 1393, 9597)
	};

	map<string, State> mapStates;

	for (auto i : vStates)
		mapStates.emplace(i.getName(), i);

	{
		cout << "|--------------------------------|" << endl;
		cout << "|========= ЗАДАНИЕ 1.2. =========|" << endl;
		cout << "|--------------------------------|" << endl;

		cout << endl;

		cout << "========================================================" << endl;
		cout << "Очередь с пиоритетом | Класс - MapPriorityQueue<>:" << endl;
		cout << "========================================================" << endl;

		MapPriorityQueue<string, State> q(mapStates);

		q.printTop();
		q.pop();
		q.push("Australia", State("Australia", "Canberra", "English", 25, 7692));
		q.printTop();
		q.pop();
		q.pop();
		q.print();
	}

	cout << "|--------------------------------|" << endl;
	cout << "|========= ЗАДАНИЕ 1.3. =========|" << endl;
	cout << "|--------------------------------|" << endl;

	cout << endl;

	IteratedTree<State> newStates;

	for (auto i : vStates)
		newStates.insert(i);

	TreeIterator<State> it(newStates.getRoot(), (AVL_Tree<State>*)(&newStates));

	cout << "==============================================================================" << endl;
	cout << "Вывод элементов дерева с помощью итератора | Класс - TreeIterator<> (print()):" << endl;
	cout << "==============================================================================" << endl;

	newStates.print(it); 
}
