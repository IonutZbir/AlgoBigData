#include <iostream>
#include <random>
#include <vector>

#define N 1000000

using namespace std;

class FirstFamilyHash{
    public:
        random_device rd;
        mt19937 gen;
        vector<int> a;

        FirstFamilyHash(int m): gen(rd()){
            uniform_int_distribution<int> domain(0, m - 1); // Random length between 30 and 60
            
            for (size_t i = 0; i < m; i++)
            {
                /* code */
            }
            
            
            a = domain(gen);
        }
}