#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

template <typename Container>
void print(const Container& v, string end){
    for (const auto& elem : v) {
        cout <<"'" << elem << "', ";
    }
    cout << end;
}

set<string> get_k_shingles_from_string(int k, const string& data){
    set<string> k_shingles;

    for (size_t cursor = 0; cursor < data.size(); cursor++) {
        string k_shingle = "";
        for (size_t i = cursor; i < cursor + k && i < data.size(); i++) {
            k_shingle += data[i];
        }
        k_shingles.insert(k_shingle);
    }
    return k_shingles;
}

set<string> get_k_shingles_from_doc(int k, const string& file_path){
    ifstream doc(file_path);
    if (!doc.is_open()) {
        cerr << "Errore nell'apertura del file!\n";
        return {};
    }

    set<string> k_shingles;
    string line;
    while (getline(doc, line)) {
        set<string> temp = get_k_shingles_from_string(k, line);
        k_shingles.insert(temp.begin(), temp.end());
    }

    doc.close();
    return k_shingles;
}

int main(){
    string str = "Sempre il 12 le avanguardie del corpo di spedizione britannico attraversarono la Manica";
    
    set<string> shingles = get_k_shingles_from_string(4, str);
    print(shingles, "\n");

    return 0;
}
