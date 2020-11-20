#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <utility>
#include <cassert>

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
pair<K, V>* findByKey(const map<K, V>& inputMap, const K& key) // Функция поиска элемента в контейнере map
{
	try
	{
		cout << "Item with key: " << key << " was found!" << endl
			 << "Value: " << inputMap.at(key) << endl;

		return new pair<K, V>(key, inputMap.at(key));
	}
	catch (const exception&)
	{
		cout << "Item with key: " << key << " was not found!" << endl;

		return nullptr;
	}

}

template<typename K, typename V>
vector<pair<K, V>>* findByValue(const map<K, V>& inputMap, const V& value) // Функция поиска элемента в контейнере map
{
	vector<pair<K, V>> result;

	for (auto i : inputMap)
	{
		if (i.second == value)
		{
			result.push_back(i);
		}
	}

	if (result.size())
	{
		cout << "Item with value: " << value << " was found!" << endl;

		for (size_t i = 0; i < result.size(); ++i)
		{
			cout << "Key " << i + 1 << ": " << result[i].first << endl;
		}
			
		return &result;
	}
	else
	{
		cout << "Item with value: " << value << " was not found!" << endl;

		return nullptr;
	}
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

	State(const string& name, const string& capital, const string& language, const unsigned& population, const unsigned& area) :
		_name(name),
		_capital(capital),
		_language(language),
		_population(population),
		_area(area) {}

	const string& getName() { return _name; }
	const string& getCapital() { return _capital; }
	const string& getLanguage() { return _language; }
	const unsigned& getPopulation() { return _population; }
	const unsigned& getArea() { return _area; }

	bool operator==(const State& temp) { return _name == temp._name; }

	bool operator!=(const State& temp) { return _name != temp._name; }

	bool operator>(const State& temp) { return _name < temp._name; }

	bool operator<(const State& temp) { return _name > temp._name; }

	bool operator>=(const State& temp) { return _name <= temp._name; }

	bool operator<=(const State& temp) { return _name >= temp._name; }

	friend ostream& operator<<(ostream&, const State&);

private:
	string _name;
	string _capital;
	string _language;
	unsigned _population;
	unsigned _area;
};

ostream& operator<<(ostream& ustream, const State& obj) // Вывод объекта класса State
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

bool operator<(const pair<string, State>& left, const pair<string, State>& right) { return left.first > right.first; } // Перегрузка оператора < (pair)

bool operator>(const pair<string, State>& left, const pair<string, State>& right) { return left.first < right.first; } // Перегрузка оператора > (pair) 

bool operator==(const pair<string, State>& left, const pair<string, State>& right) { return left.first == right.first; }

void printQueue(priority_queue<pair<string, State>>& q)
{
	while (!q.empty()) // Вывод элементов очереди с приоритетом (приоритет по ключам)
	{
		State value = q.top().second;

		cout << "Key:\t\t" << q.top().first << endl << endl
			<< "Value:" << endl << value;

		q.pop();

		if (!q.empty())
			cout << "----------------------------" << endl;
	}
}

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
		data(),
		height(1) {}

	Node<T>(T data) :
		left(nullptr),
		right(nullptr),
		parent(nullptr),
		data(data),
		height(1) {}

	bool operator<(const Node<T>& node) { return data < node.data; }

	bool operator>(const Node<T>& node) { return data > node.data; }
};

template<class T>
class AVL_Tree // Класс реализации АВЛ дерева
{
public:
	AVL_Tree() : _root(nullptr) {}

	Node<T>* getRoot() { return _root; }

	virtual void insert(const T& key) { _insert(_root, new Node<T>(key)); }

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
			else if (key > current->data&& current->right)
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

	string first(Node<State>* node) { return node->data.getName(); }
	State second(Node<State>* node) { return node->data; }

	TreeIterator<T> begin() { return TreeIterator<T>(this, this->min()); }
	TreeIterator<T> end() { return TreeIterator<T>(this, this->max()); }

	template<class T> friend ostream& operator<<(ostream&, IteratedTree<T>&);
};

template<class T>
ostream& operator<<(ostream& ustream, IteratedTree<T>& obj)
{
	TreeIterator<T> it(obj.getRoot(), (AVL_Tree<T>*)(&obj));

	while (&(*(it))) // Пока не дошли до конца
	{
		auto current = it;

		if (!(&(*(++current)))) // Если элемент поддерева является максимальным
		{
			do // Проходим по поддереву
			{
				cout << "Key:\t\t" << (*it).data.first << endl << endl
					 << "Data: " << endl << (*it).data.second;

				if (obj.min() != &(*it))
					ustream << "----------------------------" << endl;
			} while (&(*(--it)));
		}
		else // Если элемент поддерева не максимальный, то идем дальше 
			it++;
	}

	return ustream;
}

template<class T>
class Heap
{
public:
	Heap(const size_t& value) :
		_array(new Node<T>[value]),
		_size(0),
		_capacity(value) {}

	Node<T>* getLeft(const int& index) { return index < 0 || index * 2 >= _size ? nullptr : _array + (index * 2 + 1); }

	Node<T>* getRight(const int& index) { return index < 0 || index * 2 >= _size ? nullptr : _array + (index * 2 + 2); }

	Node<T>* getParent(const int& index)
	{
		if (index <= 0 || index >= _size)
			return nullptr;

		return index % 2 ? _array + (index / 2) : _array + (index / 2 - 1);
	}

	unsigned getLeftIndex(const int& index) { return index < 0 || index * 2 >= _size ? INT_MAX : index * 2 + 1; }

	unsigned getRightIndex(const int& index) { return index < 0 || index * 2 >= _size ? INT_MAX : index * 2 + 2; }

	unsigned getParentIndex(const int& index)
	{
		if (index <= 0 || index >= _size)
			return INT_MAX;

		return index % 2 == 0 ? index / 2 - 1 : index / 2;
	}

	unsigned getSize() { return _size; }

	void insert(const T& data) { _insert(new Node<T>(data)); }

	void remove(const T& data) { _remove(data); }

	Node<T> extractMax()
	{
		Node<T> root = _array[0];

		_array[0] = _array[_size - 1];
		_size--;

		_heapify(0);

		return root;
	}

	void straight(void(*f)(Node<T>*))
	{
		for (size_t i = 0; i < _size; ++i)
			f(&_array[i]);
	}

	void inorder() { _inorder(); }

	void preorder() { _preorder(); }

	void postorder() { _postorder(); }

	Node<T>& operator[](const int& index)
	{
		assert(index >= 0 || index < _size);

		return _array[index];
	}

	template<class T> friend ostream& operator<<(ostream&, Heap<T>&);

private:
	Node<T>* _array;
	int _size;
	int _capacity;

	void _insert(Node<T>* node)
	{
		if (_size < _capacity)
		{
			_array[_size].data = node->data;
			_size++;

			_siftUp();
		}
	}

	void _remove(T value)
	{
		if (!_size)
			return;

		int index = 0;

		while (index < _size)
		{
			if (_array[index].data == value)
				break;

			index++;
		}

		if (index != _size)
		{
			swap(_array[index], _array[_size - 1]);

			_size--;

			_heapify(index);
		}
	}

	void _siftUp(int index = -1)
	{
		if (index == -1)
			index = _size - 1;

		unsigned parent = getParentIndex(index);
		unsigned newIndex = getLeftIndex(parent);

		if (newIndex == index)
			newIndex = getRightIndex(parent);

		unsigned maxIndex = index;

		if (index < _size && newIndex < _size && parent >= 0)
		{
			if (_array[index] > _array[newIndex])
				maxIndex = index;

			if (_array[index] < _array[newIndex])
				maxIndex = newIndex;
		}

		if (parent < _size && parent >= 0 && _array[maxIndex] > _array[parent])
		{
			swap(_array[maxIndex], _array[parent]);
			_siftUp(parent);
		}
	}

	void _heapify(const unsigned& index)
	{
		unsigned largest = index;
		unsigned left = getLeftIndex(index);
		unsigned right = getRightIndex(index);

		if (left < _size && right < _size && _array[left] > _array[largest])
			largest = left;

		if (right < _size && left < _size && _array[right] > _array[largest])
			largest = right;

		if (left < _size && right >= _size)
			largest = left;

		if (largest != index)
		{
			swap(_array[index], _array[largest]);
			_heapify(largest);
		}
	}

	void _inorder(int index = 0)
	{
		if (getLeftIndex(index) < _size)
			_inorder(getLeftIndex(index));

		if (index >= 0 && index < _size)
			cout << _array[index].data << " ";

		if (getRightIndex(index) < _size)
			_inorder(getRightIndex(index));
	}

	void _preorder(int index = 0)
	{
		if (index >= 0 && index < _size)
			cout << _array[index].data << " ";

		if (getLeftIndex(index) < _size)
			_preorder(getLeftIndex(index));

		if (getRightIndex(index) < _size)
			_preorder(getRightIndex(index));
	}

	void _postorder(int index = 0)
	{
		if (getLeftIndex(index) < _size)
			_preorder(getLeftIndex(index));

		if (getRightIndex(index) < _size)
			_preorder(getRightIndex(index));

		if (index >= 0 && index < _size)
			cout << _array[index].data << " ";
	}
};

template<class T>
ostream& operator<<(ostream& ustream, Heap<T>& obj)
{
	Node<pair<string, State>> temp;

	while (obj.getSize())
	{
		Node<pair<string, State>> temp = obj.extractMax();

		ustream << "Key:\t\t" << temp.data.first << endl << endl
			 << "Data:" << endl << temp.data.second;

		if (obj.getSize())
			ustream << "----------------------------" << endl;
	}

	return ustream;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	vector<pair<string, unsigned>> vStates = 
	{
		pair<string, unsigned>("Russia", 144),
		pair<string, unsigned>("France", 67),
		pair<string, unsigned>("USA", 328),
		pair<string, unsigned>("Germany", 83),
		pair<string, unsigned>("Austria", 83),
		pair<string, unsigned>("Japan", 126),
		pair<string, unsigned>("China", 1393)
	};

	map<string, unsigned> mStates;

	for (auto i : vStates)
		mStates.emplace(i);

	{
		cout << "|--------------------------------|" << endl;
		cout << "|========= ЗАДАНИЕ 2.1. =========|" << endl;
		cout << "|--------------------------------|" << endl;

		cout << endl;

		cout << "====================================" << endl;
		cout << "Вывод элементов | Функция - print():" << endl;
		cout << "====================================" << endl;

		print(mStates);

		cout << endl;

		cout << "====================================================" << endl;
		cout << "Поиск элемента | Функции findByKey(), findByValue():" << endl;
		cout << "====================================================" << endl;

		findByKey(mStates, (string)"Russia");
		cout << "-------------------------------------------------" << endl;
		findByValue(mStates, (unsigned)83);
		cout << "-------------------------------------------------" << endl;
		findByKey(mStates, (string)"Brazil");
		cout <<  "-------------------------------------------------" << endl;
		findByValue(mStates, (unsigned)101);

		cout << endl;

		cout << "================================" << endl;
		cout << "Фильтрация | Функция - filter(): " << endl;
		cout << "================================" << endl;

		map<string, unsigned> filteredStates = filter(mStates, threshold);

		print(filteredStates);

		cout << endl;
	}

	vector<State> vNewStates =
	{
		State("Russia", "Moscow", "Russian", 144, 17100),
		State("France", "Paris", "French", 67, 643),
		State("USA", "Washington DC", "English", 328, 9843),
		State("Germany", "Berlin", "German", 83, 357),
		State("Armenia", "Yerevan", "Armenian", 3, 30),
		State("Japan", "Tokyo", "Japanese", 126, 377),
		State("Canada", "Ottawa", "English, French", 38, 9985),
		State("Brazil", "Brasilia", "Portuguese", 210, 8516),
		State("Italy", "Rome", "Italian", 60, 301),
		State("China", "Beijing", "Chinese", 1393, 9597)
	};

	map<string, State> mNewStates;

	for (auto i : vNewStates)
		mNewStates.emplace(i.getName(), i);

	{
		cout << "|--------------------------------|" << endl;
		cout << "|========= ЗАДАНИЕ 2.2. =========|" << endl;
		cout << "|--------------------------------|" << endl;

		cout << endl;

		cout << "================================================" << endl;
		cout << "Очередь с пиоритетом | Класс - priority_queue<>:" << endl;
		cout << "================================================" << endl;

		priority_queue<pair<string, State>> qStates;

		for (auto i : mNewStates)
			qStates.push((pair<string, State>) i);

		printQueue(qStates);

		cout << endl;
	}

	{
		cout << "|--------------------------------|" << endl;
		cout << "|========= ЗАДАНИЕ 2.3. =========|" << endl;
		cout << "|--------------------------------|" << endl;

		cout << endl;

		IteratedTree<pair<string, State>> tStates;

		for (auto i : vNewStates)
			tStates.insert(pair<string, State>(i.getName(), i));

		cout << "====================================================================" << endl;
		cout << "Вывод элементов дерева с помощью итератора | Класс - IteratedTree<>:" << endl;
		cout << "====================================================================" << endl;

		cout << tStates;

		cout << endl;
	}

	{
		cout << "|--------------------------------|" << endl;
		cout << "|========= ЗАДАНИЕ 2.4. =========|" << endl;
		cout << "|--------------------------------|" << endl;

		Heap<pair<string, State>> hStates(vNewStates.size());

		for (auto i : vNewStates)
			hStates.insert(pair<string, State>(i.getName(), i));

		cout << hStates;
	}
}
