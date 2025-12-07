#include<algorithm>
#include<cstdio>
#include<cstring>

using namespace std;

char bank[101];

int main() {
    long total_sum = 0;
    while(scanf("%s", bank) != EOF) {
        int len = strlen(bank);
        int maxidx = max_element(bank, bank + len) - bank;
        if (maxidx < len - 1) {
            total_sum += (bank[maxidx] - '0') * 10 + *max_element(bank + maxidx + 1, bank + len) - '0';
        } else {
            total_sum += (*max_element(bank, bank + len - 1) - '0') * 10 + bank[maxidx] - '0';
        }
    }
    printf("%ld\n", total_sum);
    return 0;
}