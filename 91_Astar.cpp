class Solution {
public:
    struct node{     
        int Ascore;
        int steps;
        string str;
        bool operator<(const node& b) const{
            return Ascore >= b.Ascore;
        }
    };

    string s, t;
    vector<string> dead;

    int f(string ss){
        int dist = 0;
        for (int i=0;i<4;i++){
            dist += abs((ss[i]-'0') - (t[i]-'0'));
        }
        return dist;
    }

    int openLock(vector<string>& deadends, string target) {
        s = "0000";
        t = target;
        dead = deadends;
        if (s == t) return 0;
        if (find(deadends.begin(), deadends.end(), s) != deadends.end()){
            return -1;
        }
        int ans = Astar();
        return ans;
    }

    int Astar(){
        int ans;
        priority_queue<node> que; 
        map<string, int> vis;

        que.push(node{ f(s), 0, s}); 
        vis[s] = 0; 
        while (! que.empty() ){
            node now = que.top(); que.pop();
        int steps = now.steps;
        string str = now.str;
        // cout << now.Ascore << endl;

        for (int i=0;i<4;i++){
            for (int p = -1; p<=1; p++){
                if (p == 0) continue;
                string s2 = string(str);
                int tmp = ((s2[i] - '0') + p );
                if (tmp < 0) tmp += 10;
                s2[i] = tmp%10 + '0';

                if (find(dead.begin(), dead.end(), s2) != dead.end()){
                    continue;
                }
                
                if (s2 == t) return steps+1;

                if ( vis.count(s2) == 0 || vis[s2] > steps + 1 ){
             // push  to queue
                vis[s2] = steps + 1;
                que.push(node{ f(s2)+steps+1, steps+1, s2});
                }
            }
        }
        }
        return -1;
    }

   
};