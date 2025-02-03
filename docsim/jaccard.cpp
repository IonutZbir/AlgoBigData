#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <format>

using namespace std;

#define MOD 100000

template <typename Container>
void write_on_file(const Container& v1, const Container& v2, float jsim, ofstream &file) {
    for (const auto& elem : v1) {
        file << elem << " ";
    }
    file << ", ";
    for (const auto& elem : v2) {
        file << elem << " ";
    }
    file << ", " << jsim << endl;
}

template <typename Container>
void print(const Container& v, string end){
    for (const auto& elem : v) {
        cout << elem << " ";
    }
    cout << end;
}

template <typename Container>
void print_double(const Container& v1, const Container& v2){
    print(v1, "\n");
    print(v2, "");
}

float jaccard_sim(set<int> &a, set<int> &b){
        
    vector<int> intersection;

    set_intersection(
        a.begin(), a.end(),
        b.begin(), b.end(),
        back_inserter(intersection) 
    );

    int sz_a = size(a);
    int sz_b = size(b);
    int sz_i = size(intersection);

    float jsim = (float) sz_i / (sz_a + sz_b - sz_i);

    // cout << sz_i << " " << sz_a << " " << sz_b << endl;

    return jsim;
}

int generate_sets_and_compute_jsim(size_t tests, string file_name){
    float jsim = 0;
    vector<int> v1, v2;
    set<int> s1, s2;

    ofstream jaccard_file(file_name);
    if (!jaccard_file.is_open()) {
        return -1;
    }

    // Initialize random engine and distributions
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_len(30, 60); // Random length between 30 and 60
    uniform_int_distribution<int> dist_val(0, MOD - 1); // Random values between 0 and MOD-1

    for (size_t i = 0; i < tests; ++i) {
        size_t lens = dist_len(gen);
        v1.clear();
        v2.clear();

        for (size_t j = 0; j < lens; ++j) {
            v1.push_back(dist_val(gen));
            v2.push_back(dist_val(gen));
        }

        s1 = set<int>(v1.begin(), v1.end());
        s2 = set<int>(v2.begin(), v2.end());

        jsim = jaccard_sim(s1, s2);
        write_on_file(s1, s2, jsim, jaccard_file);
    }

    jaccard_file.close();
    return 0;
}

vector<set<int>> generate_sets(float threshold){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_u(30, 60);        
    uniform_int_distribution<int> dist_val(0, MOD - 1); 

    int size_u = dist_u(gen); 
    int size_i = static_cast<int>(size_u * threshold); 
    int remain = size_u - size_i;

    set<int> intersection, set_a, set_b;

    while ((int)intersection.size() < size_i + (size_i * 0.1)) { // why (size_i * c)?? how much should be c?
        intersection.insert(dist_val(gen));
    }

    int remain_a = remain / 2;
    int remain_b = remain - remain_a;

    if(remain_a < remain_b){
        remain_a += 1;
    }else if (remain_b < remain_a){
        remain_b += 1;
    }

    while ((int)set_a.size() < remain_a) {
        int val = dist_val(gen);
        if (intersection.count(val) == 0) { 
            set_a.insert(val);
        }
    }

    while ((int)set_b.size() < remain_b) {
        int val = dist_val(gen);
        if (intersection.count(val) == 0 && set_a.count(val) == 0) { 
            set_b.insert(val);
        }
    }
    
    set_a.insert(intersection.begin(), intersection.end());
    set_b.insert(intersection.begin(), intersection.end());

    return {set_a, set_b};
}

int generate_sets_with_threshold(size_t tests, string file_name, float threshold){
    
    vector<int> v1, v2;
    set<int> s1, s2;

    ofstream jaccard_file(file_name);
    if (!jaccard_file.is_open()) {
        return -1;
    }

    for (size_t i = 0; i < tests; i++)
    {
        vector<set<int>> generated_sets = generate_sets(threshold);
        float jsim = jaccard_sim(generated_sets[0], generated_sets[1]);
        write_on_file(generated_sets[0], generated_sets[1], jsim, jaccard_file);
    }
    
    
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "[INFO]: Usage - make run ARGS=\"n_of_tests threshold\"" << endl;
        return -1;
    }

    string dir = "files_sets/";
    vector<string> files = {dir + "sets_jsim.csv",
    dir + "sets_jsim_" + string(argv[2]) + ".csv",
    dir + string(argv[1]) + "sets_jsim_" + string(argv[2]) + ".csv"};

    size_t tests = static_cast<size_t>(stoi(argv[1]));
    float threshold = static_cast<float>(stof(argv[2]));

    if (threshold < 0 or threshold > 1){
        cerr << "[ERROR]: The value of the threshold shoudl be: 0 <= threshold <= 1" << endl;
        return -1;
    }

    if(generate_sets_and_compute_jsim(tests, files[0]) < 0){
        cerr << "[Error]: Failed to open the file!" << endl;
    }else{
        cout << "[INFO]: The file '" << files[0] << "' was written successfully!" << endl;
    }

    if(generate_sets_with_threshold(tests, files[1], threshold) < 0){
        cerr << "[Error]: Failed to open the file!" << endl;
    }else{
        cout << "[INFO]: The file '" << files[1] << "' was written successfully!" << endl;
    }

    return 0;
}

