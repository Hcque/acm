#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

const int MAXN = 100;
const int MAXV = 200;
char maze[MAXN][MAXN];
int nodes[MAXN][MAXN];

int dist[MAXV][MAXV]; // dist of cells/Node
int G[MAXV][MAXV];
int row, col;
int cnt;
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

struct Node{
    int x, y;
    Node(int _x, int _y): x(_x), y(_y) {}
};

void bfs(int x, int y)
{
    int vis[MAXN][MAXN];
    memset(vis, 0, sizeof(vis));
    memset(dist, 0, sizeof(dist));

    queue<Node> que;
    que.push(Node(x, y));
    vis[x][y] = 1;
    dist[x][y] = 0;
    while (!que.empty()){
        Node node = que.front(); que.pop();
        // cout << node.x << "|" << node.y << endl;
        for (int i = 0;i<4;i++){
            int nx = dx[i] + node.x;
            int ny = dy[i] + node.y;

            if ( nx>=1 && nx<=row && ny>=1 && ny<=col 
            && maze[nx][ny] != '#' && vis[nx][ny] == 0){
                dist[nx][ny] = dist[node.x][node.y]+1;
                vis[nx][ny] = 1;
                if (nodes[nx][ny] != 0){
                    G[ nodes[x][y] ][ nodes[nx][ny] ] = dist[nx][ny];
                }
                que.push(Node(nx, ny));
            }
        }
    }

}
int prim(){
    int s = 1;
    bool u[MAXV];
    u[s] = true;
    int point;
    int low_dist[MAXV];
    for (int i=1;i<= cnt;i++){
        u[i] = false;
        low_dist[i] = INT_MAX;
    }
    low_dist[s] = 0;

    int ans = 0;
    int m = 1;
    while (1){
        if (m == cnt) break;
        int min_c = INT_MAX;
        for (int i=2;i<=cnt;i++){
            if (!u[i] && low_dist[i] > G[s][i]) {
                low_dist[i] = G[s][i];
            }
            if (!u[i] && low_dist[i] < min_c) {
                min_c = low_dist[i];
                point = i;
            }
        }

        u[point] = true;
        s = point;
        m++;
        ans += min_c;
    }
    return ans;
}

int main()
{
    int N;
    // scanf("%d", &N);
    cin >> N;
    while (N--){
        memset(nodes, 0, sizeof(nodes));
        memset(maze, 0, sizeof(nodes));
        memset(dist, 0, sizeof(dist));
        memset(G, 0, sizeof(nodes));
        cnt = 0;
        // scanf("%d %d", &col, &row);
        cin >> col >> row;
        char tmp[51];
        gets(tmp);
        for (int i=1;i<=row;i++){
            gets(maze[i]);
            for (int j=1;j<=col;j++){
                if (maze[i][j] == 'S' || maze[i][j] == 'A'){
                    nodes[i][j] = ++cnt;
                }
            // cout << "@" << maze[i][j] << " ";
            }
            // cout << endl;
        }
        // for (int i=1;i<=row;i++){
        //     for (int j=1;j<=col;j++){
        //         cout <<  nodes[i][j]  << " ";
        //     }
        //     cout << endl;
        // }

        // bfs  to form graph G
        for (int i=1;i<=row;i++){
            for (int j=1;j<=col;j++){
                if (nodes[i][j] != 0) {
                    // cout << nodes[i][j] << endl;
                    bfs(i, j);
                }
            }
        }


        // for (int i=1;i<7;i++){
        //     for (int j=1;j<=7;j++){
        //         cout << G[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        cout << prim() << endl;
    }

}