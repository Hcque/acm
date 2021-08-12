#include <iostream>
#include <set>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;
#define MAXN 7
int ma[MAXN][MAXN];
int target = 123804765;
set<int> s;
int N;

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
struct Node{
  int dist;
  int hash;
  int m[MAXN][MAXN];
  int x0,y0;
};

int x_0, y_0;
queue<Node> q;

int toInt(int arr[][MAXN])
{
int cnt = 8;
int ans = 0;
for (int i=1;i<=3;i++) for (int j=1;j<=3;j++)
  ans +=  arr[i][j] * pow(10, cnt--);
return ans;
}
void bfs() 
{
 Node n;
 n.hash = N;
 memcpy(n.m, ma, sizeof(ma));
 n.x0 = x_0; 
 n.y0 = y_0; 
 n.dist = 0;
 q.push(n);
 s.insert(n.hash);
 while (!q.empty())
 {
   Node now = q.front(); q.pop();
   if (now.hash == target) {
     cout << now.dist << endl;
     return;
   }

   for (int i=0;i<4;i++){
     int nx = now.x0 + dx[i];
     int ny = now.y0 + dy[i];
     if (nx>=1 && nx<=3 && ny>=1 && ny<=3 ){
	swap(now.m[now.x0][now.y0], now.m[nx][ny]);
	int hash_nxt = toInt(now.m);
	//cout << hash_nxt << endl;
	if ( s.find(hash_nxt) == s.end()){
	  Node nxt;
	  memcpy(nxt.m, now.m, sizeof(now.m));
	  nxt.hash = hash_nxt;
	  nxt.x0 = nx;
	  nxt.y0 = ny;
	  nxt.dist = now.dist+1;
	  q.push(nxt);
	  s.insert(nxt.hash);
	}
	
	swap(now.m[nx][ny], now.m[now.x0][now.y0]);
     }
   }

 }
 return;
}
int main()
{
  for (int i=1;i<=3;i++){
    for (int j=1;j<=3;j++){
      ma[i][j] = getchar() - '0';
      if (ma[i][j] == 0 ) {
	x_0 = i;
	y_0 = j;
      }
    }
  }
  N = toInt(ma);
  bfs();
  return 0;
}
