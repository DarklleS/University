/*
	Лабораторная работа №7 Система обработки ошибок.
*/

#include <iostream>

using namespace std;

class Exception
{
protected:
	char* str;

public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	virtual void print()
	{
		cout << "Exception: " << str;
	}
};

// --- Пункт 1 ---
class IndexOutOfBounds : public Exception
{
protected:
	int key;

public:
	IndexOutOfBounds(int Key) : Exception("Введенный индекс - некорректен!")
	{
		key = Key;
	}

	virtual int getKey() { return key; }
	void setKey(int value) { key = value; }
};

class IndexMoreThanLength : public IndexOutOfBounds
{
public:
	IndexMoreThanLength(int value) : IndexOutOfBounds(getKey()) { setKey(value); }

	void print()
	{
		cout << "----------------------------------------------" << endl;
		cout << "Индекс: " << getKey() << endl;
		cout << "Сработало исключение: " << str << endl;
		cout << "Состояние: Значение индекса больше длины массива!" << endl;
	}
};

class NegativeIndex : public IndexOutOfBounds
{
public:
	NegativeIndex(int value) : IndexOutOfBounds(getKey()) { setKey(value); }

	void print()
	{
		cout << "----------------------------------------------" << endl;
		cout << "Индекс: " << key << endl;
		cout << "Сработало исключение: " << str << endl;
		cout << "Состояние: Значение индекса равно отрицательному числу!" << endl;
	}
};

class ZeroLengthArray : public IndexOutOfBounds
{
public:
	ZeroLengthArray(int value) : IndexOutOfBounds(getKey()) { setKey(value); }

	void print()
	{
		cout << "----------------------------------------------" << endl;
		cout << "Индекс: " << key << endl;
		cout << "Сработало исключение: " << str << endl;
		cout << "Состояние: Массив пуст!" << endl;
	}
};

// --- Пункт 2 ---
class CopyTooLargeArray : public Exception
{
private:
	int capacity;
	int size;

public:
	CopyTooLargeArray(int Capacity, int Size) : Exception("Размер присваемого массива больше самого массива!")
	{
		capacity = Capacity;
		size = Size;
	}

	void print()
	{
		cout << "Размер первого массива: " << capacity << endl;
		cout << "Размер второго массива: " << size << endl;
		cout << "Сработало исключение: " << str << endl;
		cout << "Состояние: Не хватает места для присваивания массива!" << endl;
	}
};

// --- Пункт 3 ---
class IncorrectValue : public Exception // Класс обработки корректности введенного значения (размер/эллементы массива)
{
public:
	IncorrectValue() : Exception("Введенное значение - некорректено!") {}

	void print()
	{
		cout << "Сработало исключение: " << str << endl;
		cout << "Состояние: Данный элемент введен не корректно!" << endl;
	}

};

class MyArray
{
protected:
	int res;
	int capacity;	// Переменная кол-ва выделяемой памяти
	int size;		// Переменная кол-ва используемой памяти
	double* ptr;	// Переменная создания массива
	int count;		// Переменная кол-ва совпадений
	double key;		// Переменная искомого значения

public:
	MyArray(int dim)
	{
		ptr = new double[dim];
		capacity = dim;
		size = 0;
	}

	MyArray(double* arr, int len) // Конструктор принимающий существующий массив
	{
		capacity = 2 * len;
		ptr = new double[capacity];
		size = len;
		for (int i = 0; i < size; i++)
			ptr[i] = arr[i];
	}

	MyArray(const MyArray& a) // Конструктор копий
	{
		capacity = a.capacity;
		size = a.size;
		ptr = new double[capacity];

		for (int i = 0; i < size; i++)
			ptr[i] = a.ptr[i];
	}

	~MyArray()
	{
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}

	double& operator[](int index)
	{
		if (index > size-1)
			throw IndexMoreThanLength(index);
		else if (index < 0)
			throw NegativeIndex(index);
		else if (capacity == 0)
			throw ZeroLengthArray(index);
		else
			return ptr[index];
	}

	MyArray& operator=(const MyArray& a)
	{
		size = a.size;
		ptr = new double[capacity];

		if (capacity < size)
			throw CopyTooLargeArray(capacity, size);
		else
		{
			for (int i = 0; i < size; i++)
				ptr[i] = a.ptr[i];

			return *this;
		}
	}

	int getCapacity() { return capacity; }

	int getSize() { return size; }

	double getComponent(int index) // Метод генерации исключения, если индекс неправильный
	{
		if (index >= 0 && index < size)
			return ptr[index];

		return -1;
	}

	void setComponent(int index, double value) // Метод генерации исключения, если индекс неправильный
	{
		if (index >= 0 && index < size)
			ptr[index] = value;
	}

	void addValue(double value) // Метод добавления в конец нового значения
	{
		if (size < capacity)
		{
			ptr[size] = value;
			size++;
		}
	}

	void removeLastValue() // Метод удаления с конца элеменета массива
	{
		if (size >= 0)
			size--;
	}

	int search(double key) // Метод поиска совпадений
	{
		for (int i = 0; i < size; i++)
			if (key == i)
			{
				res = ptr[i];
				break;
			}

		return res;
	}

	void printArray() // Метод вывода массива
	{
		cout << "----------------------------------------------" << endl;
		cout << "Массив из " << size << " элементов:" << endl;
		cout << "[ ";

		for (int i = 0; i < size; i++)
			cout << ptr[i] << " ";

		cout << "]";
		cout << endl << "----------------------------------------------" << endl;
	}

	void printResult(int key) // Метод вывода результата
	{
		if (getSize() == 0)
			throw ZeroLengthArray(key);
		else if (key > getSize()-1)
			throw IndexMoreThanLength(key);
		else if (key < 0)
			throw NegativeIndex(key);
		else
		{
			cout << "----------------------------------------------" << endl;
			cout << "Индекс: " << key << " хранит значение: " << ptr[key] << "!" << endl;
		}
	}
};

// --- Пункт 4 --- 
int main()
{
	setlocale(LC_ALL, "ru");

	int size;
	double key;
	char* item = new char[20];
	int value;

	if (true) 
	{
		try
		{
			cout << "Введите значение размера первого массива: ";
			cin >> size;
			if (cin.fail())
			{
				cout << "----------------------------------------------" << endl;
				throw IncorrectValue();
			}

			MyArray a(size);

			cout << "Введите значение элемента первого массива: " << endl;
			for (int i = 0; i < size; i++)
			{
				cin >> value;
				if (cin.fail())
				{
					cout << "----------------------------------------------" << endl;
					throw IncorrectValue();
				}
				else
					a.addValue(value);
			}

			a.printArray();

			cout << "Введите искомый индекс: ";
			cin >> key;
			if (cin.fail())
			{
				cout << "----------------------------------------------" << endl;
				throw IncorrectValue();
			}

			try
			{
				a.printResult(key);
			}
			catch (ZeroLengthArray & a)
			{
				a.print();
			}
			catch (IndexMoreThanLength & a)
			{
				a.print();
			}
			catch (NegativeIndex & a)
			{
				a.print();
			}

			cout << "----------------------------------------------" << endl;
			cout << "Введите значение размера второго массива: ";
			cin >> size;
			if (cin.fail())
			{
				cout << "----------------------------------------------" << endl;
				throw IncorrectValue();
			}

			cout << "----------------------------------------------" << endl;
			MyArray b(size);

			try
			{
				b = a;
				cout << "Присваивание прошло успешно!" << endl;
			}
			catch (CopyTooLargeArray & b)
			{
				b.print();
				return 0;
			}
		}
		catch (IncorrectValue & a)
		{
			a.print();
			return 0;
		}
	}
}