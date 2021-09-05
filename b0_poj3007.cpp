// 1904K	188MS
#include <string>
#include <set>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXC = 75;
void cut(char* s,int i, char* sub1, char* sub2){
    strcpy(sub1, s);
    sub1[i] = '\0';
    strcpy(sub2, s+i);
}
void rev(char* s, char* out){
    int n = strlen(s);
    for (int i=0;i<n;i++){
        out[i] = s[n-i-1];
    }
    out[n] = '\0';
    // cout << "out" << out << endl;
}
void Concat(char* s1, char* s2, char* out){
    strcpy(out, s1);
    int n = strlen(s1);
    strcpy(out+n, s2);
}

const int maxn = 1e3;
struct HashTable{
    char v[MAXC];
    HashTable* next;
    HashTable(){ next = 0;}
};
HashTable *H[maxn];

int cnt = 0;
int Hash(char *s){
    int ans = 0;
    int n = strlen(s);
    for (int i=0;i<n; i++){
        ans += (s[i] * (i+4)* 76) ;
    }
    return ans % maxn;
}
void ins(char* s){
    int h = Hash(s);
    if (!H[h]) {
        H[h] = new HashTable;
        strcpy(H[h]->v , s);
        cnt++;
    }
    else if ( strcmp(H[h]->v, s) == 0) return;
    else {
        HashTable *now = H[h];
        while (now->next){
            if ( strcmp(now->next->v , s) == 0) return;
            now = now->next;
        }
        now->next = new HashTable;
        strcpy(now->next->v , s);
        cnt++;
    }
}
// set<string> S;
int main()
{
    int T;
    cin >> T;
    while (T--){
        cnt = 0;
        // S.clear();
        char s[MAXC];
        cin >> s;
        memset(H, 0, sizeof(H));

        int n = strlen(s);
        for (int i=1;i<=n-1;i++){
            char sub1[MAXC], sub2[MAXC];
            cut(s, i, sub1, sub2);
            // cout << sub1 << " |" << sub2 << endl;
            char rev1[MAXC], rev2[MAXC];
            rev(sub1, rev1);            
            rev(sub2, rev2);            
            // cout << rev1 << " |" << rev2 << endl;
            char out[MAXC]; 
            Concat(sub1,sub2,out); ins(out);
            Concat(sub1,rev2,out); ins(out);
            Concat(rev1,sub2,out); ins(out);
            Concat(rev1,rev2,out); ins(out);
            Concat(sub2,sub1,out); ins(out);
            Concat(rev2,sub1,out); ins(out);
            Concat(sub2,rev1,out); ins(out);
            Concat(rev2,rev1,out); ins(out);
        }
        // cout << S.size() << endl;
        cout << cnt << endl;
    }
    // cout << "a" + "ssb" << endl;
}