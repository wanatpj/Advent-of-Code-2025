#include<cstdio>
#include<iostream>
#include<optional>
#include<string>
#include<vector>

using namespace std;

class Solver {
public:
    virtual optional<bool> solve(int w, int h, int a[6]) = 0;
};

class BruteSolver : public Solver {
    optional<bool> solve(int w, int h, int a[6]) override {
        if ((w/3) * (h/3) >= a[0] + a[1] + a[2] + a[3] + a[4] + a[5]) return true;
        return {};
    }
};

class CountInfeasibilitySolver : public Solver {
    vector<int> counts = {7, 6, 7, 7, 7, 5};

    optional<bool> solve(int w, int h, int a[6]) override {
        int count_min = 0;
        for (int i = 0; i < 6; i++) count_min += counts[i] * a[i];
        if (w*h < count_min) return false;
        return {};
    }
};

vector<Solver*> solvers = {new BruteSolver(), new CountInfeasibilitySolver()};

int main() {
    int total = 0;
    int unknown = 0;
    string line;
    for (int i = 0; i < 30; i++) getline(cin, line);
    while(getline(cin, line)) {
        int w, h;
        int a[6];
        sscanf(line.c_str(), "%dx%d:%d%d%d%d%d%d", &w, &h, a, a+1, a+2, a+3, a+4, a+5);
        optional<bool> solution = {};
        for (Solver* solver : solvers) {
            solution = solver->solve(w, h, a);
            if (solution.has_value()) break;
        }
        if (solution.has_value()) total += solution.value();
        else unknown++;
    }
    cout << "total solved: " << total << ", unknown: " << unknown << endl;
    return 0;
}