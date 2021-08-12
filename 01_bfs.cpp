#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 35;

int ma[MAXN][MAXN];
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

struct Node{
    int x,y;
    };
    int cnt = 0;

queue<Node> q;
void bfs(int x, int y)
{
	q.push(Node{4,4});
	ma[4][4] = 2;
	while (!q.empty()){
	    Node node = q.front();
	    q.pop();
	    for (int i=0;i<4;i++){
		int nx = dx[i]+node.x;
		int ny = dy[i]+node.y;
		if (ma[nx][ny] == 0){
		    ma[nx][ny] = 2;
		    q.push(Node{nx,ny});
		}
	    }
	}
	return;
}

int main()
{
	int N;
	cin >> N;
	for (int i=0;i<N;i++){
	  for (int j=0;j<N;j++){
	    cin >> ma[i][j];
	    
	  }
	}
	bfs(4,4);
	cout << ":>" << endl;
	for (int i=0;i<N;i++){
	  for (int j=0;j<N;j++){
	    cout << ma[i][j] << " "; 
	  }
	  cout << endl;
	}
	return 0;
}
