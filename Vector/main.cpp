#include <iostream>
#include "_vector.h"
#include <algorithm>
#include "search.h"


_vector<int> SieveOfEratosthenes(int N)
{
    _vector<int> ret;
    _vector<bool> prime(N, true);

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
    std::cout << "Returning vector from sieve\n";
    return ret;
    
}

_vector<int> generatePrimes(int N)
{
    _vector<int> ret;
    ret =  SieveOfEratosthenes(N);
    int i = N;
    while(ret.size() < N)
    {
        i <<= 1;
        ret = SieveOfEratosthenes(i);
    }
    std::cout << "While loop done\n";
    return _vector<int>(ret.begin(), ret.begin() + N);
}

int main()
{
    std::cout << "Starting\n";
    _vector<int> s = generatePrimes(100);
    std::cout << "Created vector\n";
    return 0;
}
