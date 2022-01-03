
#include <string>
#include <iostream>

using namespace std;

string arr[32] = {"0","*","+","*","a","b","c","-","d"};

void f(int node)
{
    if (node> 8) return;
    int flag = (arr[node] == "+" || arr[node] == "*" || arr[node] == "-");
    if (!flag) cout << arr[node];
    else{
        cout << "(";
        f(node*2);
        cout << arr[node];
        f(node*2+1);
        cout << ")";
    }



}
int main()
{
    f(1);

}