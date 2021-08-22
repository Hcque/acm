#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;
int Size;
char minch = '9', maxch = '0';
struct node{
    string s;
    int cnt;
    int index;
    node(string _s, int _cnt, int _i): s(_s), cnt(_cnt), index(_i) {}
    node(){}
};

queue<node> que1, que2;
map<string, int> map_1, map_2;

#define CHECK  if (other.count(news) != 0){ \
                    return cnt + other[news] + 1; \
                } \
            map_[news] = cnt; 

#define RELAX if (map_.count(news) != 0){\
                map_[news] = min(map_[news], cnt+1);\
            }
int f(queue<node>& que, map<string, int>& map_, map<string, int>& other)
{
      node pp = que.front(); que.pop();
      string s = pp.s;
        int cnt = pp.cnt;
        int index = pp.index;
  
        string news = string(s);
        if (index > 0) {
            que.push(node(news, cnt+1, index-1));
        }
        if (index < Size-1) {
            que.push(node(news, cnt+1, index+1));

        }
        char ch = news[index];
        if (ch >= '0' && ch < '9') {
            news[index] = ch+1;
            RELAX
            if (map_.count(news) == 0) {
                // cout << "#1" << endl;
               CHECK
                que.push(node(news, cnt+1, index));
            }
        }
        if (ch <= '9' && ch > '0') {
            news[index] = ch-1;
            RELAX
            if (map_.count(news) == 0) {
                // cout << "#2" << endl;
               CHECK
                que.push(node(news, cnt+1, index));
            }
        }

        news = string(s);
        if (index != 0){
            swap(news[0], news[index]);
            RELAX
            if (map_.count(news) == 0) {
               CHECK
                que.push(node(news, cnt+1, index));
            }
        }
        news = string(s);
        if (index != Size-1){
            swap(news[Size-1], news[index]);
            RELAX
            if (map_.count(news) == 0) {
                // cout << "#4" << endl;
                CHECK
                que.push(node(news, cnt+1, index));
            }
        }

    return -1;
}

int main()
{
    string cur, target;
    cin >> cur >> target;
    
    for (char c: target){
        if (c < minch) minch = c;
        if (c > maxch) maxch = c;
    }
    Size = cur.size();

     // <string int> "123343", count of search length
    map_1[cur] = 0;
    map_2[target] = 0;
    que1.push(node(cur, 0, 0));
    // setAll.insert({cur, 0});
    // setAll.insert({target, 0});
    for (int i=0;i<Size;i++){
        que2.push(node(target, 0, i));
    }
    int ans = -1;

    while (! que1.empty() && !que2.empty()){
        // cout << que1.size() << "|size|"<< que2.size() << endl;
        if (que1.size() < que2.size())
             ans = f(que1, map_1, map_2);
        else 
            ans = f(que2, map_2, map_1);

        if (ans != -1) {
            cout << ans << endl;
            return 0;
        }
        // for (auto it: set_) cout << it << " ";
        // cout << endl;
    }

}