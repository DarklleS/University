#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	Node* left;
	Node* right;
	Node* parent;
	int data;
	int height;

	Node()
	{
		left = right = parent = nullptr;
		height = 1;
	}

	Node(int value) 
	{
		data = value;
		left = right = parent = nullptr;
		height = 1;
	}
};

class AVL_Tree
{
private:
	Node* root;

public:
	AVL_Tree() { root = nullptr; }

	Node* getRoot() { return root; }

	Node* insert(Node* node, int key)
	{
		!node ? node = new Node(key) : node;

		!root ? root = node : root;

		key < node->data && node ? node->left = insert(node->left, key) :
		key > node->data && node ? node->right = insert(node->right, key) :
                                   node;

        return node;
	}

	Node* remove(Node* node, int key)
	{
		Node* temp = node;

		if (!node) { return nullptr; }

		key < node->data ? node->left = remove(node->left, key) :
		key > node->data ? node->right = remove(node->right, key) :
						   node;

		if (key != node->data) { return node; }

		if (!node->left && !node->right && root == node)
		{
			delete root;
			root = nullptr;

			return root;
		}
		else if (!node->left)
		{
			if (root == node)
			{
				root = node->right;

				delete node;
				node = nullptr;

				return root;
			}

			temp = node->right;

			delete node;
			node = nullptr;

			return temp;
		}
		else if (!node->right)
		{
			if (root == node)
			{
				root = node->left;

				delete node;
				node = nullptr;

				return root;
			}

			temp = node->left;

			delete node;
			node = nullptr;

			return temp;
		}
		else
		{
			temp = min(node->right);

			node->data = temp->data;

			node->right = remove(node->right, temp->data);
		}

		return node;
	}

	Node* min(Node* node)
	{
		Node* current = node;

		while (current && current->left)
			current = current->left;

		return current;
	}

	Node* max(Node* node)
	{
		Node* current = node;

		while (current && current->right)
			current = current->right;

		return current;
	}

	void inorder(Node* node)
	{
		if (!node) { return; }

		inorder(node->left);

		cout << node->data << " ";

		inorder(node->right);
	}

    void preorder(Node* node)
    {
        if (!node) { return; }

		cout << node->data << " ";

        preorder(node->left);

        preorder(node->right);
    }

    void postorder(Node* node)
    {
        if (!node) { return; }

		postorder(node->left);

		postorder(node->right);

		cout << node->data << " ";
    }
};

int main()
{
	AVL_Tree T;
	vector<int> arr = { 30, 20, 15, 5, 25, 40, 50, 60, 45, 35 };

	// ------------------------------ | INSERT | ------------------------------ //
	for (auto value : arr)
		T.insert(T.getRoot(), value);

	cout << "---------------------------------------------------" << endl;
	cout << "|                  | AVL TREE |                   |" << endl;
	cout << "---------------------------------------------------" << endl;

	// ------------------------------ | ROOT | ------------------------------ //
	cout << endl << "Root: " << T.getRoot()->data;

	cout << endl;

	// ------------------------------ | MIN, MAX | ------------------------------ //
	cout << endl << "Min: " << T.min(T.getRoot())->data;
	cout << endl << "Max: " << T.max(T.getRoot())->data;

	cout << endl;

	// ------------------------------ | INORDER, PREORDER, POSTORDER | ------------------------------ //
	cout << endl << "Inorder:\t[ ";
	T.inorder(T.getRoot());
	cout << "]";

	cout << endl << "Preorder:\t[ ";
	T.preorder(T.getRoot());
	cout << "]";

	cout << endl << "Postorder:\t[ ";
	T.postorder(T.getRoot());
	cout << "]";

	cout << endl;

	// ------------------------------ | REMOVE | ------------------------------ //
	while (T.getRoot())
	{
		cout << endl << "Remove - " << T.getRoot()->data << ":\t[ ";
		T.remove(T.getRoot(), T.getRoot()->data);
		T.preorder(T.getRoot());
		cout << "]";
	}

	cout << endl;
}