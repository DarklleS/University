#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;

class Point2D // Реализация класса "Point2D" | Задача 1.1.
{
private:
	int x, y;
	double distance;

public:
	Point2D() :
		x(0),
		y(0),
		distance(0) {}

	Point2D(int x, int y) :
		x(x),
		y(y),
		distance(sqrt(x* x + y * y)) {}

	int getX() { return this->x; }
	int getY() { return this->y; }
	double getDistance() { return this->distance; }

	bool operator ==(const Point2D& temp) { return this->x == temp.x && this->y == temp.y && this->distance == temp.distance; }
	bool operator >(const Point2D& temp) { return this->distance > temp.distance; }
	bool operator <(const Point2D& temp) { return this->distance < temp.distance; }
	bool operator >=(const Point2D& temp) { return this->distance >= temp.distance; }
	bool operator <=(const Point2D& temp) { return this->distance <= temp.distance; }

	friend ostream& operator<< (ostream& ustream, Point2D& obj);
};

ostream& operator<< (ostream& ustream, Point2D& obj)
{
	if (&obj)
		cout << "X:\t\t" << obj.getX() << endl
			 << "Y:\t\t" << obj.getY() << endl
			 << "Distance:\t" << obj.getDistance() << endl;

	return ustream;
}

class State // Реализация класса "Государство" | Задача 1.2.
{
private:
	string name, capital, language;
	unsigned population, area;

public:
	State() :
		name("NaN"),
		capital("NaN"),
		language("NaN"),
		population(0),
		area(0) {}

	State(string name, string capital, string language, unsigned population, unsigned area) :
		name(name),
		capital(capital),
		language(language),
		population(population),
		area(area) {}

	string getName() { return this->name; }
	string getCapital() { return this->capital; }
	string getLanguage() { return this->language; }
	unsigned getPopulation() { return this->population; }
	unsigned getArea() { return this->area; }

	bool operator ==(const State& temp) { return this->population == temp.population && this->area == temp.area && this->name == temp.name; }

	bool operator >(const State& temp)
	{ 
		return this->population != temp.population ? this->population > temp.population :
			   this->area != temp.area ? this->area > temp.area :
			   this->name != temp.name ? this->name < temp.name : false;
	}

	bool operator <(const State& temp)
	{
		return this->population != temp.population ? this->population < temp.population :
			   this->area != temp.area ? this->area < temp.area :
			   this->name != temp.name ? this->name > temp.name : false;
	}

	bool operator >=(const State& temp)
	{
		return !(this->population < temp.population) ? (this->population > temp.population) || (this->population == temp.population) :
			   !(this->area < temp.area) ? (this->area > temp.area) || (this->area == temp.area) :
			   !(this->name < temp.name) ? (this->name < temp.name) || (this->name == temp.name) : false;
	}

	bool operator <=(const State& temp)
	{
		return !(this->population > temp.population) ? (this->population < temp.population) || (this->population == temp.population) :
			   !(this->area > temp.area) ? (this->area < temp.area) || (this->area == temp.area) :
			   !(this->name > temp.name) ? (this->name > temp.name) || (this->name == temp.name) : false;
	}

	friend ostream& operator<< (ostream& ustream, State& obj);
};

ostream& operator<< (ostream& ustream, State& obj)
{
	if (&obj)
		cout << "State:\t\t" << obj.name << endl
			 << "Capital:\t" << obj.capital << endl
			 << "Language:\t" << obj.language << endl
			 << "Population:\t" << obj.population << endl
			 << "Area:\t\t" << obj.area << endl;

	return ustream;
}

template <class T>
class Element
{
private:
	Element* next;
	Element* prev;
	T field;

public:
	Element() : next(nullptr), prev(nullptr), field(0) {}
	Element(T value) : next(nullptr), prev(nullptr), field(value) {}

	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);
};

template<class T>
ostream& operator<< (ostream& ustream, Element<T>& obj)
{
	if(&obj)
		ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected:
	Element<T>* head;
	Element<T>* tail;
	int num;

public:
	virtual int getNumber() { return num; }
	virtual Element<T>* getBegin() { return head; }
	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent() :
		head(nullptr),
		tail(nullptr),
		num(0) {}

	~LinkedListParent() {}

	virtual Element<T>* push(T value) = 0;
	virtual Element<T>* pop() = 0;

	virtual Element<T>* operator[](int i)
	{
		if (i < 0 || i > num) 
			return nullptr;

		Element<T>* cur = head;

		for (int j = 0; j < i; j++)
			cur = cur->getNext();

		return cur;
	}

	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
	Element<ValueType>* ptr;

public:
	ListIterator() { ptr = nullptr; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	Element<ValueType>* getPtr() { return ptr; }

	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }

	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const { return ptr == other.ptr; }

	Element<ValueType>& operator*() { return ptr ? *ptr : nullptr; }

	ListIterator& operator++() 
	{
		if (ptr && ptr->getNext())
			ptr = ptr->getNext();

		return *this;
	}
	ListIterator& operator++(int v)
	{
		if (ptr && ptr->getNext())
			ptr = ptr->getNext();

		return *this;
	}

	ListIterator& operator--()
	{
		if (ptr && ptr->getPrevious())
			ptr = ptr->getPrevious();

		return *this;
	}
	ListIterator& operator--(int v)
	{
		if (ptr && ptr->getPrevious())
			ptr = ptr->getPrevious();

		return *this;
	}
};

template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>() {}
	virtual ~IteratedLinkedList() {}

	ListIterator<T> iterator;

	ListIterator<T> begin() { ListIterator<T> it = LinkedListParent<T>::head; return it; }
	ListIterator<T> end() { ListIterator<T> it = LinkedListParent<T>::tail; return it; }

	template<class T> friend ostream& operator<< (ostream& ustream, IteratedLinkedList<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, IteratedLinkedList<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, IteratedLinkedList<T>& obj)
{
	ListIterator<T> it = obj.getBegin();
	size_t i = 0;
	T temp;

	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << "==============================" << endl;
		ustream << "Length of Linked List: " << obj.num << endl;
		ustream << "==============================";

		for (; i < obj.getNumber(); ++it, ++i)
		{
			temp = it.getPtr()->getValue();

			ustream << "Element " << i + 1 << ":" << endl;
			ustream << temp;

			if (i < obj.getNumber() - 1)
				cout << "------------------------------" << endl;
		}
	}
	else
	{
		ustream << "==============================" << endl;
		ustream << "Length of Linked List: " << obj.num << endl;
		ustream << "==============================";

		ustream << endl;

		for (; i < obj.getNumber(); ++it, ++i)
		{
			temp = it.getPtr()->getValue();

			ustream << "Element " << i + 1 << ":" << endl;
			ustream << temp;

			if(i < obj.getNumber() - 1)
				cout << "------------------------------" << endl;
		}
	}

	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, IteratedLinkedList<T>& obj)
{
	int len;
	ustream >> len;

	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

template <class T>
class Stack : public IteratedLinkedList<T>
{
public:
	Stack() : IteratedLinkedList<T>() {}

	virtual Element<T>* pop()
	{
		if (!LinkedListParent<T>::tail)
			return nullptr;

		if (LinkedListParent<T>::num == 1)
			LinkedListParent<T>::head = LinkedListParent<T>::tail = nullptr;
		else
		{
			Element<T>* newElem = LinkedListParent<T>::tail->getPrevious();
			newElem->setNext(nullptr);
			LinkedListParent<T>::tail->setPrevious(nullptr);
			LinkedListParent<T>::tail = newElem;
		}

		LinkedListParent<T>::num--;

		return LinkedListParent<T>::tail;
	}

	virtual Element<T>* push(T value)
	{
		Element<T>* newElem = new Element<T>(value);

		if (!LinkedListParent<T>::tail)
			LinkedListParent<T>::tail = LinkedListParent<T>::head = newElem;
		else
		{
			LinkedListParent<T>::tail->setNext(newElem);
			newElem->setPrevious(LinkedListParent<T>::tail);
			LinkedListParent<T>::tail = newElem;
		}

		LinkedListParent<T>::num++;

		return newElem;
	}

	virtual Element<T>* top() { return LinkedListParent<T>::tail; }
};

template <class T>
class SortedStack : public Stack<T>
{
public:
	SortedStack() : Stack<T>() {}

	virtual Element<T>* push(T value)
	{
		Element<T>* newElem = new Element<T>(value);
		Element<T>* current = LinkedListParent<T>::head;

		if (!LinkedListParent<T>::tail)
			LinkedListParent<T>::tail = LinkedListParent<T>::head = newElem;
		else if (value < LinkedListParent<T>::head->getValue())
		{
			LinkedListParent<T>::head->setPrevious(newElem);
			newElem->setNext(LinkedListParent<T>::head);
			LinkedListParent<T>::head = newElem;
		}
		else if (value > LinkedListParent<T>::tail->getValue())
		{
			LinkedListParent<T>::tail->setNext(newElem);
			newElem->setPrevious(LinkedListParent<T>::tail);
			LinkedListParent<T>::tail = newElem;
		}
		else
		{
			while (current != LinkedListParent<T>::tail)
			{
				if (value > current->getValue() && value <= current->getNext()->getValue())
				{
					newElem->setNext(current->getNext());
					current->setNext(newElem);
					newElem->setPrevious(current);
					newElem->getNext()->setPrevious(newElem);

					break;
				}
				else
					current = current->getNext();
			}
		}

		LinkedListParent<T>::num++;

		return newElem;
	}
};

template<class T>
void push(list<T>& l, T& const newTemp) // Функция добавления элемента в список
{
	auto it = l.cbegin();

	for (; it != l.cend(); ++it)
		if (newTemp > *it)
		{
			l.insert(it, newTemp);
			return;
		}

	l.insert(it, newTemp);
}

template<class T>
void pop(list<T>& l, T& const deleteTemp) // Функция удаления элемента из списка
{
	for (auto it = l.cbegin(); it != l.cend(); ++it)
		if (deleteTemp == *it)
		{
			l.erase(it);
			return;
		}
}

bool inSquare(Point2D& const point) // Предикат проверки нахождения объекта класса Point2D в единичном квадрате
{ 
	return point.getX() >= 0 && point.getX() <= 1 &&
		   point.getY() >= 0 && point.getY() <= 1; 
}

list<Point2D> filter(list<Point2D>& l, bool (*f)(Point2D& const)) // Функция перезаписи списка с элементами класса Point2D, которые лежат в единичном квадрате
{
	list<Point2D> newList;

	for (auto it : l)
		if (f(it))
			push(newList, it);

	return newList;
}

void printPoint(const list<Point2D>& l) // Вывод объекта класса Point2D
{
	int i = 1;

	for (auto it : l)
	{
		cout << "Point " << i << ":" << endl
			 << "X:\t\t" << it.getX() << endl
			 << "Y:\t\t" << it.getY() << endl
			 << "Distance:\t" << it.getDistance() << endl;

		if (i != l.size())
			cout << "------------------------------" << endl;
		
		i++;
	}
}

void printState(const list<State>& l) // Вывод объекта класса State
{
	int i = 1;

	for (auto it : l)
	{
		cout << "State " << i << ":" << endl
			 << "Name:\t\t" << it.getName() << endl
			 << "Capital:\t" << it.getCapital() << endl
			 << "Language:\t" << it.getLanguage() << endl
			 << "Population:\t" << it.getPopulation() << endl
		     << "Area:\t\t" << it.getArea() << endl;

		if (i != l.size())
			cout << "------------------------------" << endl;

		i++;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "|----------------------------|" << endl;
	cout << "|======= ЗАДАНИЕ 1.1. =======|" << endl;
	cout << "|----------------------------|" << endl;

	list<Point2D> points;
	Point2D P1(1, 2);
	Point2D P2(4, 4);
	Point2D P3(9, 1);
	Point2D P4(0, 0);
	Point2D P5(1, 0);

	push(points, P1);
	push(points, P2);
	push(points, P3);
	push(points, P4);
	push(points, P5);

	cout << endl;

	cout << "==============================" << endl;
	cout << "List after push(): " << endl;
	cout << "==============================" << endl;
	printPoint(points);

	cout << endl;

	pop(points, P1);
	cout << "==============================" << endl;
	cout << "List after pop(): " << endl;
	cout << "==============================" << endl;
	printPoint(points);

	cout << endl;

	list<Point2D> newPoints = filter(points, inSquare);
	cout << "==============================" << endl;
	cout << "List after filter(): " << endl;
	cout << "==============================" << endl;
	printPoint(newPoints);

	cout << endl;

	cout << "|----------------------------|" << endl;
	cout << "|======= ЗАДАНИЕ 1.2. =======|" << endl;
	cout << "|----------------------------|" << endl;

	list<State> states;
	State S1("Russia", "Moscow", "Russian", 144, 17100);
	State S2("France", "Paris", "French", 67, 643);
	State S3("USA", "Washington DC", "English", 328, 9843);
	State S4("Germany", "Berlin", "German", 83, 357);
	State S5("Japan", "Tokyo", "Japanese", 126, 377);
	State S6("China", "Beijing", "Chinese", 1393, 9597);

	push(states, S1);
	push(states, S2);
	push(states, S3);
	push(states, S4);
	push(states, S5);
	push(states, S6);

	cout << endl;

	cout << "==============================" << endl;
	cout << "List after push(): " << endl;
	cout << "==============================" << endl;
	printState(states);

	cout << endl;

	pop(states, S2);
	pop(states, S6);
	cout << "==============================" << endl;
	cout << "List after pop(): " << endl;
	cout << "==============================" << endl;
	printState(states);

	cout << endl;

	cout << "|----------------------------|" << endl;
	cout << "|======= ЗАДАНИЕ 1.3. =======|" << endl;
	cout << "|----------------------------|" << endl;

	cout << endl;

	cout << "===============================" << endl;
	cout << "Top Stack elements after pop(): " << endl;
	cout << "===============================";

	Stack<Point2D> stackFirst;

	stackFirst.push(P1);
	stackFirst.push(P2);
	stackFirst.push(P3);
	stackFirst.push(P4);
	stackFirst.push(P5);

	cout << endl << *stackFirst.top();
	stackFirst.pop();
	cout << "------------------------------";
	cout << endl << *stackFirst.top();
	stackFirst.pop();
	cout << "------------------------------";
	cout << endl << *stackFirst.top();
	stackFirst.pop();
	cout << "------------------------------";
	cout << endl << *stackFirst.top();
	stackFirst.pop();
	cout << "------------------------------";
	cout << endl << *stackFirst.top();
	stackFirst.pop();

	cout << endl;

	cout << "=====================================" << endl;
	cout << "Top SortedStack elements after pop(): " << endl;
	cout << "=====================================";

	SortedStack<State> sortedStackFirst;

	sortedStackFirst.push(S1); // Russia
	sortedStackFirst.push(S2); // France
	sortedStackFirst.push(S3); // USA
	sortedStackFirst.push(S4); // Germany
	sortedStackFirst.push(S5); // Japan
	sortedStackFirst.push(S6); // China

	cout << endl << *sortedStackFirst.top();
	sortedStackFirst.pop();
	cout << "------------------------------";
	cout << endl << *sortedStackFirst.top();
	sortedStackFirst.pop();
	cout << "------------------------------";
	cout << endl << *sortedStackFirst.top();
	sortedStackFirst.pop();
	cout << "------------------------------";
	cout << endl << *sortedStackFirst.top();
	sortedStackFirst.pop();
	cout << "------------------------------";
	cout << endl << *sortedStackFirst.top();
	sortedStackFirst.pop();
	cout << "------------------------------";
	cout << endl << *sortedStackFirst.top();
	sortedStackFirst.pop();

	cout << endl;

	cout << "|----------------------------|" << endl;
	cout << "|======= ЗАДАНИЕ 1.4. =======|" << endl;
	cout << "|----------------------------|" << endl;

	cout << endl;

	Stack<State> stackSecond;

	stackSecond.push(S1); // Russia
	stackSecond.push(S2); // France
	stackSecond.push(S3); // USA
	stackSecond.push(S4); // Germany
	stackSecond.push(S5); // Japan
	stackSecond.push(S6); // China

	cout << stackSecond;

	cout << endl;

	cout << "|----------------------------|" << endl;
	cout << "|======= ЗАДАНИЕ 1.5. =======|" << endl;
	cout << "|----------------------------|" << endl;

	cout << endl;

	SortedStack<State> sortedStackSecond;

	sortedStackSecond.push(S1); // Russia
	sortedStackSecond.push(S2); // France
	sortedStackSecond.push(S3); // USA
	sortedStackSecond.push(S4); // Germany
	sortedStackSecond.push(S5); // Japan
	sortedStackSecond.push(S6); // China

	cout << sortedStackSecond;
}