#include <iostream>
#include <cstring>
using namespace std;

struct HashNode
{
    int         data;
    HashNode    *next;
    HashNode(int data, HashNode* next)
    {
        this->data = data;
        this->next = next;
    }
};

class HashTable 
{
public:
    HashTable(size_t capacity) : _capacity(capacity), _size(0)
    {
        _table = new HashNode*[_capacity];
        memset(_table, 0, _capacity * sizeof (HashNode*));
    }

    ~HashTable()
    {
        for (size_t i=0; i<_capacity; ++i) {
            auto p = _table[i];
            auto q(nullptr);
            while (p) {
                q = p->next;
                delete p;
                p = q;
            }
        }
        delete [] _table;
    }

    size_t hash_func(int value)
    {
        return (value ^ 0xdeadbeef) % _capacity;
    }

    void insert(int value)
    {
        int key = hash_func(value);
        HashNode *p = _table[key];
        while (p && p->data != value) {
            p = p->next;
        }
        if (!p) {
            HashNode *new_node = new HashNode(value, _table[key]);
            _table[key] = new_node;
            ++_size;
        }
    }

    bool find(int value)
    {
        size_t key = hash_func(value);
        HashNode *p = _table[key];
        while (p && p->data != value) {
            p = p->next;
        }
        return (p != nullptr);
    }

    HashNode    **_table;
    size_t      _capacity;
    size_t      _size;
};


int main() 
{
    HashTable ht(10);


}
