#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;
const int N = 110;

int n;
struct Point{
    double x, y;
} q[N];
double ans = 1e8;

double rand(double l, double r)
{
    return (double)rand() / RAND_MAX * (r-l) + l;
}

double get_dist(Point& a, Point& b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

double cal(Point& p)
{
    double res = 0;
    for (int i = 0; i < n; i ++ )
    {
        res += get_dist(p, q[i]);
    }
    ans = min(ans, res);
    return ans;
}
void sim()
{
    Point cur = {rand(0,1e4), rand(0,1e4)};
    for (double t = 1e4; t > 1e-4; t=t*0.9){
        Point np = {rand(cur.x-t, cur.x+t), rand(cur.y-t, cur.y+t)};
        double dt = cal(np) - cal(cur);
        if (exp(-dt / t)  > rand(0,1)) cur = np;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++ ) {
        scanf("%lf%lf", &q[i].x, &q[i].y);
    }
    for (int i=0;i<100;i++ ) sim();
    printf("%.0lf\n", ans);
}