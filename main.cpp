#include <bits/stdc++.h>
#include "include/serializer-core.hpp"

using namespace std;

int main()
{   vector<int> v = {1, 2, 3, 4, 5};
    Serializable<vector<int>> s(v);
    string json = s.serialize();
    cout << "Serialized: " << json << endl;
    s.deserialize(json);
    vector<int> deserialized = s;
    cout << "Deserialized: ";
    for (const auto& elem : deserialized) {
        cout << elem << " ";
    }
    cout << endl;
    return 0;
}