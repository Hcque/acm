class Solution {
public:
    string s, t;
    vector<string> dead;
    int openLock(vector<string>& deadends, string target) {
        s = "0000";
        t = target;
        dead = deadends;
        if (s == t) return 0;
        if (find(deadends.begin(), deadends.end(), s) != deadends.end()){
            return -1;
        }

        int ans = bfs();
        return ans;
    }

    int bfs(){
        int ans;
        queue<string> que1, que2;
        map<string, int> map1, map2;

        que1.push(s); que2.push(t);
        map1[s] = 0; map2[t] = 0;
        while (!que1.empty() && !que2.empty()){
            if (que1.size() < que2.size()){
                ans = update(que1, map1, map2);
            } else {
                ans = update(que2, map2, map1);
            }
            if (ans != -1) return ans;
        }
        return -1;
    }

    int update(queue<string> &que, map<string, int>& m1, map<string, int>&other){
        string now = que.front(); que.pop();
        int step = m1[now];
        for (int i=0;i<4;i++){
            for (int p = -1; p<=1; p++){
                if (p == 0) continue;
                string s2 = string(now);
                int tmp = ((s2[i] - '0') + p );
                if (tmp < 0) tmp += 10;
                s2[i] = tmp%10 + '0';

                if (m1.count(s2) != 0 ) continue;

                if (find(dead.begin(), dead.end(), s2) != dead.end()){
                    continue;
                }

                if (other.count(s2) != 0){
                    // find
                    return step + 1 + other[s2];
                }
                // push  to queue
                m1[s2] = step +1;
                que.push(s2);

            }
        }
        return -1;


    }
};