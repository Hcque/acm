
#include <iostream>

#include <omp.h>
#include <time.h>
using namespace std;

int main()
{

    clock_t a,b;
    a = clock();
 #pragma omp parallel
 {
     #pragma omp for
     {
         for (int i = 0; i < 2e8; i ++)
         {

         }
     }
 }

 b = clock() - a ;

 cout << b;
}