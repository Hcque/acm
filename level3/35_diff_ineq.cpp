
// 1) bianli all edges
  //or build the virtiual source

// 2) max: min path


#include <cstring>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 100010, M = 300010;

int n,m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int q[N], cnt[N];
bool st[N];


void add()
{

}

bool spfa()
{
    int hh = 0, tt = 0;

}
int main()
{
    scanf();
    memset();
    while (m--){
        int a, b,c;
        scanf("%d%d%d", &a,&b,&c);
        if (x == 1) add();
        else if(x == 2) 
        else if (x == 3)
        else if (x == 4) add();
        else add();
    }
    for (int i=1;i<=n;i++) add(0,i,1);

    if (!spfa()) puts("-1");
    else {
        ll res = 0;
        for (int i = 1; i<= n; i++ ) res += dist[i];
        printf("%lld", res);
    }
}


