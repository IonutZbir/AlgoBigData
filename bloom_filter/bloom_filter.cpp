#include <vector>
#include <iostream>
#include <set>
#include <random>

#include "../hash_functions/hash_functions.cpp"

bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false; 

    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

long long nextPrime(long long n) {
    if (n <= 1) return 2; 
    long long candidate = n + (n % 2 == 0 ? 1 : 2);
    while (!isPrime(candidate)) {
        candidate += 2;
    }
    return candidate;
}

class BloomFilter {
private:
    std::vector<bool> filter;
    std::vector<FirstFamilyHash> hash_funcs;
    size_t k = 10;
public:
    std::set<int> good_values;

    BloomFilter(const std::set<int>& good_values)
    {
        
        int n = good_values.size() * 10;
        int m = nextPrime(n);

        this->good_values.insert(good_values.begin(), good_values.end());

        filter = std::vector<bool>(m, false);

        for (size_t i = 0; i < k; i++)
        {
            FirstFamilyHash h = FirstFamilyHash(m);
            hash_funcs.push_back(h);
            std::cout << h << std::endl;
        }
        
        for (auto elem : good_values)
        {
            for (auto &f : hash_funcs)
            {
                size_t index = f.hash(elem);
                filter[index] = true;
            }
        }
    }

    bool filtering(int x){
        for (auto &f : hash_funcs)
        {
            size_t index = f.hash(x);
            if(!filter[index]){
                return false;
            }
        }

        return true;
    }

    // returns a copy of the filter
    std::vector<bool> get_filter(){ 
        return std::vector<bool>(filter.begin(), filter.end());
    }   
};