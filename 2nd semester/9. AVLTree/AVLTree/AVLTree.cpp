// AVL_Tree_Inh.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

class Residence
{
protected:
	string adress;
	enum House
	{
		TOWN = 0,
		COUNTRY = 1,
		APARTAMENT = 2,
		COTTAGE = 3
	};
	House type;
	string typeName;
	double totalArea;
	double livingArea;
	double price;
public:
	Residence()
	{
		adress = "NaN";
		typeName = "NaN";
		totalArea = 10000;
		livingArea = 10000;
		price = 10000;
	}
	Residence(string str)
	{
		adress = str;
		typeName = "NaN";
		totalArea = 10000;
		livingArea = 10000;
		price = 10000;
	}
	Residence(string str, int type, double value1, double value2, double value3)
	{
		adress = str;
		typeName = typeDefinition(type);
		totalArea = value1;
		livingArea = value2;
		price = value3;
	}

	string typeDefinition(int name)
	{
		switch (name)
		{
		case Residence::TOWN:
			return "Городской дом";
		case Residence::COUNTRY:
			return "Загородный дом";
		case Residence::APARTAMENT:
			return "Квартина";
		case Residence::COTTAGE:
			return "Дача";
		default:
			break;
		}
	}

	friend bool operator<(const Residence& a, const  Residence& b);
	friend bool operator>(const Residence& a, const Residence& b);
	friend bool operator<=(const Residence& a, const Residence& b);
	friend bool operator>=(const Residence& a, const Residence& b);
	bool operator ==(const Residence& a)
	{
		return adress == a.adress;
	}

	void print()
	{
		cout << "Адресс: " << adress << endl
			<< "Тип жилья: " << typeName << endl
			<< "Общая площадь: " << totalArea << " кв. м." << endl
			<< "Жилая площадь: " << livingArea << " кв. м." << endl
			<< "Цена: " << price << " $" << endl << endl;
	}

	friend ostream& operator<< (ostream& stream, const Residence& temp);
};

ostream& operator<< (ostream& stream, const Residence& temp)
{
	stream << "Адресс: " << temp.adress << endl
		<< "Тип жилья: " << temp.typeName << endl
		<< "Общая площадь: " << temp.totalArea << " кв. м." << endl
		<< "Жилая площадь: " << temp.livingArea << " кв. м." << endl
		<< "Цена: " << temp.price << " $" << endl << endl;

	return stream;
}
bool operator<(const Residence& a, const Residence& b)
{
	return a.adress < b.adress;
}
bool operator>(const Residence& a, const Residence& b)
{
	return a.adress > b.adress;
}
bool operator<=(const Residence& a, const Residence& b)
{
	return a.adress <= b.adress;
}
bool operator>=(const Residence& a, const Residence& b)
{
	return a.adress >= b.adress;
}

class Node
{
private:
	Node* left;
	Node* right;
	Node* parent;
	Residence data;
	unsigned int height;

public:
	virtual void setLeft(Node* ptr) { left = ptr; }
	virtual void setRight(Node* ptr) { right = ptr; }
	virtual void setParent(Node* ptr) { parent = ptr; }
	virtual void setData(Residence temp) { data = temp; }
	virtual void setHeight(unsigned int value) { height = value; }

	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }
	virtual Residence getData() { return data; }
	virtual unsigned int getHeight() { return height; }

	Node(Residence temp)
	{
		data = temp;
		left = right = parent = nullptr;
		height = 1;
	}

	Node()
	{
		data = Residence();
		left = right = parent = nullptr;
		height = 0;
	}

	virtual void print(Node* temp)
	{
		data.print();
	}

	friend ostream& operator<< (ostream& stream, Node& N);
};

ostream& operator<< (ostream& stream, Node& temp)
{
	stream << "Данные узла: " << temp.data << ", высота: " << temp.height;

	return stream;
}

class Tree
{
protected:
	Node* root;

public:
	virtual Node* getRoot() { return root; }

	Tree()
	{
		root = nullptr;
	}

	virtual void add(Node* temp)
	{
		if (root == nullptr)
		{
			root = temp;
			return;
		}

		Node* current = root;

		while (current != nullptr)
		{
			if (current->getData() > temp->getData())
			{
				if (current->getLeft() != nullptr)
				{
					current = current->getLeft();
					continue;
				}

				current->setLeft(temp);
				temp->setParent(current);
				temp->setHeight(current->getHeight() + 1);

				break;
			}

			if (current->getData() < temp->getData())
			{
				if (current->getRight() != nullptr)
				{
					current = current->getRight();
					continue;
				}

				current->setRight(temp);
				temp->setParent(current);
				temp->setHeight(current->getHeight() + 1);
				
				break;
			}
		}
	}

	virtual Node* add_r(Node* temp, Node* current = nullptr)
	{
		if (temp == nullptr)
			return nullptr;

		if (root == nullptr)
		{
			root = temp;
			root->setHeight(0);
			return temp;
		}

		if (current == nullptr)
			current = root;

		if (current->getData() > temp->getData())
		{
			if (current->getLeft() != nullptr)
			{
				current->setLeft(add_r(temp, current->getLeft()));
				current->setHeight(current->getLeft()->getHeight());

				if (current->getRight() && current->getRight()->getHeight() > current->getHeight())
					current->setHeight(current->getRight()->getHeight());

				current->setHeight(current->getHeight() + 1);
			}
			else
			{
				current->setLeft(temp);
				temp->setParent(current);

				if (current->getRight() == nullptr)
					current->setHeight(current->getHeight() + 1);
			}
		}

		if (current->getData() < temp->getData())
		{
			if (current->getRight() != nullptr)
			{
				current->setRight(add_r(temp, current->getRight()));
				current->setHeight(current->getRight()->getHeight());

				if (current->getLeft() && current->getLeft()->getHeight() > current->getHeight())
					current->setHeight(current->getLeft()->getHeight());

				current->setHeight(current->getHeight() + 1);
			}
			else
			{
				current->setRight(temp);
				temp->setParent(current);

				if (current->getLeft() == nullptr)
					current->setHeight(current->getHeight() + 1);
			}
		}

		return current;
	}

	virtual void add(Residence temp)
	{
		Node* nodeTemp = new Node;
		
		nodeTemp->setData(temp);
		add_r(nodeTemp);
	}

	void fixHeight(Node* p)
	{
		int heightLeft = 0;
		int heightRight = 0;

		if (p->getLeft() != nullptr)
			heightLeft = p->getLeft()->getHeight();

		if (p->getRight() != nullptr)
			heightLeft = p->getRight()->getHeight();

		if (heightLeft != 0 || heightRight != 0)
			p->setHeight((heightLeft > heightRight ? heightLeft : heightRight) + 1);
		else
			p->setHeight(0);
	}

	void fixAllHights(Node* p)
	{
		fixHeight(p);

		while (p->getParent())
		{
			fixHeight(p);
			p = p->getParent();
		}
	}

	virtual void remove(Node* temp)
	{
		if (temp == nullptr)
			return;

		if (temp == root && temp->getLeft() == nullptr && temp->getRight() == nullptr) // Если имеем только одного элемент
		{
			delete temp;
			root = nullptr;
			return;
		}
		else if (temp == root && temp->getLeft() != nullptr && temp->getRight() == nullptr) // Если имеет только левого потомка
		{
			root = temp->getLeft();
			root->setHeight(root->getHeight() - 1);
			root->setParent(nullptr);

			delete temp;
			return;
		}
		else if (temp == root && temp->getLeft() == nullptr && temp->getRight() == nullptr) // Если имеет только правого потомка
		{
			root = temp->getRight();
			root->setHeight(root->getHeight() - 1);
			root->setParent(nullptr);

			delete temp;
			return;
		}
		else if (temp == root && temp->getLeft() != nullptr && temp->getRight() != nullptr) // Если имеем оба потомка
		{
			Node* childTemp = Tree::max(temp->getLeft());
			
			if (childTemp->getParent()->getRight() == childTemp)
			{
				childTemp->getParent()->setRight(childTemp->getLeft());
				childTemp->setRight(temp->getRight());

				if (childTemp->getLeft() != nullptr)
					childTemp->getLeft()->setParent(temp->getParent());

				childTemp->setLeft(temp->getLeft());
				temp->getLeft()->setParent(childTemp);
			}
			else
				childTemp->setRight(temp->getRight());

			temp->getRight()->setParent(childTemp);
			fixHeight(childTemp);

			root = childTemp;
			root->setParent(nullptr);

			delete temp;
			return;
		}

		Node* parentTemp = temp->getParent();

		if (temp->getLeft() == nullptr && temp->getRight() == nullptr)
		{
			if (parentTemp->getLeft() == temp)
				parentTemp->setLeft(nullptr);
			else
				parentTemp->setRight(nullptr);

			fixAllHights(parentTemp);
			delete temp;
		}
		else if (temp->getLeft() != nullptr && temp->getRight() == nullptr)
		{
			if (parentTemp->getLeft() == temp)
			{
				parentTemp->setLeft(temp->getLeft());
				temp->getLeft()->setParent(parentTemp);
			}
			else
			{
				parentTemp->setRight(temp->getLeft());
				temp->getLeft()->setParent(parentTemp);
			}

			fixAllHights(parentTemp);
			delete temp;
		}
		else if (temp->getLeft() == nullptr && temp->getRight() != nullptr)
		{
			if (parentTemp->getLeft() == temp)
			{
				parentTemp->setLeft(temp->getRight());
				temp->getRight()->setParent(parentTemp);
			}
			else
			{
				parentTemp->setRight(temp->getRight());
				temp->getRight()->setParent(parentTemp);
			}

			fixAllHights(parentTemp);
			delete temp;
		}
		else if (temp->getLeft() != nullptr && temp->getRight() != nullptr)
		{
			Node* childTemp = Tree::max(temp->getLeft());

			if (childTemp->getParent()->getRight() == childTemp)
			{
				childTemp->getParent()->setRight(childTemp->getLeft());
				childTemp->setRight(temp->getRight());

				if (childTemp->getLeft() != nullptr)
					childTemp->getLeft()->setParent(temp->getParent());

				childTemp->setLeft(temp->getLeft());
				temp->getLeft()->setParent(childTemp);
			}
			else
				childTemp->setRight(temp->getRight());

			temp->getRight()->setParent(childTemp);
			fixHeight(childTemp);
			childTemp->setParent(parentTemp);

			if (parentTemp->getLeft() == temp)
				parentTemp->setLeft(childTemp);
			else
				parentTemp->setRight(childTemp);

			fixAllHights(parentTemp);

			delete temp;
		}
	}

	virtual Node* min(Node* current = nullptr)
	{
		if (root == nullptr)
			return nullptr;

		if (current == nullptr)
			current = root;

		while (current->getLeft() != nullptr)
			current = current->getLeft();

		return current;
	}

	virtual Node* max(Node* current = nullptr)
	{
		if (root == nullptr)
			return nullptr;

		if (current == nullptr)
			current = root;

		while (current->getRight() != nullptr)
			current = current->getRight();

		return current;
	}

	virtual Node* find(Residence dataTemp, Node* current)
	{
		if (current == nullptr)
			return nullptr;

		if (current->getData() == dataTemp)
			return current;

		if (current->getData() > dataTemp)
			return find(dataTemp, current->getLeft());

		if (current->getData() < dataTemp)
			return find(dataTemp, current->getRight());
	}

	virtual void preorder(Node* temp)
	{
		if (temp != nullptr)
			temp->print(temp);

		if (temp != nullptr && temp->getLeft() != nullptr)
			preorder(temp->getLeft());

		if (temp != nullptr && temp->getRight() != nullptr)
			preorder(temp->getRight());
	}

	virtual void inorder(Node* temp)
	{
		if (root == nullptr)
			return;

		if (temp != nullptr && temp->getLeft() != nullptr)
			inorder(temp->getLeft());

		if (temp != nullptr)
			temp->print(temp);

		if (temp != nullptr && temp->getRight() != nullptr)
			inorder(temp->getRight());
	}

	virtual void postorder(Node* temp)
	{
		if (temp->getLeft() != nullptr)
			postorder(temp->getLeft());

		if (temp->getRight() != nullptr)
			postorder(temp->getRight());

		if (temp != nullptr)
			temp->print(temp);
	}

	virtual Node* successor(Residence dataTemp)
	{
		Node* current = find(dataTemp, root);

		if (current == nullptr)
			return nullptr;

		if (current->getRight() != nullptr)
			return min(current->getRight());
		else
		{
			struct Node* succes = nullptr;
			struct Node* ances = root;

			while (ances != current)
			{
				if (current->getData() < ances->getData())
				{
					succes = ances;
					ances = ances->getLeft();
				}
				else
					ances = ances->getRight();
			}
			return succes;
		}
	}

	virtual Node* predcessor(Residence dataTemp)
	{
		Node* current = find(dataTemp, root);
		Node* temp = current;

		if (current == nullptr)
			return nullptr;
		else if (current == root && current->getLeft() == nullptr)
			return nullptr;
		else if (current->getLeft() != nullptr)
			return max(current->getLeft());
		else
		{
			while (temp->getParent() && temp->getParent()->getRight() != temp)
				temp = temp->getParent();

			return temp->getParent();
		}
	}
};

class AVL_Tree : public Tree
{
protected:
	int balanceFactor(Node* p)
	{
		int heightLeft = 0;
		int heightRight = 0;

		if (p->getLeft() != nullptr)
			heightLeft = p->getLeft()->getHeight();

		if (p->getRight() != nullptr)
			heightLeft = p->getRight()->getHeight();

		return (heightRight - heightLeft);
	}

	void fixHeight(Node* p)
	{
		int heightLeft = 0;
		int heightRight = 0;

		if (p->getLeft() != nullptr)
			heightLeft = p->getLeft()->getHeight();

		if (p->getRight() != nullptr)
			heightLeft = p->getRight()->getHeight();

		p->setHeight((heightLeft > heightRight ? heightLeft : heightRight) + 1);
	}

	Node* rotateRight(Node* p)
	{
		Node* q = p->getLeft();

		p->setLeft(q->getRight());

		if (q->getRight())
			q->getRight()->setParent(p);

		q->setRight(p);
		q->setParent(p->getParent());

		if (p->getParent() && p->getParent()->getLeft() == p)
			p->getParent()->setLeft(q);
		else if (p->getParent())
			p->getParent()->setRight(q);

		p->setParent(p);

		if (p == root)
		{
			root = q;
			root->setParent(nullptr);
		}

		fixHeight(p);
		fixHeight(q);

		return q;
	}

	Node* rotateLeft(Node* q)
	{
		Node* p = q->getRight();

		q->setLeft(p->getRight());

		if (p->getLeft())
			p->getLeft()->setParent(q);

		p->setLeft(q);
		p->setParent(q->getParent());

		if (q->getParent() && q->getParent()->getLeft() == q)
			q->getParent()->setLeft(p);
		else if (q->getParent())
			q->getParent()->setRight(p);

		q->setParent(q);

		if (q == root)
		{
			root = p;
			root->setParent(nullptr);
		}

		fixHeight(q);
		fixHeight(p);

		return p;
	}

	Node* balance(Node* p)
	{
		fixHeight(p);

		if (balanceFactor(p) == 2)
		{
			if (balanceFactor(p->getRight()) < 0)
				p->setRight(rotateRight(p->getRight()));

			return rotateLeft(p);
		}

		if (balanceFactor(p) == -2)
		{
			if (balanceFactor(p->getLeft()) > 0)
				p->setLeft(rotateLeft(p->getLeft()));

			return rotateRight(p);
		}

		return p;
	}

	void balanceAll(Node* p)
	{
		balance(p);

		while (p->getParent())
		{
			p = p->getParent();
			balance(p);
		}
	}

public:
	AVL_Tree() : Tree() {}

	virtual Node* add_r(Node* temp, Node* current = nullptr)
	{
		return balance(Tree::add_r(temp, current));
	}

	virtual void add(Residence tempData)
	{
		Node* temp = new Node;

		temp->setData(tempData);
		add_r(temp);
	}

	virtual void remove(Node* temp)
	{
		if (temp == nullptr)
			return;

		if (temp == root && temp->getLeft() == nullptr && temp->getRight() == nullptr)
		{
			delete temp;
			root = nullptr;
			return;
		}
		else if (temp == root && temp->getLeft() != nullptr && temp->getRight() == nullptr)
		{
			root = temp->getLeft();
			root->setHeight(0);
			root->setParent(nullptr);

			delete temp;
			return;
		}
		else if (temp == root && temp->getLeft() == nullptr && temp->getRight() != nullptr)
		{
			root = temp->getRight();
			root->setHeight(0);
			root->setParent(NULL);

			delete temp;
			return;
		}
		else if (temp->getLeft() != nullptr && temp->getRight() != nullptr)
		{
			Node* childTemp = Tree::max(temp->getLeft());

			if (childTemp->getParent()->getRight() == childTemp)
			{
				childTemp->getParent()->setRight(childTemp->getLeft());
				childTemp->setRight(temp->getRight());

				if (childTemp->getLeft() != nullptr)
					childTemp->getLeft()->setParent(temp->getParent());

				childTemp->setLeft(temp->getLeft());
				temp->getLeft()->setParent(childTemp);
			}
			else
				childTemp->setRight(temp->getRight());

			temp->getRight()->setParent(childTemp);

			Node* parentTemp = childTemp->getParent();

			childTemp->setParent(nullptr);
			root = childTemp;

			balanceAll(parentTemp);

			delete temp;
			return;
		}

		Node* parentTemp = temp->getParent();

		if (temp->getLeft() == nullptr && temp->getRight() == nullptr)
		{
			if (parentTemp->getLeft() == temp)
				parentTemp->setLeft(nullptr);
			else
				parentTemp->setRight(nullptr);

			fixAllHights(parentTemp);
			balanceAll(parentTemp);
			delete temp;
		}
		else if (temp->getLeft() != nullptr && temp->getRight() == nullptr)
		{
			if (parentTemp->getLeft() == temp)// Если сам - левый потомок parent'a
			{
				parentTemp->setLeft(temp->getLeft());
				temp->getLeft()->setParent(parentTemp);
			}
			else
			{
				parentTemp->setRight(temp->getLeft());
				temp->getLeft()->setParent(parentTemp);
			}

			fixAllHights(parentTemp);
			balanceAll(parentTemp);
			delete temp;
		}
		else if (temp->getLeft() == nullptr && temp->getRight() != nullptr)
		{
			if (parentTemp->getLeft() == temp)// Если сам - левый потомок parent'a
			{
				parentTemp->setLeft(temp->getRight());
				temp->getRight()->setParent(parentTemp);
			}
			else
			{
				parentTemp->setRight(temp->getRight());
				temp->getRight()->setParent(parentTemp);
			}

			fixAllHights(parentTemp);
			balanceAll(parentTemp);
			delete temp;
		}
		else if (temp->getLeft() != nullptr && temp->getRight() != nullptr)
		{
			Node* childTemp = Tree::max(temp->getLeft());

			if (childTemp->getParent()->getRight() == childTemp) 
			{
				childTemp->getParent()->setRight(childTemp->getLeft());
				childTemp->setRight(temp->getRight());

				if (childTemp->getLeft() != NULL)
					childTemp->getLeft()->setParent(childTemp->getParent());

				childTemp->setLeft(temp->getLeft());
				temp->getLeft()->setParent(childTemp);
			}
			else
				childTemp->setRight(temp->getRight());

			temp->getRight()->setParent(childTemp);
			fixHeight(childTemp);
			childTemp->setParent(parentTemp);

			if (parentTemp->getLeft() == temp)
				parentTemp->setLeft(childTemp);
			else
				parentTemp->setRight(childTemp);

			fixAllHights(parentTemp);
			balance(parentTemp);
			delete temp;
		}
	}

	virtual Node* LCA(Node* a, Node* b)
	{
		Node* p = root;
		Node* temp1 = a->getData() < b->getData() ? a : b;
		Node* temp2 = a->getData() > b->getData() ? a : b;

		while (true)
		{
			if (p->getData() >= temp1->getData() && p->getData() <= temp2->getData())
			{
				return p;
			}
			else if (p->getData() > temp1->getData() && p->getData() > temp2->getData())
				p = p->getLeft();
			else
				p = p->getRight();
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Residence H1("D", 2, 68, 54, 15000);
	Residence H2("F", 0, 158, 129, 40000);
	Residence H3("G", 1, 120, 98, 25000);
	Residence H4("E", 2, 101, 95, 20000);
	Residence H5("B", 3, 112, 103, 30000);
	Residence H6("A"), H7("C"), H8("L"), H9("K"), H10("M"), H11("N"), H12("O");
	Residence R[12] = { H1, H2, H3, H4, H5, H6, H7, H8, H9, H10, H11, H12 };
	Tree Tree1;
	AVL_Tree Tree2;

	for (int i = 0; i < 9; i++)
	{
		Tree1.add(R[i]);
		Tree2.add(R[i]);
	}

	Node* root = Tree2.getRoot();

//	Node* find1 = Tree2.find(Residence("Ленина 20"), Tree2.getRoot());
	//Node* find2 = Tree2.find(Residence("Ломоносова 14"), Tree2.getRoot());

	//Node* LCA = Tree2.LCA(find1, find2);

	cout << "Tree: \nRight: " << Tree1.getRoot()->getLeft()->getHeight() << " Left: " << Tree1.getRoot()->getRight()->getHeight() << endl;
	cout << "AVL Tree: \nRight: " << root->getLeft()->getHeight() << " Left: " << root->getRight()->getHeight();


	cout << endl << "INORDER " << endl;
	Tree2.inorder(Tree2.getRoot());

	return 0;
}