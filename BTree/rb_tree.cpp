
#include "btree6.cpp"

template <class Record>
class RB_tree : public B_tree<Record,1>
{
public:
    void search(const record& x);
    void insert(const Record& x)
    {
        auto x = search(x); if (x) return x;

        x = new NODE(); size++;
        solveDoubleRed(x);
        return x?x:_hot->p;
    }
protected:
    void solveDoubleRed()
    {

    }
    void solveDoubleBlack();
    int updateHeight();
};




