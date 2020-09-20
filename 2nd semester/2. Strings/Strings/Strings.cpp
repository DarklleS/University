/* 
Лабораторная работа №2. Строки.
Вариант 20: Написать функцию trim(), удаляющую все пробелы в начале и конце строки.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char* trim(char* str, unsigned int& size, ofstream &fileOut)
{
    int left = 0;
    int right = size - 1;
    int count = 0;

    while (str[left] == ' ' || str[right] == ' ') // Поиск пробелов в начале и конце
    {
        if (str[left] == ' ')
            left++;
        if (str[right] == ' ')
            right--;
    }

    size = right - left + 1;
    char* res = new char[size + 1];

    for (int i = 0; i < size; i++) // Запись нового массива строки
    {
        res[i] = str[left];
        fileOut << res[i];
        left++;
        count++;
    }
    res[count] = '\0';

    return res;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    char symbol;
    unsigned int size = 0;
    string strPath = "string.txt";
    string resPath = "result.txt";
    ofstream fileOut;
    ifstream fileIn;

    fileIn.open(strPath);
    fileOut.open(resPath);

    while (fileIn.get(symbol)) // Счет кол-ва эллементов строки для выделения подходящего кол-ва памяти под массив
        size++;

    fileIn.close();
    fileIn.open(strPath);

    char* str = new char[size];

    // Вывод не обработанной строки
    cout << "Текст до работы функции trim(): " << endl;

    for (int i = 0; fileIn.get(str[i]); i++) // Запись исходного массива строки
        cout << str[i];

    cout << endl << "\n--------------------------------------------------------------------------------\n" << endl;

    // Вывод обработанной строки
    cout << "Текст после работы функции trim(): " << endl;

    char* res = trim(str, size, fileOut);
    cout << res << endl;
    
    fileIn.close();
    fileOut.close();
    delete[] str;
    delete[] res;
}