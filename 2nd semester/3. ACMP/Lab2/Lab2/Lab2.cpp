#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    
    int n;
    string arrPath = "INPUT.TXT";
    string resPath = "OUTPUT.TXT";
    ifstream fileIn;
    ofstream fileOut;

    fileIn.open(arrPath);
    fileOut.open(resPath);

    fileIn >> n;
    int res = n*n-3*n+2;
    fileOut << res;

    return 0;
}