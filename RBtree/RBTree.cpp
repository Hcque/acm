
template <class Record>
struct Bnode{
    Record data;
    Bnode<Record> *left, *right;
    Bnode(const Record &target): data(target), left(nullptr), right(nullptr) {}
    Bnode(){}
};

enum Color {red, black};
template <class Record>
struct RB_node : public Bnode<Record>{
    Color color;
    RB_node(const Record &target): color(red), data(target) {}
    RB_node(){}
};



