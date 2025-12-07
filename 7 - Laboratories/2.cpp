#include<algorithm>
#include<cstdio>
#include<iostream>
#include<numeric>
#include<ranges>
#include<string>
#include<vector>

using namespace std;

// works because no ^ on the edges

int main(){
    string line;
    vector<unsigned long long> timelines(142, 0), prev_timelines(142, 0);
    while(cin >> line) {
        for(auto [i, c] : views::enumerate(line)) {
            if (c == 'S') timelines[i] = 1;
            else if (c == '^') {
                timelines[i - 1] += prev_timelines[i];
                timelines[i + 1] += prev_timelines[i];
            } else {
                timelines[i] += prev_timelines[i];
            }
        }
        prev_timelines.swap(timelines);
        timelines = vector<unsigned long long>(142, 0);
    }
    unsigned long long result = reduce(prev_timelines.begin(), prev_timelines.end());
    printf("%llu\n", result);
    return 0;
}