

#include <unordered_set>
#include <iostream>

using namespace std;

class T
{
public:
    int a, b;
    bool operator==(const T& ano)const {
        return a== ano.a && b == ano.b; 
    }
    struct HF{
        std::size_t operator()(const T& ano) const{
            return std::hash<int>()(ano.a + ano.b);

        }


    };
};

unordered_set<T, T::HF> test_set;
int main()
{
    T t1 = {1,2};
    T t3 = {2,1};
    T t2 = {2,3};
    test_set.insert(t1);
    test_set.insert(t2);
    test_set.insert(t3);
    cout << test_set.size() << endl;

}