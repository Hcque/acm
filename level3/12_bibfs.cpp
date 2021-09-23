
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

const int N = 6;
int n;
string a[N], b[N];

using namespace std;

// int extend(queue<string>& q, unordered_map<string, int>&da, unordered_map<string, int>& db, 
//     string a[N], string b[N])
// {
//     int d = da[q.front()];
//     while (q.size() && da[q.front()] == d)
//     {
//         auto t = q.front();
//         q.pop();

//         for (int i = 0; i < n; i ++ )
//             for (int j = 0; j < t.size(); j ++ )
//                 if (t.substr(j, a[i].size()) == a[i])
//                 {
//                     string r = t.substr(0, j) + b[i] + t.substr(j + a[i].size());
//                     if (db.count(r)) return da[t] + db[r] + 1;
//                     if (da.count(r)) continue;
//                     da[r] = da[t] + 1;
//                     q.push(r);
//                 }
//     }

//     return 11;
// }

int extend(queue<string>& q, 
            unordered_map<string, int>& da, unordered_map<string, int>& db, 
            string a[], string b[])
{

    string t = q.front(); q.pop();
    
    for (int i = 0; i < t.size(); i ++ )
        for (int j = 0; j < n; j ++ )
            if (t.substr(i, a[j].size()) == a[j]){
                string state = t.substr(0,i) + b[j] + t.substr(i+a[j].size());
                if (db.count(state)) 
                {
                    return da[t] + 1 + db[state];
                }
                if (da.count(state)) continue;
                da[state] = da[t] + 1;
                q.push(state);
            }
    return 11; 
}

int bfs(string A, string B)
{
    queue<string> qa, qb;
    unordered_map<string, int>da, db;
    qa.push(A); qb.push(B);
    da[A] = 0; db[B] = 0;

    while (qa.size() && qb.size())
    {
        int t;
        if (qa.size() <= qb.size()) t = extend(qa, da, db, a, b);
        else t = extend(qb, db, da, b,a);

        if (t <= 10) return t;
    }

    return 11;
}
int main()
{
    string A, B;
    cin >> A >> B;
    while ( cin >> a[n] >> b[n]) n++;

    int step = bfs(A, B);
    if (step > 10) puts("NO ANSWER!");
    else printf("%d\n", step);
}