#include<cstdio>
#include<stdexcept>

int main() {
    char lr;
    int rot;
    int pos = 50;
    int cnt = 0;
    while(scanf(" %c%d", &lr, &rot) != EOF) {
        pos = (pos + rot * (lr == 'L' ? -1 : 1) + 100) % 100;
        if (!pos) cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}