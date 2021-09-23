#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 10010;

int n;
PDD q[N];
int stk[N];
bool used[N];

double get_dist(PDD a, PDD b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
PDD operator- (PDD a, PDD b)
{
    return {a.x-b.x, a.y-b.y};
}

double cross(PDD a, PDD b)
{
    return a.x*b.y - a.y*b.x;
}

double area(PDD a, PDD b, PDD c)
{
    return fabs(cross(b-a, c-a)/2);
}

double andrew()
{
    sort(q, q+n);
    int top = 0;
    for (int i = 0; i < n; i ++ )
    {
        while (top >= 2 && area(q[stk[top-1]], q[stk[top]], q[i]) >= 0)
            used[stk[top--]] = false;
        stk[ ++ top] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = n-1; i >= 0; i -- )
    {
        if (used[i]) continue;
        while (top >= 2 && area(q[stk[top-1]], q[stk[top]], q[i] <= 0))
            top--;
        stk[ ++ top] = i;
    }
    double ans= 0;
    for (int i = 1; i <= n ; i ++ )
    {
        ans += get_dist(q[stk[i-1]], q[stk[i]]);
    }    
    return ans;

}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++ ) cin >> q[i].x >> q[i].y;
    double ans = andrew();
    printf("%.2lf\n", ans);


}