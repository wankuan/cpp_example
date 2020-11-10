#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
using namespace std;
template <class K, class V>
class Map {
public:
    V& operator[](const K& k);
    pair<K, V>* begin() {
        return &elem[0];
    }
    pair<K, V>* end() {
        return &elem[0] + elem.size();
    }

private:
    vector<pair<K, V>> elem;
};

template <class K, class V>
V& Map<K, V>::operator[](const K& k) {
    for (auto& x : elem) {
        if (k == x.first) {
            return x.second;
        }
    }
    elem.push_back({k, V{}});
    return elem.back().second;
}

int main() {
    Map<string, int> map_buf;
    for(string s; cin>>s;){
        ++map_buf[s];
    }
    for(auto &x:map_buf){
        cout << "string: " << x.first << " count: " << x.second << endl;
    }
}
