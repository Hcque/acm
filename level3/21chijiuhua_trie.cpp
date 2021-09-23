// it self not change
// https://www.acwing.com/problem/content/258/


#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 6e5+10, M = N * 25;

int n,m;
int s[N];
int tr[M][2], max_dfsn[M];
int root[N];

void insert(int i, int k, int p, int q)
{
    if (k < 0)
    {
        max_dfsn[q] = i;return;
    }
    if (p) 
}

int main()
{
    scanf("%d%d", &n,&m);

    max_dfsn[0] = -1;
    root[0] = ++ idx;
    insert(0,23,0,root[0]);





}




