#include <string>

using namespace std;
const int maxn = 2* 1e6 + 9;

int trie[maxn][26];
int cntword[maxn];
int fail[maxn];

void insertWords(string s){
    int root = 0;
    for (int i=0;i<s.size();i++){
	int next = s[i] - 'a';
    }


}

void getFail(){


}

int query(string s){

}

int main()
{
    int n;
    string s;
    for (int i=0;i<n;i++){
	cin >> s;
	insertWords(s);
    }
    fail[0] = 0;

    cin >> s;

    return 0;
}
