/*
	Практическая работа №6. Связные (связанные) списки.
*/

#include <iostream>

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

public:

	virtual Element* getBegin() { return begin; }
	virtual Element* getEnd() { return end; }
	virtual int getSize() { return size; }
	
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
};

int main()
{
	setlocale(LC_ALL, "ru");

	if (true)
	{
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

		for (int i = 0; i < 10; i++)
		{
			firstList.push(i);
			secondList.push(i * 2);
			thirdList.push(i * 5);
			fourthList.push(i * 10);
		}

		cout << "| Реализация исходных списков |" << endl << endl;

		cout << "- Элементы первого списка: ";
		firstList.print();
		cout << "- Размер списка: " << firstList.getSize() << endl << endl;

		cout << "- Элементы второго списка: ";
		secondList.print();
		cout << "- Размер списка: " << secondList.getSize() << endl << endl;

		cout << "- Элементы третьего списка: ";
		thirdList.print();
		cout << "- Размер списка: " << thirdList.getSize() << endl << endl;

		cout << "- Элементы четвертого списка: ";
		fourthList.print();
		cout << "- Размер списка: " << fourthList.getSize() << endl << endl;

		cout << "-------------------------------------------------------------------------------------------------------------------\n" << endl;
		
		cout << "| Реализация первого списка после работы функций удаления элемента |" << endl << endl;

		cout << "- Введите индекс элемента, который желаете удалить из списка: ";
		cin >> index;
		if (cin.fail() || index > firstList.getSize() - 1 || index < 0)
		{
			cout << endl << "- [ОШИБКА] Введенный индекс некорректен!" << endl;
			return 0;
		}
		cout << endl << "- Элементы первого списка (функцкия remove): ";
		firstList.remove(firstList[index]);
		firstList.print();
		cout << "- Размер списка: " << firstList.getSize() << endl << endl;

		cout << "- Элементы первого списка (функцкия pop_front): ";
		firstList.pop_front();
		firstList.print();
		cout << "- Размер списка: " << firstList.getSize() << endl << endl;

		cout << "- Элементы первого списка (функцкия pop_back): ";
		firstList.pop_back();
		firstList.print();
		cout << "- Размер списка: " << firstList.getSize() << endl << endl;

		cout << "- Элементы первого списка (функцкия pop_back_r): ";
		firstList.pop_back_r();
		firstList.print();
		cout << "- Размер списка: " << firstList.getSize() << endl << endl;

		cout << "-------------------------------------------------------------------------------------------------------------------\n" << endl;

		cout << "| Реализация второго списка после работы функции добавления элемента |" << endl << endl;

		cout << "- Введите индекс элемента, который желаете добавить в список: ";
		cin >> index;
		if (cin.fail() || index > secondList.getSize() - 1 || index < 0)
		{
			cout << endl << "- [ОШИБКА] Введенный индекс некорректен!" << endl;
			return 0;
		}
		cout << "- Введите значение элемента, которое желаете добавить в список: ";
		cin >> value;
		if (cin.fail())
		{
			cout << endl << "- [ОШИБКА] Введенное значение некорректно!" << endl;
			return 0;
		}
		cout << endl << "- Элементы второго списка (функцкия insert): ";
		secondList.insert(secondList[index], value);
		secondList.print();
		cout << "- Размер списка: " << secondList.getSize() << endl;
		
		cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;

		cout << "| Реализация третьего списка после работы функций поиска элемента |" << endl << endl;

		cout << "- Введите значение элемента, которое желаете найти в списке: ";
		cin >> key;
		if (cin.fail())
		{
			cout << endl << "- [ОШИБКА] Введенное значение некорректно!" << endl;
			return 0;
		}

		if (thirdList.find(key) == nullptr)
			cout << endl << "- [НЕУДАЧНО] Элемент " << key << " не был найден в третьем списке (функцкия find)!" << endl;
		else
			cout << endl << "- [УДАЧНО] Элемент " << key << " был найден в третьем списке (функцкия find)!" << endl;

		if (thirdList.find_r(key) == nullptr)
			cout << endl << "- [НЕУДАЧНО] Элемент " << key << " не был найден в третьем списке (функцкия find_r)!" << endl;
		else
			cout << endl << "- [УДАЧНО] Элемент " << key << " был найден в третьем списке (функцкия find_r)!" << endl;

		cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;

		cout << "| Реализация чертвертого списка после работы функции разбиения |" << endl << endl;

		cout << "- Введите индекс элемента, который будет являться границей разбиения списка: ";
		cin >> index;
		if (cin.fail() || index > fourthList.getSize() - 1 || index < 0)
		{
			cout << endl << "- [ОШИБКА] Введенный индекс некорректен!" << endl;
			return 0;
		}

		fourthList.split(fourthList[index], fourtListFirst, fourtListSecond);

		cout << endl << "- Элементы первой части четвертого списка (функция split): ";
		fourtListFirst->print();
		cout << "- Размер списка: " << index + 1 << endl;

		cout << endl << "- Элементы второй части четвертого списка (функция split): ";
		fourtListSecond->print();
		cout << "- Размер списка: " << fourthList.getSize() - index - 1 << endl;

		cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;

		cout << "| Реализация пятого списка после работы функции склеивания |" << endl << endl;

		cout << "- Элементы пятого списка (функцкия merge): ";
		fifthList.merge(fourtListFirst, fourtListSecond);
		fifthList.print();
		cout << "- Размер списка: " << fourthList.getSize() << endl;
	}

	return 0;
}
