#include <iostream>
#include<cstdio>
#include <cstring>
#include <QString>
#include <math.h>
#include <cmath>

using namespace std;

int main()
{
    while(true) // бесконечный цикл, чтобы программа работала, пока не будут введены правильные данные
    {
        double op1, op2, res;
        char input1[10000], input2[10000];
        QString conver1, conver2, converCalc; // Переменная конвертации переменной ввода позиции
        bool flag1, flag2;  // Переменная проверки конвертации
        char calc[100];
        int errorCode=9;


        try
        {
            cout << "\nВведите первый операнд: ";
            gets(input1);

            conver1.append(input1); // Конвертация массива с эллементами чисел в целое число
            op1 = conver1.toDouble(&flag1); // Присваивание переменной искомой позиции конвертации значений массива

            if(flag1 == 0) // Проверка на превышение диапозона, нулевую позицию и удачную конвертацию
            {
                errorCode = 1;
                throw invalid_argument("");
            }

            cout << "Введите второй операнд: ";
            gets(input2);

            conver2.append(input2); // Конвертация массива с эллементами чисел в целое число
            op2 = conver2.toDouble(&flag2); // Присваивание переменной искомой позиции конвертации значений массива

            if(flag2 == 0) // Проверка на превышение диапозона, нулевую позицию и удачную конвертацию
            {
                errorCode = 2;
                throw invalid_argument("");
            }

            cout << "Даны операции: | + | - | * | / |\nВыберите одну из них для последующего вычисления: ";
            gets(calc);

            QString(converCalc) = calc;
            if (strlen(calc) != 1)
            {
                errorCode = 3;
                throw invalid_argument("");
            }
            else
            {
                if (converCalc != "+")
                {
                    if (converCalc != "-")
                    {
                        if (converCalc != "*")
                        {
                            if (converCalc != "/")
                            {
                                errorCode = 3;
                                throw invalid_argument("");
                            }
                            else if (op2 != 0)
                                res = op1 / op2;
                            else
                            {
                                errorCode = 4;
                                throw invalid_argument("");
                            }
                        }
                        else
                            res = op1 * op2;
                    }
                    else
                        res = op1 - op2;
                }
                else
                    res = op1 + op2;
            }
            if (isinf(res))
            {
                errorCode = 5;
                throw invalid_argument("");
            }


        }
        catch (const exception)
        {
            if (errorCode == 1)
            {
                cout << "\n|------------------- ВНИМАНИЕ -------------------|";
                cout << "\n       Некорректный ввод первого операнда!\n";
                cout << "|------------------------------------------------|\n";
            }
            if (errorCode == 2)
            {
                cout << "\n|------------------- ВНИМАНИЕ -------------------|";
                cout << "\n       Некорректный ввод второго операнда!\n";
                cout << "|------------------------------------------------|\n";
            }
            if (errorCode == 3)
            {
                cout << "\n|------------------- ВНИМАНИЕ -------------------|";
                cout << "\n           Некорретный выбор операции!\n";
                cout << "|------------------------------------------------|\n";
            }
            if (errorCode == 4)
            {
                cout << "\n|------------------- ВНИМАНИЕ -------------------|";
                cout << "\n           Деление на 0 - запрещено!\n";
                cout << "|------------------------------------------------|\n";
            }
            if (errorCode == 5)
            {
                cout << "\n|------------------- ВНИМАНИЕ -------------------|";
                cout << "\n Результат вышел за диапозон допустимых значений!\n";
                cout << "|------------------------------------------------|\n";
            }

            continue;
        }

        cout << "\n|----------- РЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ -----------|";
        cout << "\n " << op1 << " " << calc << " " << op2 << " = " << round(res*100000)/100000 << "\n";
        cout << "|---------------------------------------------|\n";
        cout << "\nДля завершения работы программы нажмите ENTER . . .";
        return 0;
    }
}

