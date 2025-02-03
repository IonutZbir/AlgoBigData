#include <random>
#include <iostream>
#include <vector>
#include <cmath>

#include "hash_functions.cpp"

using namespace std;
    
int main(){

    uniform_int_distribution<int> dist(1, 2500);

    random_device rd;
    mt19937 gen(rd());

    int m = 211;
    vector<int> v(m, 0);

    FirstFamilyHash ffh = FirstFamilyHash(m);

    ffh.printParams();

    // for (size_t i = 0; i < m; i++)
    // {
    //     int n = dist(gen);
    //     size_t index = ffh.hash(n); 
    //     v[index] = n;
    // }

    // for (size_t i = 0; i < m; i++)
    // {
    //     cout << i << ", " << v[i] << endl;
    // }

    string s = "Ciao mondo!";
    string s1 = "Hello World!";

    cout << s << " - " << ffh.hash(s) << endl;
    cout << s1 << " - " << ffh.hash(s1) << endl;

    return 0;
}