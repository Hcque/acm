
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 1e4+10;
int n;
double ans = 1e8;
typedef pair<double, double> Point;
#define x first
#define y second

Point q[N];
    double get_dist(Point & a, Point & b)
    {
        double dx = (a.x - b.x) ;
        double dy = (a.y - b.y) ;
        return sqrt(dx*dx + dy*dy);
    }

double rand(double l, double r)
{
    return (double) rand() / RAND_MAX * (r-l) + l;
}

double cal(Point p)
{
    double res = 0;
    for (int i = 0; i < n; i++ )
        res += get_dist(p, q[i]);
    ans = min(ans, res);
    return res;
}

void sim_anneal()
{
    Point cur = {rand(0,1e4), rand(0,1e4)};
    for (double t = 1e4; t > 1e-4; t=t*0.9)
    {
        Point p = {rand(cur.x -t, cur.x+t), rand(cur.y-t, cur.y+t)};
        double dt = cal(p) - cal(cur);
        if (exp( -dt / t) > rand(0,1)) cur = p;
    }
}
int main()
{
    cin>> n;
    for (int i = 0; i < n; i++ ) scanf("%lf%lf", &q[i].x, &q[i].y);

    for (int i = 0; i < 100; i ++ ) sim_anneal();
    printf("%.0lf", ans);

}

