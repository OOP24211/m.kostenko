#include "../include/LRU.hpp"
#include <cstddef>

struct LRUCache::Node{
    int key;
    int value;
    Node *prev;
    Node *next;
    
    Node(int k, int v):key(k),value(v), prev(nullptr), next(nullptr){}

};

class LRUCache::LinkedList{
    private:
    Node *head;
    Node *tail;
    public:
    LinkedList(): head(nullptr), tail(nullptr){}
    Node* GetHead(){
        return head;
    }
    Node* GetTail(){
        return tail;
    }
    Node* push_front(int key, int value){
        Node *ptr = new Node(key, value);
        ptr->next = head;

        if (head!=nullptr) {
            head->prev=ptr;
        }
        if(tail==nullptr){
            tail=ptr;
        }

        head=ptr;

        return ptr;
    }

    void pop_back(){
        if(tail == nullptr)return;

        Node *ptr = tail->prev;
        if(ptr!=nullptr){
            ptr->next = nullptr;
        }
        else head = nullptr;
        delete tail;
        tail = ptr;
    }

    void remove(Node* node){
        Node *ptr = node;
        if(ptr == nullptr) return;

        if(ptr == head){
            if(ptr->next)ptr->next->prev = nullptr;
            head = ptr->next;
        }
        else if (ptr ==tail) {
            ptr->prev->next=nullptr;
            tail = ptr->prev;
        } else{
        Node *left = ptr->prev;
        Node *right = ptr->next;
        left->next = right;
        right->prev = left;
        }
        delete ptr;
    } 

    void addToFront(Node* node){
        node->next = head;
        if(head != nullptr){
            head->prev = node;  
        }
        if(tail == nullptr){
            tail = node;
        }
        head = node;

    }
    void moveToFront(Node* node){
        remove(node);
        addToFront(node);
    }
};

LRUCache::LRUCache(size_t cap): capacity(cap){
    list = new LinkedList();
}

LRUCache::~LRUCache(){
    delete list;
}

int LRUCache::get(int key){
    if (capacity == 0) return -1;

    auto iterator = mapCache.find(key);
    if (iterator!=mapCache.end()){
        list->moveToFront(iterator->second);
        return iterator->second->value;
    }
    else {
        return -1;
    }

}
 
void LRUCache::put(int key, int value){
    if (capacity == 0) return;

    auto iterator = mapCache.find(key);
    if(iterator != mapCache.end()){
        mapCache[key]->value = value;
        list->moveToFront(mapCache[key]);
    }
    else {
         if(mapCache.size()>=capacity){
            int old_key = list->GetTail()->key;
            list->pop_back();
            mapCache.erase(old_key);
        }
        Node* new_node = list->push_front(key, value);
        mapCache[key]= new_node;       
    }
}

int LRUCache::operator[](int key){
    return get(key);
}
