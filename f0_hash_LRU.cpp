struct doubleList {
    int key, value;
    doubleList *prev, *next;
    doubleList(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {};
    doubleList() : prev(nullptr), next(nullptr) {};
};

class LRUCache {

private:
    int sz;
    int cap = 0;
    doubleList *head, *tail;
    unordered_map<int, doubleList*> cache;

public:
    LRUCache(int capacity) : sz(capacity) {
        head = new doubleList();
        tail = new doubleList();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        int ans;
        if (cache.count(key)){
            ans = cache[key]->value;
            // remove to head
            doubleList *x = cache[key];
            remove_node(x);
            insert_head(x);
        }
        else ans = -1;
        return ans;
    }
    
    void put(int key, int value) {
        if (cache.count(key)){
            cache[key]->value = value;
            remove_node(cache[key]);
            insert_head(cache[key]);
        }
        else{
            cap++;
            if (cap > sz){
                remove_tail();
                cap--;
            }
            doubleList *D = new doubleList(key, value);
            insert_head(D);
            cache[key] = D;
        }
    }

    void remove_node(doubleList* x){
        x->prev->next = x->next;
        x->next->prev = x->prev;  
    }

    void insert_head(doubleList *x){
        x->next = head->next;
        head->next->prev = x;
        head->next = x;
        x->prev = head;
    }

    void remove_tail(){
        cache.erase(tail->prev->key);
        remove_node(tail->prev);        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */