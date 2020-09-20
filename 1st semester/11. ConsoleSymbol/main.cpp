#include <iostream>
#include<cstdio>
#include <cstring>
#include <QString>
using namespace std;

int main()
{
    while(true) // ��᪮���� 横�, �⮡� �ணࠬ�� ࠡ�⠫�, ���� �� ���� ������� �ࠢ���� �����
    {
        unsigned int index;   // ��६����� ����樨 ������ ᨬ����
        char input[10000]; // ���ᨢ ᮤ�ঠ騩 �������� ���祭�� �᪮��� ����樨
        char str[10000];  // ���ᨢ ᮤ�ঠ騩 ������� ���������� ⥪��
        QString convert; // ��६����� �������樨 ��६����� ����� ����樨
        bool flag;  // ��६����� �஢�ન �������樨

        try
        {
            cout << "\n������ ⥪��:  ";
            gets(str); // ���� ⥪�� � ��६����� ���ᨢ�

            if (strlen(str) == 0) // �஢�ઠ ����⢮����� ���������� ���ᨢ�
                throw invalid_argument("");

            cout << "������ ������ �᪮���� ᨬ���� � ��������� �� 1 �� " << strlen(str) << ": ";
            gets(input); // ���� �᪮��� ����樨

            if (strlen(input) == 0) // �஢�ઠ ����⢮����� ���������� ���祭��
                throw invalid_argument("");

            convert.append(input); // ��������� ���ᨢ� � �����⠬� �ᥫ � 楫�� �᫮
            index = convert.toUInt(&flag); // ��ᢠ������ ��६����� �᪮��� ����樨 �������樨 ���祭�� ���ᨢ�

            if(index > strlen(str) || index == 0 || flag == 0) // �஢�ઠ �� �ॢ�襭�� ���������, �㫥��� ������ � 㤠��� ���������
                throw invalid_argument("");
        }
        catch (const exception)
        {
            cout << "\n|------------------- �������� -------------------|";
            cout << "\n           ������� �����४�� �����!\n";
            cout << "|------------------------------------------------|\n";

            continue;
        }
            cout << "\n|--------------- ��������� ������ ---------------|";
            cout << "\n           ������: " << input << " - ����� ᨬ���: " << str[index-1] << "           \n";
            cout << "|------------------------------------------------|\n";
            cout << "\n��� �����襭�� ࠡ��� �ணࠬ�� ������ ENTER . . .";
            return 0;
    }
}

