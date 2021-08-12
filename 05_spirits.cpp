#include <iostream>
#include <queue>
#include <cstring>
#include <set>
#include <cmath>

using namespace std;
typedef long long unsigned int ll;

#define MAXN 6
int ma[MAXN][MAXN];
ll target;

set<int> s;
// set<ll> hs[20004];

// int matarget[][MAXN] = {0,0,0,0,0,0,
//         0,0,0,1,1,0,
// 		    0,0,1,1,1,1,
// 		    0,1,2,1,1,1,
// 		    0,0,1,0,0,1,
// 		    0,0,0,0,0,0};

// int matarget[][MAXN] = {0,0,0,0,0,0,
//         0,1,0,1,1,0,
// 		    0,0,1,2,1,1,
// 		    0,1,0,1,1,1,
// 		    0,0,1,0,0,1,
// 		    0,0,0,0,0,0};
int matarget[][MAXN] = {0,0,0,0,0,0,
        0,1,1,1,1,1,
		    0,0,1,1,1,1,
		    0,0,0,2,1,1,
		    0,0,0,0,0,1,
		    0,0,0,0,0,0};

int x_0, y_0;
struct Node{
  ll hash;
  int m[MAXN][MAXN];
  int dist;
  int x0, y0;
};
queue<Node> q;

int dx[] = {-2,-1,1,2,2,1,-1,-2};
int dy[] = {1 , 2,2,1,-1,-2,-2,-1};

inline ll GenHash(int arr[][MAXN]){
  int num = 0;
  for (int i=5;i>=1;i--){
    for (int j=5;j>=1;j--){
      num = num * 3 + arr[i][j];      
    }
  }
  return num;
}

inline void prin(int arr[][MAXN]){
  int num = 0;
  for (int i=1;i<=5;i++){
    for (int j=1;j<=5;j++){
       cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}

inline int Find(ll x){
  return s.find(x) != s.end();
}

void search()
{
 s.clear();
 Node st;
 st.hash = GenHash(ma);
 memcpy(st.m, ma, sizeof(ma));
 st.dist = 0;
 st.x0= x_0; st.y0= y_0;
 q.push(st);
 s.insert( st.hash);
 while (! q.empty()){
   Node cur = q.front(); q.pop();
	// cout << cur.hash << endl;
   if (cur.dist >15) {
   cout << "-1" << endl; return;
   }
  //  cout << cur.hash << " " << target << endl;
  //  break;
   if ( s.count(target)>0  ){
      cout << cur.dist << endl;
      return;
   }
   for (int i=0;i<8;i++){
     int nx = dx[i] + cur.x0;
     int ny = dy[i] + cur.y0;
     if (nx >=1 && nx<=5 && ny>=1 && ny<=5){
       swap(cur.m[nx][ny], cur.m[cur.x0][cur.y0]);
	ll nxt_hash = GenHash(cur.m);
       if (! Find(nxt_hash)){
         Node nxt;
    nxt.dist = cur.dist+1;
    memcpy(nxt.m, cur.m, sizeof(cur.m));
    nxt.x0 = nx; nxt.y0 = ny;
    nxt.hash = nxt_hash;
    s.insert(nxt.hash);
    q.push(nxt);
       }
       swap(cur.m[cur.x0][cur.y0], cur.m[nx][ny]);
     }
   }
 }
 s.clear();
 return;
}

int main()
{
  int N;
  char ch;
  cin >> N;
  target = GenHash(matarget);
  for (int i=0;i<N;i++){
    for (int x=1;x<=5;x++){
      for (int y=1;y<=5;y++){
        cin >> ch;
        switch (ch){
        case '0' : ma[x][y] = 0;break;
        case '1' : ma[x][y] = 1;break;
        case '*' : ma[x][y] = 2;
        x_0 = x; y_0 = y;
        break;
        }
      }
    }
    prin(ma);
    search();
  }
  return 0;
}
