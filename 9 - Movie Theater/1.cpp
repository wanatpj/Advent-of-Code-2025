#include<algorithm>
#include<complex>
#include<cstdio>
#include<ranges>
#include<vector>

using namespace std;


long long find_max_area(
    const vector<pair<int, int>>& pareto_frontier,
    const pair<int, int>& corner
) {
    long long max_value = -1;
    for (auto& point : views::reverse(pareto_frontier)) {
        long long dsecond = corner.second - point.second;
        if (dsecond < 0) break;
        long long dfirst = corner.first - point.first;
        max_value = max(max_value, (dfirst + 1) * (long long)(dsecond + 1));
    }
    return max_value;
}

int main(){
    int a, b;
    vector<pair<int, int>> points;
    while(scanf("%d,%d", &a, &b) != EOF) points.push_back(make_pair(a, b));
    long long max_area = -1;
    for (int ii = 0; ii < 2; ii++) {
        sort(points.begin(), points.end());
        vector<pair<int, int>> pareto_frontier;
        for (int i = 0; i < points.size(); i++) {
            if (pareto_frontier.empty() || pareto_frontier.rbegin()->second > points[i].second) {
                pareto_frontier.push_back(points[i]);
            }
            if (i + 1 < points.size() && points[i].first == points[i + 1].first) continue;
            long long area = find_max_area(pareto_frontier, points[i]);
            max_area = max(area, max_area);
        }
        for (auto& point : points) point = make_pair(point.first, -point.second);
    }
    printf("%lld\n", max_area);
    return 0;
}