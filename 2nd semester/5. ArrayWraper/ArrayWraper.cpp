/*
    Лабораторная работа №5 Обертка массива.
    Задача: Определение частоты встречи в массиве определенного элемента.
*/

#include <iostream>
#include <ctime>

using namespace std;

class MyArray
{
protected:
	int capacity;	// Переменная кол-ва выделяемой памяти
	int size;		// Переменная кол-ва используемой памяти
	double* ptr;	// Переменная создания массива
	int count;		// Переменная кол-ва совпадений
	int key;		// Переменная искомого значения

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
		{
			ptr[i] = arr[i];
		}
	}

	MyArray(const MyArray& a) // Конструктор копий
	{
		capacity = a.capacity;
		size = a.size;
		ptr = new double[capacity];

		for (int i = 0; i < size; i++)
		{
			ptr[i] = a.ptr[i];
		}
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
		if (index > size || index < 0)
		{
			cout << "[ОШИБКА] Введен неверный индекс!" << endl;
		}
		else
		{
			return ptr[index];
		}
	}

	MyArray& operator=(const MyArray& a)
	{
		capacity = a.capacity;
		size = a.size;
		ptr = new double[capacity];

		for (int i = 0; i < size; i++)
		{
			ptr[i] = a.ptr[i];
		}

		return *this;
	}

	int Capacity() // Метод обращения к полю capacity
	{
		return capacity; 
	}

	int Size() // Метод обращения к полю size
	{
		return size; 
	}

	double GetComponent(int index) // Метод генерации исключения, если индекс неправильный
	{
		if (index >= 0 && index < size)
		{
			return ptr[index];
		}

		return -1;
	}

	void SetComponent(int index, double value) // Метод генерации исключения, если индекс неправильный
	{
		if (index >= 0 && index < size)
		{
			ptr[index] = value;
		}
	}

	void AddValue(double value) // Метод добавления в конец нового значения
	{
		if (size < capacity)
		{
			ptr[size] = value;
			size++;
		}
	}

	void RemoveLastValue() // Метод удаления с конца элеменета массива
	{
		if (size >= 0)
		{
			size--;
		}
	}

	int Search(int key) // Метод поиска совпадений
	{
		for (int i = 0; i < size; i++)
		{
			if (key == ptr[i])
			{
				count++;
			}
		}

		return count;
	}

	void PrintArray() // Метод вывода массива
	{
		cout << "----------------------------------------------" << endl;
		cout << "Массив из " << size << " элементов:" << endl;
		cout << "[ ";

		for (int i = 0; i < size; i++)
		{
			cout << ptr[i] << " ";
		}

		cout << "]";
		cout << endl << "----------------------------------------------" << endl;
	}

	void PrintResult(int key) // Метод вывода результата
	{
		int res = Search(key);
		
		cout << "----------------------------------------------" << endl;
		if (res > 0)
		{ 
			cout << "Значение: " << key << " было встреченно в массиве " << res << " раз." << endl;
		}
		else
		{
			cout << "Значение: " << key << " было не найдено!" << endl;
		}
	}
};

int main() // Функция задачи: Определение частоты встречи в массиве определенного элемента.
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	int size;
	int key;
	
	if (true)
	{
		cout << "Введите значение размера массива: ";
		cin >> size;
		if (cin.fail() || size < 1)
		{
			cout << "----------------------------------------------" << endl;
			cout << "[ОШИБКА] Введено некорректное значение!" << endl;
			return 0;
		}

		MyArray a(size);

		for (int i = 0; i < size; i++)
		{
			a.AddValue(rand() % 10);
		}

		a.PrintArray();

		cout << "Введите искомое значение: ";
		cin >> key;
		if (cin.fail())
		{
			cout << "----------------------------------------------" << endl;
			cout << "[ОШИБКА] Введено некорректное значение!" << endl;
			return 0;
		}
		
		a.PrintResult(key);
	}
}