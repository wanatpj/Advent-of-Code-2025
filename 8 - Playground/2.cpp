#include<algorithm>
#include<cstdio>
#include<functional>
#include<tuple>
#include<vector>

using namespace std;

class DisjointSet {
public:
    DisjointSet(int n) : n(n), parent(vector<int>(n)) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    void union_(int a, int b) {
        parent[find(a)] = find(b);
    }
private:
    int n;
    vector<int> parent;
};

long long euclid_distance_sq(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    long long x = get<0>(a) - get<0>(b);
    long long y = get<1>(a) - get<1>(b);
    long long z = get<2>(a) - get<2>(b);
    return x*x + y*y + z*z;
}

int main(){
    int x, y, z;
    vector<tuple<int, int, int>> space;
    while(scanf("%d,%d,%d", &x, &y, &z) != EOF) {
        space.push_back(tuple(x, y, z));
    }
    vector<tuple<long long, int, int>> distances;
    for (int i = 0; i < space.size(); i++) {
        for (int j = 0; j < space.size(); j++) {
            if (i < j) {
                distances.push_back(tuple(euclid_distance_sq(space[i], space[j]), i, j));
            }
        }
    }
    sort(distances.begin(), distances.end());
    DisjointSet ds(space.size());
    int op_cnt = 0;
    long long result = -1;
    for (int i = 0; i < distances.size(); i++) {
        if (ds.find(get<1>(distances[i])) != ds.find(get<2>(distances[i]))) {
            ds.union_(get<1>(distances[i]), get<2>(distances[i]));
            op_cnt++;
            if (op_cnt == space.size() - 1) {
                result = get<0>(space[get<1>(distances[i])]) * (long long)get<0>(space[get<2>(distances[i])]);
            }
        }
    }
    printf("%lld\n", result);
    return 0;
}