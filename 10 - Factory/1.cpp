#include<algorithm>
#include<iostream>
#include<ranges>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

int light_mask(const string& lights) {
    int total = 0;
    for (int i = 0; i < lights.size(); i++) {
        if (lights[i] == '#') total |= 1 << i;
    }
    return total;
}

int find_minimum_presses(int light_mask, const vector<int>& button_masks) {
    int mini = button_masks.size() + 1;
    for (int i = 0; i < (1 << button_masks.size()); i++) {
        int mask = 0;
        int cnt = 0;
        for (int j = 0; j < button_masks.size(); j++) {
            if (i & (1 << j)) {
                mask ^= button_masks[j];
                cnt++;
            }
        }
        if (mask == light_mask) {
            mini = min(mini, cnt);
        }
    }
    if (mini == button_masks.size() + 1) throw runtime_error("fail");
    return mini;
}

int main() {
    string line;
    int total = 0;
    while(getline(cin, line) && !line.empty()) {
        string lights, raw_button;
        vector<int> buttons;
        stringstream ss(line);
        ss >> lights;
        lights = lights.substr(1, lights.size() - 2);
        while (ss >> raw_button && raw_button[0] == '(') {
            int button_mask = 0;
            for (auto&& [index, rng] : views::enumerate(views::split(
                raw_button.substr(1, raw_button.size() - 2), ','))
            ) {
                button_mask |= 1 << stoi(string(rng.begin(), rng.end()));
            }
            buttons.push_back(button_mask);
        }
        total += find_minimum_presses(light_mask(lights), buttons);
    }
    cout << total << endl;
    return 0;
}