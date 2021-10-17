

template <class Record, int order>
struct Node
{
    Record data[order-1];
    Node<Record, order>* branch[order];
    Node() {}
}