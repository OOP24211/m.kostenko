#include "../include/LFU.hpp"
#include <list>
#include <iostream>

LFUCache::LFUCache(size_t cap) : capacity(cap), minFrequency(1) {
    if(capacity == 0){
        std::cout << "CACHE DISABLED" << std::endl;
    }
}

struct LFUCache::Node{
private:
    int key;
    int value;
    int frequency;
public:
    Node(int k, int v): key(k), value(v), frequency(1){}
    int GetFreq(){
        return this->frequency;
    }
    int GetValue(){
        return this->value;
    }
    int GetKey(){
        return this->key;
    }
    void SetValue(int value){
        this->value = value;
        return;
    }
    void SetFreq(int freq){
        this->frequency = freq;
        return;
    }
};

class LFUCache::FrequencyList{
private:
    std::list<Node*> nodes;
public:
    void addNode(Node* node){
        nodes.push_front(node);
    }
    void removeNode(Node* node){
        nodes.remove(node);
    }

    Node* getLRUNode(){
        return nodes.back();
    }

    bool empty(){
        return nodes.empty();
    }
};

int LFUCache::get(int key){
    if (capacity == 0) {
        return -1;
    }
    auto keyIterator = mapKey.find(key);
    if(keyIterator == mapKey.end())return -1;
  
    Node* node = mapKey[key];
    int oldFreq = node->GetFreq();
    int newFreq = oldFreq + 1;

    mapFreq[oldFreq]->removeNode(node);

    if(mapFreq[oldFreq]->empty()){
        delete mapFreq[oldFreq];
        mapFreq.erase(oldFreq);

        if(oldFreq == minFrequency){
            minFrequency = newFreq;
        }

    }

    node->SetFreq(newFreq);

    auto freqIterator = mapFreq.find(newFreq);
    if (freqIterator == mapFreq.end()) {
        mapFreq[newFreq] = new FrequencyList();
    }
    mapFreq[newFreq]->addNode(node);

    return node->GetValue();
}

void LFUCache::put(int key, int value){
    
    auto iterator = mapKey.find(key);
    if (iterator!=mapKey.end()){
        mapKey[key] ->SetValue(value);
        get(key);
        return;
    }
    if(mapKey.size()>=capacity){
        FrequencyList *freqList = mapFreq[minFrequency];
        Node *nodeDelete = freqList->getLRUNode();

        freqList->removeNode(nodeDelete);
        mapKey.erase(nodeDelete->GetKey());
        delete nodeDelete;
        
        if(mapFreq[minFrequency]->empty()){
            delete mapFreq[minFrequency];
            mapFreq.erase(minFrequency);
        }
    }

    Node *newNode = new Node(key,value);
    mapKey[key]  = newNode;

    if(mapFreq.find(1) == mapFreq.end()){
        mapFreq[1] = new FrequencyList();
    }

    if (mapFreq[1]->empty()){
        mapFreq[1] = new FrequencyList;
    }
    mapFreq[1]->addNode(newNode);
    minFrequency = 1;
}

int LFUCache::operator[](int key) {
    return get(key);
}

LFUCache::~LFUCache() {
    for (auto& pair : mapKey) delete pair.second;
    for (auto& pair : mapFreq) delete pair.second;

}
