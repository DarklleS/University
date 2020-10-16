#include <iostream>
#include <vector>

using namespace std;

template<class T>
struct Node
{
	Node* left;
	Node* right;
	Node* parent;
	T data;
	T height;

	Node<T>() :
		left(nullptr),
		right(nullptr),
		parent(nullptr),
		data(NULL),
		height(1) {}

	Node<T>(T value)	:
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
	AVL_Tree(): root(nullptr) {}

	Node<T>* getRoot() { return root; }

	void insert(T key)
	{
		Node<T>* node = new Node<T>(key);
		_insert(root, node);
	}

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
			else if (key > current->data && current->right)
				current = current->right;
		}
	}

	void remove(T key)
	{
		_remove(root, key);
	}

	Node<T>* min(Node<T>* node)
	{
		Node<T>* current = node;

		while (current && current->left)
			current = current->left;

		return current;
	}

	Node<T>* max(Node<T>* node)
	{
		Node<T>* current = node;

		while (current && current->right)
			current = current->right;

		return current;
	}

	void inorder(Node<T>* node)
	{
		if (!node) 
			return;

		inorder(node->left);
		cout << node->data << " ";
		inorder(node->right);
	}

    void preorder(Node<T>* node)
    {
        if (!node)
			return;

		cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node<T>* node)
    {
        if (!node) 
			return;

		postorder(node->left);
		postorder(node->right);
		cout << node->data << " ";
    }

private:
	Node<T>* root;

	Node<T>* _insert(Node<T>* current, Node<T>* node)
	{
		if (!current)
			current = node;

		if (!root)
			root = node;

		if (node->data < current->data && current)
			current->left = _insert(current->left, node);
		else if (node->data > current->data&& current)
			current->right = _insert(current->right, node);

		return current;
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
				root = current->right;

				delete current;
				current = nullptr;

				return root;
			}

			temp = current->right;

			delete current;
			current = nullptr;

			return temp;
		}
		else if (!current->right)
		{
			if (root == current)
			{
				root = current->left;

				delete current;
				current = nullptr;

				return root;
			}

			temp = current->left;

			delete current;
			current = nullptr;

			return temp;
		}
		else
		{
			temp = min(current->right);

			current->data = temp->data;

			current->right = _remove(current->right, temp->data);
		}

		return current;
	}
};

int main()
{
	AVL_Tree<int> T;
	vector<int> arr = { 30, 20, 15, 5, 25, 40, 50, 60, 45, 35 };

	cout << "===================================================" << endl;
	cout << "|                   [AVL TREE]                    |" << endl;
	cout << "===================================================" << endl;

	// ------------------------------ | INSERT | ------------------------------ //
	{
		for (auto i : arr)
			T.insert(i);

		cout << endl << "===================================================";
	}

	// ------------------------------ | ROOT | ------------------------------ //
	{
		cout << endl << "Root:\t" << T.getRoot()->data;

		cout << endl << "===================================================";
	}

	// ------------------------------ | MIN, MAX | ------------------------------ //
	{
		cout << endl << "Min:\t" << T.min(T.getRoot())->data;
		cout << endl << "Max:\t" << T.max(T.getRoot())->data;

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
		T.inorder(T.getRoot());
		cout << "]";

		cout << endl << "Preorder:\t[ ";
		T.preorder(T.getRoot());
		cout << "]";

		cout << endl << "Postorder:\t[ ";
		T.postorder(T.getRoot());
		cout << "]";

		cout << endl << "===================================================";
	}

	// ------------------------------ | REMOVE | ------------------------------ //
	{
		while (T.getRoot())
		{
			cout << endl << "Remove - " << T.getRoot()->data << ":\t[ ";
			T.remove(T.getRoot()->data);
			T.preorder(T.getRoot());
			cout << "]";
		}

		cout << endl;
	}
}