#include<cstdio>
#include<cstring>
#include<map>
#include<utility>
#include<string>
#include<tuple>

using namespace std;

// Works only because we do not have ^^ (^ next to ^)
map<pair<char, char>, tuple<int, string, int>> state_machine = {
    { {'S', '.'}, {0, "|", 0}},
    { {'|', '^'}, {-1, "|^|", 1}},
    { {'|', '.'}, {0, "|", 0}},
};

int main() {
    char line[2][142];
    int cnt = 0;
    int splits = 0;
    for (int i = 0; i < 142; i++) line[1][i] = '.';
    while(scanf("%s", line[cnt & 1]) != EOF) {
        int length = strlen(line[cnt & 1]);
        for (int i = 0; i < length; i++) {
            auto it = state_machine.find(make_pair(line[(cnt & 1) ^ 1][i],  line[cnt & 1][i]));
            if (it != state_machine.end()) {
                int shift;
                string pattern;
                int reward;
                tie(shift, pattern, reward) = it->second;
                strncpy(line[cnt & 1] + i + shift, pattern.c_str(), pattern.size());
                splits += reward;
            }
        }
        cnt++;
    }
    printf("%d\n", splits);
    return 0;
}