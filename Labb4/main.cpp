#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <random>
#include "RedAndBlackTree.h"
#include "BinarySearch.h"
#include <chrono>

std::vector<int> GenerateVector(int size)
{
    std::random_device rnd_device;

    std::mt19937 mersenne_engine{rnd_device()};
    std::uniform_int_distribution<int> dist{1, 52};

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    std::vector<int> ret(size);

    std::generate(ret.begin(), ret.end(), gen);

    return ret;
}

int findRandomElement(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    std::vector<int> temp;
    std::sample(begin, end, std::back_inserter(temp), 1, std::mt19937{std::random_device{}()});
    return temp.front();
}

int main()
{
    search::RedAndBlackTree<int> tree;
    auto vec = GenerateVector(1000);
    std::cout << "Vector generated\n";
    for (auto &c : vec)
    {
        std::cout << c << "\n";
        tree.insert(c);
    }
    std::cout << "Tree created\n";

    std::sort(vec.begin(), vec.end());

    std::cout << "Sorting done\n";

    auto element = findRandomElement(vec.begin(), vec.end());

    auto start = std::chrono::high_resolution_clock::now();
    auto x = tree.search(element);
    auto stop = std::chrono::high_resolution_clock::now();
    if (x != nullptr)
    {
        std::chrono::duration<double, std::micro> time = stop - start;
        std::cout << "Tree: " << time.count() << "\n";
    }

    start = std::chrono::high_resolution_clock::now();
    auto y = search::BinarySearch(vec.begin(), vec.end(), element);
    stop = std::chrono::high_resolution_clock::now();
    if (y != vec.end())
    {
        std::chrono::duration<double, std::micro> time = stop - start;
        std::cout << "Bin: " << time.count() << "\n";
    }

    return 0;
}