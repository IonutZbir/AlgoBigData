#include <random>
#include <cassert>
#include <iostream>
    
#define p 1000003

class FirstFamilyHash {
private:
    int m;
    int a, b;


public:
    FirstFamilyHash(int m) : m(m) { // inizializza i valori: this->m = m
        // assert(isPrime(m) && "[INFO]: m deve essere un numero primo\n");
        std::random_device rd;
        std::mt19937 gen(rd());
        
        std::uniform_int_distribution<int> domain(1, p - 1); // a deve essere > 0
        a = domain(gen);
        b = domain(gen);
    }

    int hash(const std::string& str) const {
        int hashValue = 0;
        size_t primeBase = 31;
        for (char c : str) {
            hashValue = (hashValue * primeBase + static_cast<int>(c)) % p;
        }
        return hash(hashValue);
    }

    int hash(int x) const {
        int result = ((a * x + b) % p) % m; 
        if(result < 0){ // in caso si va in negativo causa overflow
            result += m;
        }

        return result;
    }

    void printParams() const {
        std::cout << "a: " << a << ", b: " << b << ", p: " << p << ", m: " << m << std::endl;
    }

    bool isPrime(int n) const {
       if (n <= 1) return false;
        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const FirstFamilyHash& hash) {
        os << "FirstFamilyHash("
           << "m=" << hash.m
           << ", a=" << hash.a
           << ", b=" << hash.b
           << ")";
        return os;
    }
};

