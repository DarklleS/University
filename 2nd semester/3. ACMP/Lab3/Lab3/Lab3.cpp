#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    int n;
    int m;
    string arrPath = "INPUT.TXT";
    string resPath = "OUTPUT.TXT";
    ifstream fileIn;
    ofstream fileOut;

    fileIn.open(arrPath);
    fileOut.open(resPath);

    fileIn >> n >> m;

    int value = 0;
    int count = 0;

    for (int i = 0; true; i++) 
    {
        if (m == 0)     // Если все элементы удалены
        {
            count = 1;
            break;
        }
        if (m == 1)     // Если остался 1 элемент
        {
            count = n;
            break;
        }
        if (n < m)      // Если кол-во элементов "до" меньше чем кол-во элементов "после"
        {
            count = 0;
            break;
        }

        value = m + i * (m - 1);

        if (value > n)
            break;

        count += n - value + 1;
    }

    fileOut << count;

    return 0;  
}