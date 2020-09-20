#include <iostream>
#include<cstdio>
#include <cstring>
#include <QString>
#include <math.h>
#include <cmath>

using namespace std;

int main()
{
    while(true) // ��᪮���� 横�, �⮡� �ணࠬ�� ࠡ�⠫�, ���� �� ���� ������� �ࠢ���� �����
    {
        double op1, op2, res;
        char input1[10000], input2[10000];
        QString conver1, conver2, converCalc; // ��६����� �������樨 ��६����� ����� ����樨
        bool flag1, flag2;  // ��६����� �஢�ન �������樨
        char calc[100];
        int errorCode=9;


        try
        {
            cout << "\n������ ���� ���࠭�: ";
            gets(input1);

            conver1.append(input1); // ��������� ���ᨢ� � �����⠬� �ᥫ � 楫�� �᫮
            op1 = conver1.toDouble(&flag1); // ��ᢠ������ ��६����� �᪮��� ����樨 �������樨 ���祭�� ���ᨢ�

            if(flag1 == 0) // �஢�ઠ �� �ॢ�襭�� ���������, �㫥��� ������ � 㤠��� ���������
            {
                errorCode = 1;
                throw invalid_argument("");
            }

            cout << "������ ��ன ���࠭�: ";
            gets(input2);

            conver2.append(input2); // ��������� ���ᨢ� � �����⠬� �ᥫ � 楫�� �᫮
            op2 = conver2.toDouble(&flag2); // ��ᢠ������ ��६����� �᪮��� ����樨 �������樨 ���祭�� ���ᨢ�

            if(flag2 == 0) // �஢�ઠ �� �ॢ�襭�� ���������, �㫥��� ������ � 㤠��� ���������
            {
                errorCode = 2;
                throw invalid_argument("");
            }

            cout << "���� ����樨: | + | - | * | / |\n�롥�� ���� �� ��� ��� ��᫥���饣� ���᫥���: ";
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
                cout << "\n|------------------- �������� -------------------|";
                cout << "\n       �����४�� ���� ��ࢮ�� ���࠭��!\n";
                cout << "|------------------------------------------------|\n";
            }
            if (errorCode == 2)
            {
                cout << "\n|------------------- �������� -------------------|";
                cout << "\n       �����४�� ���� ��ண� ���࠭��!\n";
                cout << "|------------------------------------------------|\n";
            }
            if (errorCode == 3)
            {
                cout << "\n|------------------- �������� -------------------|";
                cout << "\n           �������� �롮� ����樨!\n";
                cout << "|------------------------------------------------|\n";
            }
            if (errorCode == 4)
            {
                cout << "\n|------------------- �������� -------------------|";
                cout << "\n           ������� �� 0 - ����饭�!\n";
                cout << "|------------------------------------------------|\n";
            }
            if (errorCode == 5)
            {
                cout << "\n|------------------- �������� -------------------|";
                cout << "\n ������� ��襫 �� �������� �����⨬�� ���祭��!\n";
                cout << "|------------------------------------------------|\n";
            }

            continue;
        }

        cout << "\n|----------- ��������� ���������� -----------|";
        cout << "\n " << op1 << " " << calc << " " << op2 << " = " << round(res*100000)/100000 << "\n";
        cout << "|---------------------------------------------|\n";
        cout << "\n��� �����襭�� ࠡ��� �ணࠬ�� ������ ENTER . . .";
        return 0;
    }
}

