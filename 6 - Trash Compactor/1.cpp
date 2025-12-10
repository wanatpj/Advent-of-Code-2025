#include<cstdlib>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

int main(){
    vector<vector<short>> parsed;
    string line;
    long long total = 0;
    while(getline(cin, line) && !line.empty()) {
        int idx = 0;
        stringstream ss(line);
        string raw_number;
        vector<short> new_row;
        while(ss >> raw_number) {
            if (raw_number[0] == '+') {
                for (auto& row : parsed) {
                    total += row[idx];
                }
            } else if (raw_number[0] == '*') {
                long long chunk = 1;
                for (auto& row : parsed) chunk *= row[idx];
                total += chunk;
            } else {
                new_row.push_back(atoi(raw_number.c_str()));
            }
            idx++;
        }
        parsed.push_back(std::move(new_row));
    }
    cout << total << endl;
    return 0;
}
