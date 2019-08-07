#include "sort.h"

std::vector<int> increasing(int N)
{
    std::vector<int> out;
    for(int i = 0; i< N; i++)
    {
        out.push_back(i);
    }
    return out;    
}

std::vector<int> decreasing(int N)
{
    std::vector<int> out;
    for(int i = N; i>0; i--)
    {
        out.push_back(i);
    }
    return out;    
}
std::vector<int> constant(int N, int val)
{
    std::vector<int> out;
    for(int i = 0; i< N; i++)
    {
        out.push_back(val);
    }
    return out;    
}


int main()
{
    int N = 200000;
    int sampels = 1;
    std::cout << "Increasing\n";
    sorting s(increasing(N),0,sampels,"[Increasing]");
    s.insertionSort();
    s.selectionSort();
    s.quickSort();
    s.medianQuickSort();
    s.standardSort();
    std::cout << "Decreasing\n";
    s = sorting(decreasing(N),0,sampels,"[Decreasing]");
    s.insertionSort();
    s.selectionSort();
    s.quickSort();
    s.medianQuickSort();
    s.standardSort();
    std::cout << "Constant\n";
    s = sorting(decreasing(N),0,sampels,"[Constant]");
    s.insertionSort();
    s.selectionSort();
    s.quickSort();
    s.medianQuickSort();
    s.standardSort();
    std::cout << "Random\n";
    s = sorting(N,0,sampels,"[Random]");
    s.insertionSort();
    s.selectionSort();
    s.quickSort();
    s.medianQuickSort();
    s.standardSort();
    return 0;
}