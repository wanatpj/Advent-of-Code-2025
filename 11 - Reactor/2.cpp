#include<iostream>
#include<map>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

struct Counter {
    long long null;
    long long fft;
    long long dac;
    long long fft_dac;

    bool operator==(const Counter&) const = default;

    Counter& operator+=(const Counter& other) {
        this->null += other.null;
        this->fft += other.fft;
        this->dac += other.dac;
        this->fft_dac += other.fft_dac;
        return *this;
    }
};

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

int fft_id = id("fft");
int dac_id = id("dac");
int svr_id = id("svr");
int out_id = id("out");

Counter count_paths(vector<Counter>& counter, int id, int target_id) {
    counter[id] = Counter{};
    Counter cnt = Counter{.null=(id == target_id ? 1 : 0), .fft=0, .dac=0, .fft_dac=0};
    for (int n : graph[id]) {
        if (counter[n] == Counter{.null=-1}) {
            cnt += count_paths(counter, n, target_id);
        } else if (counter[n] == Counter{}) {
            throw runtime_error("not  a dag");
        } else {
            cnt += counter[n];
        }
    }
    if (id == fft_id) {
        cnt.fft += cnt.null;
        cnt.fft_dac += cnt.dac;
        cnt.null = 0;
        cnt.dac = 0;
    } else if (id == dac_id) {
        cnt.dac += cnt.null;
        cnt.fft_dac += cnt.fft;
        cnt.null = 0;
        cnt.fft = 0;
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
    vector<Counter> counter(total_ids, Counter{.null=-1});
    cout << count_paths(counter, svr_id, out_id).fft_dac << endl;
    return 0;
}