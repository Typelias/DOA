#include <vector>

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