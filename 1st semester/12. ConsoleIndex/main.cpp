#include <iostream>
#include<cstdio>
#include <cstring>
#include <QString>

using namespace std;

int main()
{
    while(true) // ��᪮���� 横�, �⮡� �ணࠬ�� ࠡ�⠫�, ���� �� ���� ������� �ࠢ���� �����
    {
        char symbol[1]; // ��६����� ᨬ���� ������ ᨬ����
        char str[10000];  // ���ᨢ ᮤ�ঠ騩 ������� ���������� ⥪��
        int index[10000]; // ���ᨢ ᮤ�ঠ騩 �������� ����樨 �᪮���� ᨬ����
        int n=0;
        int k=0;

        try
        {
            cout << "\n������ ⥪��:  ";
            gets(str); // ���� ⥪�� � ��६����� ���ᨢ�

            if (strlen(str) == 0) // �஢�ઠ ����⢮����� ���������� ���ᨢ�
                throw invalid_argument("");

            cout << "������ �᪮�� ᨬ���: ";
            gets(symbol); // ���� �᪮��� ����樨

            if (strlen(symbol) == 0 || strlen(symbol) > 1) // �஢�ઠ ����⢮����� ���������� ���ᨢ�
                throw invalid_argument("");
            for (int i = 0; i < 9999; i++)
            {
                if (symbol[0] == str[i])
                {
                    index[n] = i;
                    n++;
                }
            }
        }
        catch (const exception)
        {
            cout << "\n|------------------- �������� -------------------|";
            cout << "\n           ������� �����४�� �����!\n";
            cout << "|------------------------------------------------|\n";

            continue;
        }
        if (n > 0)
        {
            cout << "\n|--------------- ��������� ������ ---------------|";
            cout << "\n ������: " << symbol[0] << " - ����� ����樨: | ";

            for (int i = 0; i<n; i++)
            {
                cout << index[k]+1 << " | ";
                k++;
            }
            cout << "\n|------------------------------------------------|\n";
        }
        else
        {
            cout << "\n|--------------- ��������� ������ ---------------|";
            cout << "\n            ������: " << symbol[0] << " - �� �� ������!";
            cout << "\n|------------------------------------------------|\n";
        }

        cout << "\n��� �����襭�� ࠡ��� �ணࠬ�� ������ ENTER . . .";
        return 0;
    }
}

