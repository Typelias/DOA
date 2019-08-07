#pragma once
#include <vector>
#include <iostream>
#include <list>

//#define Iter std::vector<int>::iterator
#define Table std::vector<std::list<int>>
namespace search
{
    struct node
    {
        int data;
        node* less = nullptr;
        node* more = nullptr;
        node* parent = nullptr;        
    };

    class binarySearchTree
    {
    public:
        template<typename Iter>
        binarySearchTree(Iter begin, Iter end)
        {
            root = new node;
            root->data = *begin;
            begin++;
            node* curr = root;
            while(begin != end)
            {
                insert(*begin, root);  
                begin++;
                    
            }
        }
        void insert(int val, node* parent);
        ~binarySearchTree();
        int* find(int target);
    private:
        node* root;
        node* findLastNode();
        void remove(node* node);
    };

    class Hashtable
    {
    public:
        template<typename Iter>
        Hashtable(Iter begin, Iter end)
        {
            size = findNextPrime(100);
            table = Table(size);
            for(auto i = begin; i != end; i++)
            {
                insert(*i);
            }
        }

        int sizeOfVector()
        {
            return table.size();
        }
        int maxHeight()
        {
            int max = 0;
            for(auto &c : table) if(max < c.size()) max = c.size();
            return max;
        }

        int* find(int target);
        void insert(int number);
    private:
        Table table;
        void resize();
        int findNextPrime(int prime);
        int size;
        int items = 0;
    };

    bool isPrime(int number);
    
    template<typename Iter>
    Iter linearSearch(Iter begin, Iter end, int target)
    {
        for(Iter i = begin; i!=end; i++)
            if(*i == target)
                return i;
        return end; 
    }  
    template<typename Iter, typename T>
    Iter binarySearch(Iter begin, Iter end, T target)
    {
        if(end >= begin)
        {
            Iter mid = begin + (end - begin) / 2;
            if(*mid == target)
                return mid;
            if(*mid > target)
                return binarySearch(begin, mid-1, target);
            return binarySearch(mid+1, end, target);
        }
        return end;

        /*auto left = begin, right = end - 1;

        while(left <= right)
        {
            auto mid = left + (right - left) / 2;

            if(target == *mid) return mid;
            else if(target < *mid) right = mid - 1;
            else if(target > *mid) left = mid + 1;
        }

        return end;*/        
    } 
}
