#include<cstdio>
#include<iostream>
#include<set>
#include<string>
#include<utility>

using namespace std;

unsigned long long INF = 1ULL << 63;

int main() {
    set<pair<unsigned long long, unsigned long long> > ranges;
    string line;
    while(std::getline(cin, line) && !line.empty()) {
        unsigned long long a, b;
        sscanf(line.c_str(), "%llu-%llu", &a, &b);
        auto begin_it = ranges.lower_bound(make_pair(a, a));
        auto end_it = ranges.upper_bound(make_pair(b, INF));
        auto end_it_copy = end_it;
        if (begin_it != ranges.begin() && (--begin_it)->second < a) begin_it++;
        auto new_pair = make_pair(
            begin_it == ranges.end() ? a : min(a, begin_it->first),
            end_it == ranges.begin() ? b : max((--end_it_copy)->second, b));
        ranges.erase(begin_it, end_it);
        ranges.insert(new_pair);
    }
    unsigned long long id;
    int cnt = 0;
    while(scanf("%llu", &id) != EOF) {
        auto approx_it = ranges.lower_bound(make_pair(id, id));
        if ((approx_it != ranges.end() && approx_it->first == id) || (approx_it != ranges.begin() && (--approx_it)->second >= id)) {
            cnt++;
        }
    }
    printf("# of fresh: %d\n", cnt);
    unsigned long long total_length = 0;
    for (auto& range : ranges) {
        total_length += range.second - range.first + 1;
    }
    printf("# of fresh within ranges: %llu\n", total_length);
    return 0;
}