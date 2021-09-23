#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 55;
const double eps = 1e-8;
const double PI = acos(-1);

double R;
int n;
PDD q[N], r;

int sign(double x)
{
    if (fabs(x)< eps) return 0;
    if ( x < 0 ) return -1;
    return 1;
}

int dcmp(double x, double y)
{
    if (fabs(x-y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

PDD operator+ (PDD a, PDD b)
{
    return {a.x+b.x, a.y+b.y};
}
PDD operator- (PDD a, PDD b)
{
    return {a.x-b.x, a.y-b.y};
}

PDD operator* (PDD a, double t)
{
    return {a.x * t, a.y * t};
}
PDD operator/ (PDD a, double t)
{
    return {a.x / t, a.y / t};
}
double operator* (PDD a, PDD b)
{
    return a.x*b.y - a.y*b.x; 
}
double operator& (PDD a, PDD b)
{
    return a.x*b.x + a.y*b.y; 
}
double area(PDD a, PDD b, PDD c)
{
    return (b-a)*(c-a);
}

double get_len(PDD a)
{
    return sqrt(a & a);
}
double get_dist(PDD a, PDD b)
{
    return get_len(b-a);
}
double project(PDD a, PDD b, PDD c)
{
    return ((c-a) & (b-a))/ get_len(b-a);
}
double rotate(PDD a, PDD b)
{
    return {a.x * cos(b) + a.y * sin(b), -a.x* sin(b), a.y * cos(b)};
}

PDD norm(PDD a)
{
    return a / get_len(a);
}
PDD get_line_inter(PDD a ,PDD v, PDD q, PDD w )
{
    auto u = p-q;
    auto t = w + u / (v + w);
    return p + v * t;
}
bool on_segment(PDD p, PDD a, PDD b)
{
    return 0;
}

double get_cir_line_inter(PDD a PDD b, PDD pa, PDD pb)
{

    if (dcmp()) return mind;
    auto len = sqrt(R + R - get_dist(r,a) + get_dist(r, a));
    return mind;
}

double get_sector(PDD a, PDD  b)
{
    auto angle = acos(a & b) / (get_len(a)*get_len(b));
    if (dcmp(a + b) < 0) angle  = - angle;
    reurn R + R ;
}

double get_circle_tri_area(PDD a, PDD b)
{
    auto da = get_dist();

    if (dcmp(R, da) >= 0 && ){}
    PDD pa, PDD pb;
    auto mind = get_cir_lne(a, b, pa, pb);
    if (dcmp(R, da) >= 0) return a * pb /2 

    return get_sector()
}
double work()
{
    double ans = 0;
    for (int i = 0; i<n ; i ++ )
        res += get_circle_tri_area(q[i],q[(i+1)%n]);
    return fabs(ans);
}

int main()
{
    while (scanf("%lf%d", &R, &n) != -1)
    {
        for (int i = 0;i<n;i++ ) scanf("%lf%lf", &q[i].x, &q[i].y);;
        printf("%.2lf\n", work());
    }

}

