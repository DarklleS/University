/* 
Лабораторная работа №1. Одномерные массивы.
Вариант 20: Получить количество элементов, больших, чем среднее геометрическое в массиве.
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int valueComp(int arr[], int size)
{
    int mul = 1;
    float exp = 1.0 / size; // Переменная степени корня
    double avg;             // Переменная значения среднего геометрического
    unsigned int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 0)
        {
            mul = 0;
            break;
        }
        else
        {
            mul *= arr[i];
        }
    }
    avg = pow(mul, exp);

    for (int i = 0; i < size; i++)
        (arr[i] > avg) ? count++ : count;   // Cчет кол-ва элементов массива больших чем ср. геометрическое

    return count;
}

int main()
{
    setlocale(LC_ALL, "ru");

    unsigned int size = 5;
    int* arr = new int[size];
    int value;
    string str;
    string arrPath = "array.txt";
    string resPath = "result.txt";
    ifstream fileIn;
    ofstream fileOut;

    fileIn.open(arrPath);
    fileOut.open(resPath);

    cout << "Элементы массива:" << endl;
    cout << "----------------------------------------------" << endl;

    for (int i = 0; !fileIn.eof(); i++)
    {
        str = "";
        getline(fileIn, str);               // Считывание и присваивание строки
        arr[i] = stoi(str);                 // Конвертирование строки в число и добавление его в ячейку массива
        cout << str << endl;
    }

    value = valueComp(arr, size);

    cout << "----------------------------------------------" << endl;
    cout << "Кол-во чисел больше чем ср. геометрическое: " << value << endl;

    fileOut << value;                       // Запись файла с результатом

    fileIn.close();
    fileOut.close();
    delete[] arr;

    return 0;
}