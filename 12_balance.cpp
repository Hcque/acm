#include <iostream>

using namespace std;

bool solve(int &w)
{
    int w1,d1,w2,d2;
    cin >> w1 >> d1 >> w2 >> d2;


    if (!w1) solve(w1);
    if (!w2) solve(w2);

    return w1*d1 == w2*d2;
}

int main()
{
   int N;
   while (N--)
   {
   if (solve()) cout << "YES\n";
   else cout << "NO\n";
   cout << endl;
   }
}
