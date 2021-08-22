#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 10006;
const double pi = 2;

struct Node{
    int x, y;
} p[MAXN], P[MAXN];

int n, L;
double cross(Node a, Node b, Node c){

}

double dist(Node a, Node b){
    return sqrt( (a.x-b.x)*(a.x-b.x) - (a.y-b.y)*(a.y-b.y) );
}

bool cmp(Node a, Node b){


}


int main(){
    int N ;
    cin >> N;
    while (N--){
        cin >> n >> L;
        for (int i=0;i<n;i++){
            cin >> p[i].x >> p[i].y;
            cout << p[i].x << endl;

        }
        if (n == 1) cout << 0 << endl;
        else if (n == 2) cout << dist(p[0], p[1]) << endl;
        else {

        }

    }
}