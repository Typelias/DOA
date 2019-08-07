#include "search.h"
#include <algorithm>


namespace search
{
    binarySearchTree::~binarySearchTree()
    {
        remove(root);
    }
    void binarySearchTree::insert(int val, node* parent)
    {
        if(val<parent->data)
        {
            if(parent->less) insert(val,parent->less);
            else
            {
                parent->less = new node;
                parent->less->data = val;
                parent->less->parent = parent;
            }
            
        }
        else if(val>parent->data)
        {
            if(parent->more) insert(val,parent->more);
            else
            {
                parent->more = new node;
                parent->more->data = val;
                parent->more->parent = parent;
            }
            
        }
    }
    void binarySearchTree::remove(node* node)
    {
        if(node->less) remove(node->less);
        if(node->more) remove(node->more);
        delete node;
    }

    int* binarySearchTree::find(int target)
    {
        node* curr = root;
        while(curr->data != target)
        {
            if(target<curr->data)
                if(curr->less != nullptr)
                    curr = curr->less;
                else
                    return nullptr;
            if(target>curr->data)
                if(curr->more != nullptr)
                    curr = curr->more;
                else
                    return nullptr;
                
        }
        return &curr->data;        
    }
//Hashtabel
    void Hashtable::insert(int number)
    {
        items++;
        if(static_cast<double>(items)/table.size() >= 0.5)
            resize();
        int index = number % table.size();
        table[index].push_front(number);
    }

    void Hashtable::resize()
    {
        items = 0;
        auto temp = table;
        int newSize = findNextPrime(table.size()*2);
        table = Table(newSize);
        for(auto &list : temp)
            for(auto &item : list)
                insert(item);
    }

    bool isPrime(int number)
    {
        for(int i = 2; i <=number/2; i++)
            if(number % i == 0)
                return false;
        return true;
    }

    int Hashtable::findNextPrime(int prime)
    {
        prime+=50;
        while (!isPrime(prime))
            prime++;
        return prime;
    }

    int* Hashtable::find(int target)
    {
        int index = target % table.size();
        auto find = linearSearch(table[index].begin(), table[index].end(),target);
        if(find != table[index].end())
            return &*find;
        else
            return nullptr;
    }
}
