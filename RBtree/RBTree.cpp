
template <class Record>
struct Bnode{
    Record data;
    Bnode<Record> *left, *right;
    Bnode(const Record &target): data(target), left(nullptr), right(nullptr) {}
    Bnode(){}
    virtual Color get_color() const { return red; }
    virtual void set_color(Color c) {}
};

enum Color {red, black};
template <class Record>
struct RB_node : public Bnode<Record>{
    Color color;
    RB_node(const Record &target): color(red), data(target) {}
    RB_node(){}
    void set_color(COlor c);
    Color get_color() const;
};


enum RB_code {okay, red_node, left_red, right_red, duplicated};
#define BNODE Bnode<Record>
#define NODE RB_node<Record>

template <class Record>
class RB_tree
{
public:
    int insert(const Record& new_entry);
private:
    RB_code rb_insert(BNODE* cur, const Record& new_entry);
    RB_code modify_left(BNODE* &cur, RB_code& child_status);

    RB_node<Record> *root;
};

template <class Record>
int RB_tree<Record>::insert(const Record& new_entry)
{
    RB_code status = rb_insert(root, new_entry);
    switch (status)
    {
        case red_node:
            root->set_color(black);
        case okay:
            return 1;
        case duplicated:
            return 2;
        case right_red:
        case left_red:
            std::cerr << "INSERT ERROR\n" ;
            return -1;
    }
}

template <class Record>
RB_code RB_tree<Record>::rb_insert(BNODE* cur, const Record& new_entry)
{
    RB_code status, child_status;
    if (cur == NULL){
        cur = new NODE(new_entry);
        status = red_node;
    }
    else if (new_entry == cur->data) return duplicated;
    else if (new_entry < cur->data) {
        child_status = rb_insert(cur->left, new_entry);
        status = modify_left(cur, child_status);
    }
    else{
        child_status = rb_insert(cur->right, new_entry);
        status = modify_right(cur, child_status);
    }
    return status;
}

template <class Record>
RB_code RB_tree<Record>::modify_left(BNODE* &cur, RB_code& child_status)
{
    RB_code sttaus = okay;
    BNODE *aunt = cur->right;
    Color aunt_color = black;
    if (aunt != NULL) aunt_color = aunt->get_color();
    switch (child_status) {
        case okay:
            break;
        case red_node:
            if (cur->get_color() == red) status = left_red;
            else status = okay;
            break;
        case left_red:
            if (aunt_color == black) status = rotate_right(cur);
            else status = flip_color(cur);
            break;
        case right_red:
            if (aunt_color == black) status = double_rotate_right(cur);
            else status = flip_color(cur);
            break;
    }
    return status;
}




