// 428 ms	160.8 MB

// https://leetcode-cn.com/problems/lru-cache/submissions/

#include <iostream>
using namespace std;
class LRUCache{ 

    struct Node{ 
        int data, key;
        Node* prev, *next;
        Node(){}
        Node(int _k, int _v): key(_k), data(_v) { prev = next = NULL; }
    };
    int siz, cap;
    Node* head, *tail;
    Node* H[10005];
public:
    LRUCache(int capacity){
        siz = 0; cap = capacity;
        head = new Node; tail = new Node;
        head->next = tail; tail->prev = head;
        for (int i=0; i<10005;i++) H[i] = 0;
    }
    int get(int key){
        if (!H[key]) return -1;
        rem_node(H[key]); ins_head(H[key]);
        return (H[key])->data;
    }
    void ins_head(Node* now){
        now->prev = head;
        now->next = head->next;
        head->next->prev = now;
        head->next = now;
    }
    void rem_node(Node* now){
         now->prev->next = now->next;
         now->next->prev = now->prev;
    }
    void remove_tail(){
        H[tail->prev->key] = 0;
        Node* toDel = tail->prev;
        toDel->prev->next = tail;
        tail->prev = toDel->prev;
        delete toDel;
    }
    void put(int key, int value){
       
        if (H[key]) {
            H[key]->data = value; 
            rem_node(H[key]); ins_head(H[key]);
            return;
        }
        if (siz == cap){
            remove_tail(); siz--;
        }
        Node *now = new Node(key, value);
        H[key] = now;  siz++;
        ins_head(now);
    }

};

// int main(){
// LRUCache lRUCache =  LRUCache(2);
// lRUCache.put(1, 1); // cache is {1=1}
// lRUCache.put(2, 2); // cache is {1=1, 2=2}
// lRUCache.get(1);    // return 1
// lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
// lRUCache.get(2);    // returns -1 (not found)
// lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
// lRUCache.get(1);    // return -1 (not found)
// lRUCache.get(3);    // return 3
// lRUCache.get(4);    // return 4

// }