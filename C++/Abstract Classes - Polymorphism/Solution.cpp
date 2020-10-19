#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache {

   protected:
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : protected Cache
{
    public:
    LRUCache(int _copacity) { cp = _copacity; }

    ~LRUCache() {
        if(!mp.empty()) {
            for(auto itr: mp) { delete itr.second; }
        }
        mp.clear();
    }

    void set(int _key, int _value)
    {
        Node* newNode = nullptr;
        Node* firstNode = nullptr;
        if (!mp.empty()) {
            for (auto itr : mp) {
                if (!itr.second->prev) { firstNode = itr.second; }
            }
            auto itr = mp.find(_key);
            if (itr != mp.end()) {
                if (itr->first == firstNode->key) {
                    if (_value != firstNode->value) { firstNode->value = _value; }
                } else {
                    if (itr->second->prev) { itr->second->prev->next = itr->second->next; }
                    if (itr->second->next) { itr->second->next->prev = itr->second->prev; }
                    if (_value != itr->second->value) { itr->second->value = _value; }
                    itr->second->next = firstNode;
                    itr->second->prev = NULL;
                    firstNode->prev = itr->second;
                }
            } else {
                for (auto itr : mp) {
                    if (itr.second->value == _value) {
                        newNode = itr.second;
                        if (newNode->prev) { newNode->prev->next = newNode->next; }
                        if (newNode->next) { newNode->next->prev = newNode->prev; }
                        mp.erase(itr.first);
                        break;
                    }
                }
                if (!newNode) {
                    newNode = new Node(_key, _value);
                    if (cp > 0) { --cp; }
                    else if (mp.size() > 1) {
                        auto itr = mp.begin();
                        while (itr != mp.end()) {
                            if (!itr->second->next) { break; }
                            itr++;
                        }
                        delete itr->second;
                        mp.erase(itr);
                    }
                }

                firstNode->prev = newNode;
                newNode->next = firstNode;
                mp.insert(pair<int, Node*>(_key, newNode));
            }
        } else {
            if (!cp) return;

            newNode = new Node(_key, _value);
            mp.insert(pair<int, Node*>(_key, newNode));
            if (cp > 0) { --cp; }
        }
    }

    int get(int _key)
    {
        if(!mp.empty()) {
            auto itr = mp.find(_key);
            if (itr != mp.end()) { return itr->second->value; }
        }
        return -1;
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
