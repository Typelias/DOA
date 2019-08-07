#include <iostream>
#include <algorithm>
#include <random>
#include "search.h"
#include <chrono>
#include <fstream>
#include <cstring>

#define Iter std::vector<int>::iterator

struct Data
{
    int N;
    std::vector<double> times;
    float stdev;
    int sampels;
    double mean;

    void clear()
    {
        stdev = 0;
        mean = 0;
        times.clear();
    }
};

double mean(std::vector<double> inData)
{
    return std::accumulate(inData.begin(),inData.end(),0.0)/inData.size();
}

std::vector<int> SieveOfEratosthenes(int N)
{
    std::vector<int> ret;
    std::vector<bool> prime(N, true);

    for(int p=2; p*p<=N;p++)
    {
        if(prime[p] == true)
        {
            for(int i =p*p; i<=N; i+=p)
            {
                prime[i] = false;
            }
        }
    }


    for(int p=2; p<=N; p++)
    {
        if(prime[p])
        {
            ret.push_back(p);
        }
    }

    return ret;
    
}

std::vector<int> generatePrimes(int N)
{
    std::vector<int> ret;
    ret =  SieveOfEratosthenes(N);
    int i = N;
    while(ret.size() < N)
    {
        i <<= 1;
        ret = SieveOfEratosthenes(i);
    }

    return std::vector<int>(ret.begin(), ret.begin() + N);
}

int findRandomElement(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    std::vector<int> temp;
    std::sample(begin,end, std::back_inserter(temp),1,std::mt19937{std::random_device{}()});
    return temp.front();
}
void print(std::string method, Data data, bool printToFile)
{
    std::cout << method << "\n";
    std::cout << data.N << "\t" << data.mean << "\t" << data.stdev << "\t" <<data.sampels <<"\n";

    if(printToFile)
    {
        std::string filename = method + ".txt";
        std::ofstream out;
        out.open(filename,std::ostream::app);
        out << data.N << "\t" << data.mean << "\t" << data.stdev << "\t" <<data.sampels <<"\n";
        out.close();    
    }
}

double RunLinear(Iter begin, Iter end, int target)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto x = search::linearSearch(begin,end,target);
    auto stop = std::chrono::high_resolution_clock::now();
    if(*x != target)
    {
        std::cout << "Linear search failed\n";
        return -1;
    }
    std::chrono::duration<double,std::micro> time = stop - start;
    return time.count();
}

double RunBinary(Iter begin, Iter end, int target)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto x = search::binarySearch(begin,end,target);
    auto stop = std::chrono::high_resolution_clock::now();
    if(*x != target)
    {
        std::cout << "Binary search failed\n";
        return -1;
    }
    std::chrono::duration<double,std::micro> time = stop - start;
    return time.count();
}

std::vector<double> RunTree(Iter begin, Iter end, int samples, int N)
{
    std::vector<double> times;
    search::binarySearchTree s(begin,end);
    for(int i = 0; i< samples; i++)
    {
        int target = findRandomElement(begin,begin+N);
        auto start = std::chrono::high_resolution_clock::now();
        auto x = s.find(target);
        auto stop = std::chrono::high_resolution_clock::now();
        if(x == nullptr)
        {
            std::cout << "Tree failed\n";
            break;
        }
        std::chrono::duration<double,std::micro> time = stop - start;
        times.push_back(time.count());
    }
    
    return times;
}

std::vector<double> RunTable(Iter begin, Iter end, int samples, int N)
{
    std::vector<double> times;
    search::Hashtable t(begin,end);
    for(int i = 0; i< samples; i++)
    {
        int target = findRandomElement(begin,begin+N);
        auto start = std::chrono::high_resolution_clock::now();
        auto x = t.find(target);
        auto stop = std::chrono::high_resolution_clock::now();
        if(*x != target)
        {
            std::cout << "Table failed\n";
            break;
        }
        std::chrono::duration<double,std::micro> time = stop - start;
        times.push_back(time.count());
    }
    return times;
}

int main()
{
    int StartN = 10000;
    int samples = 10000;
    bool printToFile = false;
    int element;
    double sq_sum;
    Data data;
    data.sampels = samples;
    std::vector<int> g = generatePrimes(StartN*10);
    std::vector<int> shuf = g;
    std::random_device random;
    std::mt19937 mt(random());
    std::shuffle(shuf.begin(),shuf.end(),mt);

    auto start = std::chrono::high_resolution_clock::now();
    for(int mult = 1; mult<=10; mult++)
    {
        int N = StartN*mult;
        data.N = N;

        //Linear
        for(int i = 0; i< samples; i++)
        {
            element = findRandomElement(g.begin(),g.begin()+N);
            data.times.push_back(RunLinear(g.begin(),g.begin()+N,element));
        }
        data.mean = std::accumulate(data.times.begin(),data.times.end(),0.0)/data.times.size();
        sq_sum = std::inner_product(data.times.begin(), data.times.end(), data.times.begin(), 0.0);
        data.stdev = std::sqrt(sq_sum / data.times.size() - data.mean * data.mean);
        print("Linear Search",data, printToFile);
        data.clear();

        //Binary
        for(int i = 0; i< samples; i++)
        {
            element = findRandomElement(g.begin(),g.begin()+N);
            data.times.push_back(RunBinary(g.begin(),g.begin()+N,element));
        }
        data.mean = std::accumulate(data.times.begin(),data.times.end(),0.0)/data.times.size();
        sq_sum = std::inner_product(data.times.begin(), data.times.end(), data.times.begin(), 0.0);
        data.stdev = std::sqrt(sq_sum / data.times.size() - data.mean * data.mean);
        print("Binary Search",data, printToFile);
        data.clear();

        //Tree
        data.times = RunTree(shuf.begin(),shuf.begin()+N,samples,N); 
        data.mean = mean(data.times);
        sq_sum = std::inner_product(data.times.begin(), data.times.end(), data.times.begin(), 0.0);
        data.stdev = std::sqrt(sq_sum / data.times.size() - data.mean * data.mean);
        print("Binary Search Tree",data, printToFile);
        data.clear();

        //Table
        data.times = RunTable(shuf.begin(),shuf.end(),samples,N);
        data.mean = mean(data.times);
        sq_sum = std::inner_product(data.times.begin(), data.times.end(), data.times.begin(), 0.0);
        data.stdev = std::sqrt(sq_sum / data.times.size() - data.mean * data.mean);
        print("Hashtable",data, printToFile);
        data.clear();
    }


    //Linear
    /*for(int i = 0; i<samples; i++)
    {
        element = findRandomElement(g.begin(),g.end());
        auto start = std::chrono::high_resolution_clock::now();
        auto x = search::linearSearch(g.begin(),g.end(),element);
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> time = stop - start;
        if(x == g.end())
        {
            std::cout <<"Linear search failed\n";
            break;
        }
        data.times.push_back(time.count());
    }
    data.mean = std::accumulate(data.times.begin(),data.times.end(),0.0)/data.times.size();
    sq_sum = std::inner_product(data.times.begin(), data.times.end(), data.times.begin(), 0.0);
	data.stdev = std::sqrt(sq_sum / data.times.size() - data.mean * data.mean);
    print("Linear Search",data, printToFile);
    data.clear();

    //Binary
    for(int i = 0; i<samples; i++)
    {
        element = findRandomElement(g.begin(),g.end());
        auto start = std::chrono::high_resolution_clock::now();
        auto x = search::binarySearch(g.begin(),g.end(),element);
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> time = stop - start;
        if(x == g.end())
        {
            std::cout <<"Binary search failed\n";
            break;
        }
        data.times.push_back(time.count());
    }
    data.mean = std::accumulate(data.times.begin(),data.times.end(),0.0)/data.times.size();
    sq_sum = std::inner_product(data.times.begin(), data.times.end(), data.times.begin(), 0.0);
	data.stdev = std::sqrt(sq_sum / data.times.size() - data.mean * data.mean);
    print("Binary Search",data, printToFile);
    data.clear();

    //Tree
    std::random_device random;
    std::mt19937 mt(random());
    std::shuffle(g.begin(),g.end(),mt);
    start = std::chrono::high_resolution_clock::now();
    search::binarySearchTree s(g.begin(),g.end());
    stop = std::chrono::high_resolution_clock::now();
    time = stop - start;
    //std::cout << "Starting loop\n";
    for(int i = 0; i<samples; i++)
    {
        //if(i%1000 == 0) std::cout << i <<"\n";
        element = findRandomElement(g.begin(),g.end());
        auto start = std::chrono::high_resolution_clock::now();
        auto x = s.find(element);
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> time = stop - start;
        if(*x != element)
        {
            std::cout <<"Binary search tree failed\n";
            std::cout << "searched for: " << element << "found: " << *x <<"\n";
            auto y = std::find(g.begin(),g.end(),element);
            std::cout << "std::find found: " << *y <<"\n";
            break;
        }
        
        data.times.push_back(time.count());
    }
    //std::cout << "Loop done\n";
    data.mean = std::accumulate(data.times.begin(),data.times.end(),0.0)/data.times.size();
    sq_sum = std::inner_product(data.times.begin(), data.times.end(), data.times.begin(), 0.0);
    data.stdev = std::sqrt(sq_sum / data.times.size() - data.mean * data.mean);
    print("Binary Search Tree",data, printToFile);
    data.clear();



    //Table
    search::Hashtable t(g.begin(),g.end());
    for(int i = 0; i<samples; i++)
    {
        element = findRandomElement(g.begin(),g.end());
        auto start = std::chrono::high_resolution_clock::now();
        auto x = t.find(element);
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> time = stop - start;
        if(x == nullptr)
        {
            std::cout <<"Hashtable failed\n";
            break;
        }
        data.times.push_back(time.count());
    }
    data.mean = std::accumulate(data.times.begin(),data.times.end(),0.0)/data.times.size();
    sq_sum = std::inner_product(data.times.begin(), data.times.end(), data.times.begin(), 0.0);
    data.stdev = std::sqrt(sq_sum / data.times.size() - data.mean * data.mean);
    print("Hashtable",data, printToFile);
    data.clear();
    std::cout << "Binary Tree generated in time: " << time.count() << "ms\n";
    std::cout <<"size of table: Width: " << t.sizeOfVector() << " Height " << t.maxHeight() << "\n";
    */
   
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = stop - start;
    std::cout << "Total runtime: " << time.count() << "\n";
    return 0;
}