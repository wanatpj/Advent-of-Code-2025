#include<iostream>
#include<optional>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

optional<short> vertical_line(const vector<string>& lines, int i) {
    short s = 0;
    bool any = false;
    for (int r = 0; r < lines.size() - 1; r++) {
        if (i < lines[r].size() && '0' <= lines[r][i] && lines[r][i] <= '9') {
            s *= 10;
            s += lines[r][i] - '0';
            any = true;
        }
    }
    if (!any) return {};
    return s;
}

int main(){
    vector<string> lines;
    string line;
    long long total = 0;
    while(getline(cin, line) && !line.empty()) lines.push_back(line);
    for(int i = 0; i < lines.rbegin()->size(); i++) {
        char op = lines.rbegin()->at(i);
        optional<short> number;
        long long chunk = 1;
        while(number = vertical_line(lines, i)) {
            if (op == '+') total += number.value();
            else if (op == '*') chunk *= number.value();
            i++;
        }
        if (op == '*') total += chunk;
    }
    cout << total << endl;
    return 0;
}