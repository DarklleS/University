#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip> 
#include <cmath>

using namespace std;

long long gcdExtended(long long a, long long b) // Расширенный алгоритм Евклида
{
    long long  p = 1, q = 0, r = 0, s = 1, x, y;

    while (a && b) 
    {
        if (a >= b) 
        {
            a = a - b;
            p = p - r;
            q = q - s;
        }
        else
        {
            b = b - a;
            r = r - p;
            s = s - q;
        }
    }

    if (a)
    {
        x = p;
        y = q;
    }
    else
    {
        x = r;
        y = s;
    }

    return x;
}

long long int gcd(long long int  a, long long int  b) // НОД
{
    long long int  temp;

    if (a < b) 
    { 
        temp = a; 
        a = b; 
        b = temp; 
    }

    while (b != 0) 
    {
        temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

void message(int p, double a, int n, long long* x, long long* y, double res) // Сообщение о состоянии работы программы
{
    cout << "---------------------------------------------------------" << endl;
    cout << "| ИНФОРМАЦИЯ О ВВЕДЕННЫХ ДАННЫХ |" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << " Поле вычетов по модулю: " << p << endl;
    cout << " Значение точки: " << a << endl;
    cout << " Степень многочлена: " << n << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << " Координаты всех точек:" << endl;
    cout << "     X" << " Y" << endl;
    for (int i = 0; i < n; i++)
        cout << " " << i + 1 << ") [" << x[i] << "," << y[i] << "]" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "| РЕЗУЛЬТАТ РАБОТЫ ПРОГРАММЫ |" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << " Значение интерполяционного многочлена Лагранжа: " << fixed << res << endl;
    cout << "---------------------------------------------------------" << endl;
}

int  main()
{
    setlocale(LC_ALL, "ru");

    long long p, a, n, numerator = 1, denominator = 1;
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> p; // Чтение значения модуля вычетов
    if (fin.fail())
    {
        cout << "В файле находится не верное значение!";
        return 0;
    }

    fin >> a; // Чтение значения точки
    if (fin.fail())
    {
        cout << "В файле находится не верное значение!";
        return 0;
    }

    fin >> n; // Чтение значения степени многочлена
    if (n < 1)
    {
        if (fin.fail())
        {
            cout << "В файле находится не верное значение!";
            return 0;
        }
        else
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "[ОШИБКА] Значение степени многочлена меньше 1!" << endl;
            cout << "-----------------------------------------------------" << endl;

            return 0;
        }
    }

    long long* x = new long long[n]; // Массив со значениями координат по оси Х
    long long* y = new long long[n]; // Массив со значениями координат по оси Y

    long long* temp = new long long;

    for (int i = 0; !fin.eof() && i < n; i++) // Чтение из файла значений координат точек
    {
        fin >> *temp;
        if (fin.fail())
        {
            cout << "В файле находится не верное значение!";
            return 0;
        }
        x[i] = *temp % p; // Присваивание координате Х

        fin >> *temp;
        if (fin.fail())
        {
            cout << "В файле находится не верное значение!";
            return 0;
        }
        y[i] = *temp % p; // Присваивание координате Y
    }

    delete temp;
    temp = nullptr;

    long int res = 0;

    for (long long int i = 0; i < n; i++) // Вычисление значения в точке a
    {
        for (long long int j = 0; j < n; j++)
        {
            if (x[j] != x[i])
            {
                long long int num = a - x[j];
                long long int den = x[i] - x[j];

                numerator *= (num);
                denominator *= (den);

                int gcdValue = gcd(numerator, denominator);

                numerator /= gcdValue;
                denominator /= gcdValue;
                numerator %= p;
                denominator %= p;
            }
        }

        numerator = y[i] * numerator % p;

        if (numerator < 0) // Eсли числитель меньше 0 добавляем р
            numerator = numerator + p;

        if (denominator < 0) // Eсли знаменатель меньше 0 добавляем р
            denominator = denominator + p;

        if (denominator != 1) 
        {
            long long int  temp = gcdExtended(denominator, p) % p;
            if (temp < 0)
                temp += p;

            res += numerator * temp % p;
        }

        numerator = 1;
        denominator = 1;
    }

    res %= p;
    fout << res;

    message(p, a, n, x, y, res); // Вывод результата работы программы

    delete[] x;
    x = nullptr;

    delete[] y;
    y = nullptr;

    fin.close();
    fout.close();
}