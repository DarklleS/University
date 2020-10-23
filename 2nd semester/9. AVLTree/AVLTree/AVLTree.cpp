#include <iostream>
#include <vector>

using namespace std;

template<class T>
struct Node
{
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
	T data;
	T height;

	Node<T>() :
		left(nullptr),
		right(nullptr),
		parent(nullptr),
		data(NULL),
		height(1) {}

	Node<T>(T value) :
		left(nullptr),
		right(nullptr),
		parent(nullptr),
		data(value),
		height(1) {}
};

template<class T>
class AVL_Tree
{
public:
	AVL_Tree() : root(nullptr) {}

	Node<T>* getRoot() { return root; }

	void insert(T key) { _insert(root, new Node<T>(key)); }

	void remove(T key) { _remove(root, key); }

	Node<T>* min() { return _min(root); }

	Node<T>* max() { return _max(root); }

	Node<T>* find(T key)
	{
		if (!root)
			return nullptr;

		Node<T>* current = root;

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

	void inorder() { _inorder(root); }

	void preorder() { _preorder(root); }

	void postorder() { _postorder(root); }

private:
	Node<T>* root;

	Node<T>* _insert(Node<T>* current, Node<T>* node)
	{
		if (!current)
			current = node;

		if (!root)
			root = node;

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

		return balance(current);
	}

	Node<T>* _remove(Node<T>* current, T key)
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

		if (!current->left && !current->right && root == current)
		{
			delete root;
			root = nullptr;

			return root;
		}
		else if (!current->left)
		{
			if (root == current)
			{
				current->right->parent = nullptr;
				root = current->right;

				delete current;
				current = nullptr;

				return root;
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
			if (root == current)
			{
				current->left->parent = nullptr;
				root = current->left;

				delete current;
				current = nullptr;

				return root;
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

		return balance(current);
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

	int balanceFactor(Node<T>* node)
	{
		int heightLeft = 0;
		int heightRight = 0;

		if (node->left)
			heightLeft = node->left->height;

		if (node->right)
			heightRight = node->right->height;

		return heightRight - heightLeft;
	}

	void fixHeight(Node<T>* node)
	{
		int heightLeft = 0;
		int heightRight = 0;

		if (node->left)
			heightLeft = node->left->height;

		if (node->right)
			heightRight = node->right->height;

		node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	}

	Node<T>* rotateRight(Node<T>* p)
	{
		Node<T>* q = p->left;

		p->left = q->right;
		q->right = p;

		q->parent = p->parent;
		p->parent = q;

		if (p->left)
			p->left->parent = p;

		if (p == root)
			root = q;

		fixHeight(p);
		fixHeight(q);

		return q;
	}

	Node<T>* rotateLeft(Node<T>* q)
	{
		Node<T>* p = q->right;

		q->right = p->left;
		p->left = q;

		p->parent = q->parent;
		q->parent = p;

		if (q->right)
			q->right->parent = q;

		if (q == root)
			root = p;

		fixHeight(q);
		fixHeight(p);

		return p;
	}

	Node<T>* balance(Node<T>* node)
	{
		fixHeight(node);

		if (balanceFactor(node) == 2)
		{
			if (balanceFactor(node->right) < 0)
			{
				node->right = rotateRight(node->right);
				node->right->parent = node;
			}

			return rotateLeft(node);
		}
		if (balanceFactor(node) == -2)
		{
			if (balanceFactor(node->left) > 0)
			{
				node->left = rotateLeft(node->left);
				node->left->parent = node;
			}

			return rotateRight(node);
		}

		return node;
	}
};

int main()
{
	AVL_Tree<int> T;
	vector<int> arr = { 10,20,30,40,50,25 };

	cout << "===================================================" << endl;
	cout << "|                   [AVL TREE]                    |" << endl;
	cout << "===================================================" << endl;

	// ------------------------------ | INSERT | ------------------------------ //
	{
		for (auto i : arr)
			T.insert(i);
	}

	// ------------------------------ | ROOT | ------------------------------ //
	{
		cout << "Root:\t" << T.getRoot()->data;

		cout << endl << "===================================================";
	}

	// ------------------------------ | MIN, MAX | ------------------------------ //
	{
		cout << endl << "Min:\t" << T.min()->data;
		cout << endl << "Max:\t" << T.max()->data;

		cout << endl << "===================================================";
	}

	// ------------------------------ | FIND | ------------------------------ //
	{
		vector<int> temp = { 45, 10 };

		for (auto i : temp)
		{
			cout << endl << "Find - " << i << ":\t";
			if (T.find(i))
				cout << i << " was found!";
			else
				cout << i << " was not found!";
		}
		temp.clear();

		cout << endl << "===================================================";
	}

	// ------------------------------ | INORDER, PREORDER, POSTORDER | ------------------------------ //
	{
		cout << endl << "Inorder:\t[ ";
		T.inorder();
		cout << "]";

		cout << endl << "Preorder:\t[ ";
		T.preorder();
		cout << "]";

		cout << endl << "Postorder:\t[ ";
		T.postorder();
		cout << "]";

		cout << endl << "===================================================";
	}

	// ------------------------------ | REMOVE | ------------------------------ //
	{
		while (T.getRoot())
		{
			cout << endl << "Remove - " << T.getRoot()->data << ":\t[ ";
			T.remove(T.getRoot()->data);
			T.preorder();
			cout << "]";
		}

		cout << endl;
	}
}
