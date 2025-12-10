#include<algorithm>
#include<cmath>
#include<complex>
#include<cstdio>
#include<iterator>
#include<map>
#include<ranges>
#include<vector>

using namespace std;


struct Corner {
    int prev_dfirst;
    int prev_dsecond;
    int next_dfirst;
    int next_dsecond;

    auto operator<=>(const Corner& other) const = default;
};

struct ChangeLocation {
    int change;
    int dfirst;
    int dsecond;
};


const map<Corner, ChangeLocation> change_location = {
    {{-1,  0,  0, -1}, { 1, 1, 0}},
    {{-1,  0,  0,  1}, { 1, 0, 0}},
    {{ 1,  0,  0, -1}, { 1, 1, 1}},
    {{ 1,  0,  0,  1}, { 1, 0, 1}},
    {{ 0, -1, -1,  0}, {-1, 1, 0}},
    {{ 0, -1,  1,  0}, {-1, 1, 1}},
    {{ 0,  1, -1,  0}, {-1, 0, 0}},
    {{ 0,  1,  1,  0}, {-1, 0, 1}},
};


struct PrefSum2D {
    vector<vector<long long>> pref_sum;
    map<int, int> dx_mapping;
    map<int, int> dy_mapping;

    bool full_rectangle(const pair<int, int>& A, const pair<int, int>& B) const {
        pair<int, int> mA = make_pair(dx_mapping.find(min(A.first, B.first))->second, dy_mapping.find(min(A.second, B.second))->second);
        pair<int, int> mB = make_pair(dx_mapping.find(max(A.first, B.first))->second, dy_mapping.find(max(A.second, B.second))->second);
        return (
            pref_sum[mB.first][mB.second] - pref_sum[mB.first][mA.second-1] - pref_sum[mA.first-1][mB.second] + pref_sum[mA.first-1][mA.second-1]
            == (mB.first - mA.first + 1) * (long long)(mB.second - mA.second + 1)
        );
    }
};

void basic_pref_sum(vector<vector<long long>>& arr) {
    size_t N = arr.size(), M = arr[0].size();
    for (int i = 1; i < N; i++) arr[i][0] += arr[i-1][0];
    for (int j = 1; j < M; j++) arr[0][j] += arr[0][j-1];
    for (int i = 1; i < N; i++) 
        for (int j = 1; j < M; j++)
            arr[i][j] += arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1];
}

template<typename T>
T mod_at(const vector<T>& vec, int n) {
    return vec[(n + vec.size()) % vec.size()];
}

template<typename T>
T sgn(T a) {
    return (a > T(0)) - (a < T(0));
}

PrefSum2D compute_pref_sum(const vector<pair<int, int>>& points) {
    vector<int> x;
    vector<int> y;
    transform(points.begin(), points.end(), back_inserter(x), [](const pair<int, int>& point) { return point.first; });
    transform(points.begin(), points.end(), back_inserter(y), [](const pair<int, int>& point) { return point.second; });
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    map<int, int> dx_mapping;
    map<int, int> dy_mapping;
    for (int i = 0; i < x.size(); i++) dx_mapping[x[i]] = i + 1;
    for (int i = 0; i < y.size(); i++) dy_mapping[y[i]] = i + 1;
    vector<vector<long long>> pref_sum(x.size() + 2, vector<long long>(y.size() + 2, 0));
    int border_idx = min_element(points.begin(), points.end()) - points.begin();
    int shift = (
        points[border_idx].first == points[(border_idx + 1 ) % points.size()].first
        ? 1
        : -1
    );
    for (int i = 0; i < points.size(); i++) {
        auto prev = mod_at(points, (i - 1) * shift);
        auto current = mod_at(points, i*shift);
        auto next = mod_at(points, (i + 1) * shift);
        ChangeLocation cl = change_location.find(
            Corner{
                .prev_dfirst=sgn(current.first-prev.first),
                .prev_dsecond=sgn(current.second-prev.second),
                .next_dfirst=sgn(next.first-current.first),
                .next_dsecond=sgn(next.second-current.second)}
        )->second;
        pref_sum[dx_mapping[current.first] + cl.dfirst][dy_mapping[current.second] + cl.dsecond] += cl.change;
    }
    basic_pref_sum(pref_sum);
    basic_pref_sum(pref_sum);
    return PrefSum2D{
        .pref_sum=pref_sum,
        .dx_mapping=dx_mapping,
        .dy_mapping=dy_mapping
    };
}


long long find_max_area(
    const vector<pair<int, int>>& prev_points,
    const pair<int, int>& corner,
    const PrefSum2D& prefSum2D
) {
    long long max_value = -1;
    for (auto& point : prev_points) {
        if (!prefSum2D.full_rectangle(point, corner)) continue;
        long long dfirst = abs(corner.first - point.first);
        long long dsecond = abs(corner.second - point.second);
        max_value = max(max_value, (dfirst + 1) * (long long)(dsecond + 1));
    }
    return max_value;
}

int main(){
    int a, b;
    vector<pair<int, int>> points;
    while(scanf("%d,%d", &a, &b) != EOF) points.push_back(make_pair(a, b));
    long long max_area = -1;
    PrefSum2D prefSum2D = compute_pref_sum(points);
    sort(points.begin(), points.end());
    vector<pair<int, int>> prev_points;
    for (int i = 0; i < points.size(); i++) {
        prev_points.push_back(points[i]);
        long long area = find_max_area(prev_points, points[i], prefSum2D);
        max_area = max(area, max_area);
    }
    printf("%lld\n", max_area);
    return 0;
}