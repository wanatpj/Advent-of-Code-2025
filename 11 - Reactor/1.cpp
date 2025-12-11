#include<iostream>
#include<map>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

map<string, int> ids;
int total_ids = 0;
vector<vector<int>> graph;

int id(const string& s) {
    auto it = ids.find(s);
    if (it != ids.end()) return it->second;
    return ids[s] = total_ids++;
}

int ensure_id(int id) {
    while(id >= graph.size()) {
        graph.push_back(vector<int>());
    }
    return id;
}

long long count_paths(vector<long long>& counter, int id, int target_id) {
    counter[id] = 0;
    int cnt = (id == target_id ? 1 : 0);
    for (int n : graph[id]) {
        if (counter[n] == -1) {
            cnt += count_paths(counter, n, target_id);
        } else if (counter[n] == 0) {
            throw runtime_error("not  a dag");
        } else {
            cnt += counter[n];
        }
    }
    return counter[id] = cnt;
}

int main() {
    string line;
    while(getline(cin, line)) {
        string from, to;
        stringstream ss(line);
        ss >> from;
        int from_id = ensure_id(id(from.substr(0, from.size() - 1)));
        while(ss >> to) graph[from_id].push_back(id(to));
    }
    vector<long long> counter(total_ids, -1);
    cout << count_paths(counter, id("you"), id("out")) << endl;
    return 0;
}