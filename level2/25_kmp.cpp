
#include <iostream>

using namespace std;

const int N = 1e6+10, M = N;
int n,m;
char p[N], s[M];
int ne[N];

int main()
{
    cin >> n >> p + 1 >> m >> s+1;
    // next
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && p[i] != p[j+1]) j = ne[j];
        if (p[i] == p[j+1]) j++;
        ne[i] = j;
    }
        for (int i=0;i<10;i++) cout << ne[i] << " ";
        cout << endl;
    //
    for (int i=1,j=0; i <= m;i++)
    {
        while (j && s[i] != p[j+1]) j = ne[j];
        if (s[i] == p[j+1]) j ++ ;
        if (j == n)
        {
            printf("%d ", i-n);        
            j = ne[j];
        }
    }
}
