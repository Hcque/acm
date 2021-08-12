#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N;
struct Node{
  int A[10];
  int n, nown;
};
queue<Node> q;
void bfs()
{
  Node st;
  st.n = N; st.nown = 1;
  q.push(st);
  while (! q.empty()){
    Node node = q.front(); q.pop();
    if (node.nown == N+1){
      for (int i=1;i<=N;i++)
        cout << node.A[i] << " ";
      cout << endl;
    }
    else{
    for (int i=1;i<=node.n;i++){
      int ok = 1;
      for (int j=1;j<node.nown;j++){
	if (node.A[j] == i) ok = 0;
      }
      if (ok){
	node.A[node.nown] = i;
	Node nxt; 
	nxt.n = N;
	memcpy(nxt.A,node.A,(node.nown+1)*sizeof(int));
	nxt.nown = node.nown+1;
	q.push(nxt);
      }
    }
    }
  }
  return;
}
int main()
{
 cin >> N;
 bfs();

 return 0;
}
