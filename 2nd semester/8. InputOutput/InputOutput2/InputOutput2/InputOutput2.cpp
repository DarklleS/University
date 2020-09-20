#include <iostream>
#include <fstream>

using namespace std;

class Element
{
private:
	Element* next;
	Element* prev;
	double data;

public:
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	virtual Element* getPrev() { return prev; }
	virtual void setPrev(Element* value) { prev = value; }

	virtual double getData() { return data; }
	virtual void setData(double value) { data = value; }
};

class LinkedListParent
{
protected:
	Element* begin;
	Element* end;
	int size;
	int capacity;
	bool flag = false;

public:

	virtual Element* getBegin() { return begin; }
	virtual Element* getEnd() { return end; }
	virtual int getSize() { return size; }
	virtual int getCapacity() { return capacity; }

	virtual void setCapacity(int value) { capacity = value; }

	LinkedListParent()
	{
		begin = nullptr;
		end = nullptr;
		size = 0;
	}

	~LinkedListParent() {}

	LinkedListParent(const LinkedListParent& item) // Конструктор копий
	{
		begin = nullptr;
		size = 0;
		Element* cur = item.begin;

		while (cur != nullptr)
		{
			push(cur->getData());
			cur = cur->getNext();
		}

		delete cur;
	}

	virtual LinkedListParent& operator=(const LinkedListParent& item) // Перегрузка оператора =
	{
		begin = nullptr;
		end = nullptr;

		Element* cur = item.begin;

		while (cur != nullptr)
		{
			push(cur->getData());
			cur = cur->getNext();
		}

		delete cur;

		return *this;
	}

	virtual Element* operator[](int i) // Перегрузка оператора []
	{
		Element* cur = begin;

		if (i < 0 || i > size)
			return nullptr;

		for (int k = 0; k < i; k++)
			cur = cur->getNext();

		return cur;
	}


	virtual Element* push(double value) // Метод добавления элемента в конец списка
	{
		Element* cur = begin;

		if (begin == nullptr) // Если в списке нет элементов - перемещаем элемент в начало
		{
			size = 1;
			begin = new Element;
			end = begin;

			begin->setData(value);
			begin->setNext(nullptr);
			begin->setPrev(nullptr);

			return begin;
		}

		while (cur->getNext() != nullptr) // Поиск последнего элемента
			cur = cur->getNext();

		size++;

		cur->setNext(new Element);
		cur->getNext()->setData(value);
		cur->getNext()->setNext(nullptr);
		cur->getNext()->setPrev(cur);

		end = cur->getNext();

		return cur->getNext();
	}

	virtual Element* push_r(double value, Element* current = nullptr) // Метод добавления элемента в конец списка (рекурсивно)
	{
		if (begin == nullptr) // Если в списке нет элементов - перемещаем элемент в начало
		{
			size = 1;
			begin = new Element;
			end = begin;

			begin->setData(value);
			begin->setNext(nullptr);

			return begin;
		}

		if (current == nullptr) // Если ничего не передано - начинаем поиск сводобного места с начала
			current = begin;

		if (current->getNext() != nullptr) // Если находимся в списке - начинам поиск элемента
			return push_r(value, current->getNext());

		if (current->getNext() == nullptr) // Если указатель на следующий элемент свободен - добавляем новый (конец рекурсии)
		{
			current->setNext(new Element);
			current->getNext()->setData(value);
			current->getNext()->setNext(nullptr);

			end = current;

			size++;

			return current->getNext();
		}
	}

	virtual double pop_back() // Метод удаления элемента с конца списка
	{
		Element* cur = begin;
		Element* prev = nullptr;
		double res;

		if (begin == nullptr)
			return -1;

		if (size == 1)
		{
			res = begin->getData();
			size--;
			return res;
		}

		while (cur->getNext() != nullptr) // Поиск последнего и предпоследнего элемента
		{
			prev = cur;
			cur = cur->getNext();
		}

		res = cur->getData();
		end = cur->getPrev();

		prev->setNext(nullptr);

		delete cur;

		size--;

		return res;
	}

	virtual double pop_back_r(Element* current = nullptr) // Метод удаления элемента с конца списка (рекурсивно)
	{
		double res;

		if (size == 1)
		{
			res = begin->getData();
			size--;
			return res;
		}

		if (current == nullptr)
			current = begin;

		if (current->getNext() != nullptr)
			return pop_back_r(current->getNext());

		if (current->getNext() == nullptr)
		{
			res = current->getData();

			current->getPrev()->setNext(nullptr);
			delete current;

			size--;

			return res;
		}
	}

	virtual void pop_front() // Метод удаления элемента с начала списка
	{
		Element* cur = begin;

		if (size > 1)
			begin = begin->getNext();

		size--;

		delete cur;
	}

	virtual void print() // Метод вывода списка
	{
		Element* cur = begin;

		while (cur != nullptr)
		{
			cout << cur->getData() << " ";
			cur = cur->getNext();
		}
		cout << endl;
	}

	virtual void print_r(Element* current = nullptr) // Метод вывода списка (рекурсивно)
	{
		if (current == nullptr)
			current = begin;

		if (current != nullptr)
		{
			cout << current->getData() << " ";

			if (current->getNext() != nullptr)
				print_r(current->getNext());
		}
	}
};

class LinkedListChild : public LinkedListParent
{
public:
	LinkedListChild() : LinkedListParent() {}
	~LinkedListChild() {}

	LinkedListChild(const LinkedListChild& list) // Конструктор копий
	{
		begin = nullptr;
		Element* cur = list.begin;

		while (cur != nullptr)
		{
			push(cur->getData());
			cur = cur->getNext();
		}

		delete cur;
	}

	LinkedListChild& operator=(const LinkedListChild& item) // Перегрузка оператора =
	{
		begin = nullptr;
		Element* cur = item.begin;

		while (cur != nullptr)
		{
			push(cur->getData());
			cur = cur->getNext();
		}

		delete cur;

		return *this;
	}

	virtual Element* insert(Element* current, double value) // Метод добавления нового элемента в произвольное место списка
	{
		Element* item = new Element;

		item->setNext(current->getNext());
		item->setData(value);
		item->setPrev(current);
		current->setNext(item);

		if (current == end)
			end = current->getNext();

		size++;

		return item;
	}

	void remove(Element* current) // Метод удаления элемента из произвольного места списка
	{
		if (current != nullptr)
		{
			if (current == getBegin())
			{
				pop_front();
			}
			else if (current->getNext() != nullptr)
			{
				current->getPrev()->setNext(current->getNext());
				current->getNext()->setPrev(current->getPrev());

				delete current;
			}
			else
			{
				current->getPrev()->setNext(nullptr);

				delete current;
			}

			if (current == end)
				end = current->getPrev();

			size--;
		}
	}

	Element* find(double key) // Метод поиска элемента в списке
	{
		Element* cur = begin;

		while (cur != nullptr)
		{
			if (cur->getData() == key)
				return cur;

			cur = cur->getNext();
		}

		return nullptr;
	}

	Element* find_r(double key, Element* current = nullptr) // Метод поиска элемента в списке (рекурсивно)
	{
		if (current == nullptr)
			current = begin;

		if (begin->getData() == key)
		{
			current = begin;
			return current;
		}

		if (end->getData() == key)
		{
			current = end;
			return current;
		}

		if (current->getData() == key)
			return current;

		if (current != nullptr)
			if (current->getNext() == nullptr)
				return nullptr;
			else
				return find_r(key, current->getNext());
	}

	void split(Element* delimiter, LinkedListChild* List1, LinkedListChild* List2) // Метод разбиения списка
	{
		List1->begin = begin;
		List1->end = delimiter;

		List2->begin = delimiter->getNext();
		List2->end = end;

		List1->end->setNext(nullptr);
	}

	void merge(LinkedListChild* List1, LinkedListChild* List2) // Метод склеивания списка
	{
		begin = List1->begin;
		end = List1->end;

		end->setNext(List2->begin);

		end = List2->end;

		size = List1->size + List2->size;
	}

	friend ostream& operator << (ostream& ustream, LinkedListChild& obj);
	friend istream& operator >> (istream& ustream, LinkedListChild& obj);
};

ostream& operator << (ostream& ustream, LinkedListChild& obj) // Перегрузка оператора вывода
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.size << endl;

		for (int i = 0; i < obj.size; i++)
			ustream << obj[i]->getData() << " ";

		return ustream;
	}
	else
	{
		ustream << "Вывод списка из " << obj.size << " элементов:";
		ustream << endl << "------------------------------------------------------------------" << endl;

		for (int i = 0; i < obj.size; i++)
			ustream << "Значение " << i << ": " << obj[i]->getData() << endl;

		return ustream;
	}
}

istream& operator >> (istream& ustream, LinkedListChild& obj) // Перегрузка оператора ввода
{
	if (obj.capacity < 1 && obj.size < 1)
	{
		ustream >> obj.capacity;
	}
	else
	{
		double k;
		ustream >> k;
		obj.push(k);
		obj.capacity--;
	}

	return ustream;
}

ostream& my_manip(ostream& ustream) // Манипулятор вывода
{
	ustream << fixed; // Избавление от экспоненты
	ustream << left;
	ustream.width(5);
	ustream.precision(2);

	return ustream;
}

int main()
{
	setlocale(LC_ALL, "ru");

	/*
	LinkedListChild firstList;
	LinkedListChild secondList;
	LinkedListChild thirdList;
	LinkedListChild fourthList;
	LinkedListChild fifthList;
	LinkedListChild* fourtListFirst = new LinkedListChild;
	LinkedListChild* fourtListSecond = new LinkedListChild;
	int index;
	double value;
	double key;
	*/

	unsigned int size;
	LinkedListChild L1;
	LinkedListChild L2;
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	if (true)
	{
		// ===================== Работа с вводом из файла =====================
		while (!fin.eof())
		{
			if (fin.fail())
			{
				cout << "[ОШИБКА] В файле находится некорректное значение!" << endl;
				return 0;
			}
			fin >> L1;

			if (L1.getCapacity() < 1)
				break;
		}

		if (L1.getSize() < 1)
		{
			cout << "[ОШИБКА] Введено некорректное значение размера списка!" << endl;
			return 0;
		}

		cout << my_manip << L1;
		fout << my_manip << L1;

		fin.close();
		fout.close();

		cout << "==================================================================" << endl;

		// ===================== Работа с вводом через консоль =====================

		cout << "Введите значение длины списка: ";
		cin >> L2;
		if (cin.fail())
		{
			cout << "------------------------------------------------------------------" << endl;
			cout << "[ОШИБКА] Введено некорректное значение!" << endl;
			return 0;
		}
		if (L2.getCapacity() < 1)
		{
			cout << "------------------------------------------------------------------" << endl;
			cout << "[ОШИБКА] Введено некорректное значение размера списка!" << endl;
			return 0;
		}

		cout << "Введите значения элементов списка: " << endl;
		while (L2.getCapacity())
		{
			cin >> L2;
			if (cin.fail())
			{
				cout << "------------------------------------------------------------------" << endl;
				cout << "[ОШИБКА] Введено некорректное значение!" << endl;
				return 0;
			}
		}

		cout << "------------------------------------------------------------------" << endl;
			
		cout << L2;
	}

	return 0;
}