#include <iostream>
#include <fstream>

 using namespace std;

 int main()
 {
     string arrPath = "INPUT.TXT";
     string resPath = "OUTPUT.TXT";
     ifstream fileIn;
     ofstream fileOut;

     fileIn.open(arrPath);
     fileOut.open(resPath);

     unsigned long long int a, b;

     fileIn >> a >> b;

     unsigned long long int k = 1;

     for (unsigned long long int i = a; i <= b; i++)
     {
         if (b > 1000000)
             return 0;
         if (a > b)
             return 0;
         if (a < 0 || b < 0)
             return 0;

         while (k <= i)
         {
             k *= 10;
         }
        
         if ((i * i) % k == i)
         {
             fileOut <<  i << " ";
         }
     }
     fileIn.close();
     fileOut.close();

    return 0;
}

