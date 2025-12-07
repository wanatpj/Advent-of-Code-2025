#include<cmath>
#include<cstdio>

int main() {
    char lr;
    int rot;
    int pos = 50;
    int cnt = 0;
    while(scanf(" %c%d", &lr, &rot) != EOF) {
        int reversed = (lr == 'L' ? -1 : 1);
        int rotation = rot * reversed;
        int excl_begin = pos * reversed,
            end = (pos + rotation) * reversed;
        int shift = 100 * (abs(excl_begin) / 100 + 1);
        cnt += (end + shift) / 100 - (excl_begin + shift) / 100;
        pos = (pos + rotation + 100) % 100;
    }
    printf("%d\n", cnt);
    return 0;
}