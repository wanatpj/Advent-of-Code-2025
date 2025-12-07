#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

long long INF = (1LL << 32);


long long find_max_joltage(char* bank, int len) {
    vector<vector<long long>> max_joltage(12, vector<long long>(len + 1));
    max_joltage[0][0] = -INF;
     for (int j = 1; j <= len; j++) {
        max_joltage[0][j] = max(max_joltage[0][j-1], (long long)bank[j-1]);
    }
    for (int i = 1; i < 12; i++) {
        max_joltage[i][0] = -INF;
        for (int j = 1; j <= len; j++) {
            max_joltage[i][j] = max(max_joltage[i][j-1], bank[j-1] + 10*max_joltage[i-1][j-1]);
        }
    }
    return max_joltage[11][len];
}

int main() {
    char bank[101];
    long long total_sum = 0;
    while(scanf("%s", bank) != EOF) {
        int len = strlen(bank);
        transform(bank, bank + len, bank, [](char c) { return c - '0';});
        total_sum += find_max_joltage(bank, len);
    }
    printf("%lld\n", total_sum);
    return 0;
}