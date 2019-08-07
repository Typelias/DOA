#include <iostream>
#include "primes.h"
#include <algorithm>
#include <numeric>
#include <chrono>
#include <string>
using INT_V = std::vector<int>;
#define INT_MAX std::numeric_limits<int>::max()
#define INT_MIN std::numeric_limits<int>::min()

struct person
{
    int age;
    std::string name;
};

INT_V numbers(int size)
{
    srand(time(NULL));
    INT_V data;
    for(int i = 0; i < size; i++)
    {
        data.push_back(rand()% 100 + 0);
    }
    return data;
}

struct print_person
{
    void operator()(person p){ std::cout << p.name << " " << p.age << "\n"; }
};

int main()
{
    std::vector<person> p;
    p.push_back({25, "kalle"});

    std::vector<int> bigBoy = numbers(10);

    print_person g;
    std::for_each(p.begin(), p.end(), g);


    for(auto &c : bigBoy) std::cout << c << "\n";
    
    /*auto start = std::chrono::high_resolution_clock::now();
    std::sort(bigBoy.begin(), bigBoy.end());
    auto stop = std::chrono::high_resolution_clock::now();


    std::chrono::duration<double, std::milli> time = stop - start;

    std::cout << time.count() << "\n";*/
    
    return 0;

}