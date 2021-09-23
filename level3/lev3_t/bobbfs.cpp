
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;
const int N = 6;
string a[N], b[N];
string A, B;

int extend(queue<string> qa, 
            unordered_map<string, int> da,
            unordered_map<string, int> db,
            string a[], string b[])
{
    auto t = qa.front(); qa.pop();
    for (int i = 0; i < t.size(); i ++){
        for (int j = 0; j < 6; j ++ ){
            if (t.substr(i, a[j].size()) == a[j] ){
                string state = t.substr(0,i) + b[j] + t.substr(i+a[j].size());
                if (da.count(state)) continue;
                da[state] = da[t] + 1;
                if (db.count(state)) return da[state] + db[state];
                qa.push(state);
            }
        }
    }
}
int bfs()
{
    queue<string> qa, qb;
    unordered_map<string, int> da, db;
    qa.push(A), da[A] = 0;
    qb.push(B), db[B] = 0;

    while (qa.size() && qb.size())
    {
        int t;
        if (qa.size() <  qb.size()) t = extend(qa, da, db, a, b);
        else t = extend(qb, db, da, b,a);
        if (t <= 10) return t;
    }
    return 11;
}

int n;
int main()
{
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) n++;
    bfs();

}