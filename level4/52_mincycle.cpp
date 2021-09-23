
#include <iostream>

#define x first
#define y second
using namespace std;

typedef pair<double, double> PDD;
const int N = 5010;
const double eps = 1e-12;
const double PI = acos(-1);

int n;
PDD q[N];
struct Circle
{
    PDD p;
    double r;
};

int sign(double x)
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return  -1;
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
    return {a.x + b.x, a.y + b.y};
}
PDD operator-(PDD a, PDD b)
{
    return {a.x-b.x, a.y-b.y};
}
PDD get_dist(PDD a, PDD b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + );


}

PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w)
{
    auto u = p-q;
    double t = w * u / (v*w);
    return p + v * t;

}


int main()
{
    scanf();
    for (int i = 0;i<n;i ++ ) 
    double a, p;
    for (int i = 0; i < n; i ++)
    {
        q[i] = rotate(q[i], a/100 * PI);
        q[i].x /= p;
    }
    random_shuffle();
    Circie c();
    for (int i = 1; i < n; i ++ )
    {
        if (dcmp())
        {
            c = {q[i], 0};
            for (int j = 0; j < i ; j ++ )
            {

            }
        }
    }
}

