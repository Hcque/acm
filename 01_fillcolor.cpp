#include <iostream>
using namespace std;

const int MAXN = 35;

int ma[MAXN][MAXN];
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int cnt = 0;

void dfs(int x, int y)
{
	ma[x][y] = 2;
	for (int i=0;i<4;i++){
	  if (ma[dx[i]+x][dy[i]+y] == 0 ){
	    dfs(dx[i]+x,dy[i]+y) ;
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
	dfs(4,4);
	cout << ":>" << endl;
	for (int i=0;i<N;i++){
	  for (int j=0;j<N;j++){
	    cout << ma[i][j] << " "; 
	  }
	  cout << endl;
	}
	return 0;
}
