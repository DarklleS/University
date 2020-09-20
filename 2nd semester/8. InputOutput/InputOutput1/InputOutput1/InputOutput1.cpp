#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

class MyArray
{
protected:
	int capacity; // Переменная кол-ва выделяемой памяти
	int size; // Переменная кол-ва используемой памяти
	double* ptr; // Переменная создания массива
	int count; // Переменная кол-ва совпадений
	double key; // Переменная искомого значения

public:
	void setKey(double value) { key = value; }
	void setSize(int value) { size = value; }
	void setCapacity(int value) { capacity = value; }

	int getSize() { return size; }
	int getCapacity() { return capacity; }

	MyArray() 
	{
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

	double getComponent(int index) // Метод генерации исключения, если индекс неправильный
	{
		if (index >= 0 && index < size)
		{
			return ptr[index];
		}

		return -1;
	}

	void setComponent(int index, double value) // Метод генерации исключения, если индекс неправильный
	{
		if (index >= 0 && index < size)
		{
			ptr[index] = value;
		}
	}

	void createArray()
	{
		srand(time(0));

		ptr = new double[capacity];
		count = 0;

		cout << "----------------------------------------------" << endl;
		cout << "Массив из " << capacity << " элементов:" << endl;

		for (int i = 0; i < capacity; i++)
		{
			ptr[i] = rand() % 6;
			cout << ptr[i] << " ";
			size++;
		}

		cout << endl << "----------------------------------------------" << endl;
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
		{
			size--;
		}
	}

	int search() // Метод поиска совпадений
	{
		count = 0;
		for (int i = 0; i < size; i++)
		{
			if (key == ptr[i])
			{
				count++;
			}
		}

		return count;
	}

	void printArray() // Метод вывода массива
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

	void printResult() // Метод вывода результата
	{
		int res = search();

		if (res > 0)
		{
			cout << "Значение: " << key << " было встреченно в массиве " << res << " раз." << endl;
		}
		else
		{
			cout << "Значение: " << key << " было не найдено!" << endl;
		}
	}

	friend ostream& operator << (ostream& ustream, MyArray& obj);
	friend istream& operator >> (istream& ustream, MyArray& obj);
};

ostream& operator << (ostream& ustream, MyArray& obj) // Перегрузка оператора вывода
{		
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.size << endl;
		for (int i = 0; i < obj.size; i++)
			ustream << obj[i] << " ";

		return ustream;
	}
	else
	{
		ustream << "Вывод массива из " << obj.size << " элементов:";
		ustream << endl << "------------------------------------------------------------------" << endl;

		for (int i = 0; i < obj.size; i++)
			ustream << "Значение " << i << ": " << obj[i] << endl;

		return ustream;
	}
}

istream& operator >> (istream& ustream, MyArray& obj) // Перегрузка оператора ввода
{
	if (obj.capacity < 1)
	{ 
		ustream >> obj.capacity;
		if (obj.capacity > 0)
			obj.ptr = new double[obj.capacity];
	}
	else
	{
		double k;
		ustream >> k;
		obj.addValue(k);
	}

	return ustream;
}

ostream& my_manip(ostream& ustream) // Манипулятор вывода
{
	ustream << fixed; // Избавление от экспоненты
	ustream << left;
	ustream.precision(2);
	ustream.width(5);
	
	return ustream;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	int size = 0;
	double key;
	MyArray a;
	MyArray b;
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	if (true)
	{
		a.setCapacity(size);
		a.setSize(size);

		// ===================== Работа с вводом из файла =====================

		while (!fin.eof())
		{
			if (fin.fail())
			{
				cout << "[ОШИБКА] В файле находится некорректное значение!" << endl;
				return 0;
			}
			fin >> a;
			if (a.getCapacity() < 1)
				break;
		}

		if (a.getSize() < 1)
		{
			cout << "[ОШИБКА] Введено некорректное значение размера массива!" << endl;
			return 0;
		}
		cout << my_manip << a;

		cout << "------------------------------------------------------------------" << endl;

		cout << "Введите искомое значение: ";
		cin >> key;
		if (cin.fail())
		{
			cout << "------------------------------------------------------------------" << endl;
			cout << "[ОШИБКА] Введено некорректное значение!" << endl;
			return 0;
		}
		else
			a.setKey(key);

		cout << "------------------------------------------------------------------" << endl;

		a.printResult();

		fout << my_manip << a;

		cout << "==================================================================" << endl;

		// ===================== Работа с вводом через консоль =====================
		cout << "Введите значение размер массива: ";
		cin >> b;
		if (cin.fail() || b.getCapacity() < 1)
		{
			cout << "------------------------------------------------------------------" << endl;
			cout << "[ОШИБКА] Введено некорректное значение!" << endl;
			return 0;
		}

		cout << "Введите значения элементов массива: " << endl;
		while (b.getSize() < b.getCapacity())
		{
			if (cin.fail())
			{
				cout << "------------------------------------------------------------------" << endl;
				cout << "[ОШИБКА] Введено некорректное значение!" << endl;
				return 0;
			}
			cin >> b;
		}

		cout << "------------------------------------------------------------------" << endl;

		cout << my_manip << b;

		fin.close();
		fout.close();
	}

	return 0;
}