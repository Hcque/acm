
#include <iostream>
#include <cstring>

using namespace std;

const int N = 510, M = 2510*2, W = 210;
int h[N], e[M],w[M], ne[M], idx;
int T, n, m1, m2;

void add(int a,int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int q[N], dist[N], cnt[N], inq[N];

int spfa()
{
    int hh = 0, tt = 0;
    memset(dist, 0, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    memset(inq, 0, sizeof inq);
    for (int i = 1; i <= n; i ++ ){
        q[ tt ++ ] = i;
        inq[i] = 1;        
    }
    while (hh != tt)
    {
        auto t = q[ hh ++ ];
        if (hh == N) hh = 0;
        inq[t] = 0;

        for (int i = h[t];~i;i=ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]){
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return 1;
                if (!inq[j]){
                    q[ ++ tt ] = j;
                    if (tt == N) tt = 0;
                    inq[j] = 1;
                }
            }
        }
    }
    return 0;
}


// bool spfa()
// {
//     memset(dist, 0, sizeof dist);
//     memset(cnt, 0, sizeof cnt);
//     memset(inq, 0, sizeof inq);

//     int hh = 0, tt = 0;
//     for (int i = 1; i <= n; i ++ )
//     {
//         q[tt ++ ] = i;
//         inq[i] = true;
//     }

//     while (hh != tt)
//     {
//         int t = q[hh ++ ];
//         if (hh == N) hh = 0;
//         inq[t] = false;

//         for (int i = h[t]; ~i; i = ne[i])
//         {
//             int j = e[i];
//             if (dist[j] > dist[t] + w[i])
//             {
//                 dist[j] = dist[t] + w[i];
//                 cnt[j] = cnt[t] + 1;
//                 if (cnt[j] >= n) return true;
//                 if (!inq[j])
//                 {
//                     q[tt ++ ] = j;
//                     if (tt == N) tt = 0;
//                     inq[j] = 1;
//                 }
//             }
//         }
//     }

//     return false;
// }
int main()
{
    cin >> T;
    while (T--)
    {
        scanf("%d%d%d", &n, &m1, &m2);
        memset(h,-1,sizeof h);
        idx = 0;
        while (m1--)
        {
            int a,b,c;
            scanf("%d%d%d", &a, &b, &c);
            add(a,b,c), add(b,a,c);
        }
        while (m2--)
        {
            int a,b,c;
            scanf("%d%d%d", &a, &b, &c);
            add(a,b,-c);
        }
        int ans = spfa();
        if (ans) puts("YES");
        else puts("NO");
    }

}