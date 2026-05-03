// Q15. Interactive DLS for Missionaries and Cannibals.
// Classic 3M-3C with boat 2 needs more than depth 3, so the cutoff may fail.
#include <bits/stdc++.h>
using namespace std;
using State = tuple<int,int,char>;

int totalPeople, boatCap;

int ask(string msg, int def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : stoi(s);
}

bool safe(int m, int c) {
    int rm = totalPeople - m, rc = totalPeople - c;
    return m >= 0 && c >= 0 && m <= totalPeople && c <= totalPeople && (m == 0 || m >= c) && (rm == 0 || rm >= rc);
}

vector<State> children(State s) {
    auto [m, c, side] = s; vector<State> out;
    for (int dm = 0; dm <= boatCap; dm++) for (int dc = 0; dc <= boatCap; dc++) if (dm + dc >= 1 && dm + dc <= boatCap) {
        int nm = side == 'L' ? m - dm : m + dm, nc = side == 'L' ? c - dc : c + dc;
        if (safe(nm, nc)) out.push_back({nm, nc, side == 'L' ? 'R' : 'L'});
    }
    return out;
}

bool dls(State s, State goal, int depth, vector<State>& path) {
    if (s == goal) return true;
    if (depth == 0) return false;
    for (State n : children(s)) if (find(path.begin(), path.end(), n) == path.end()) {
        path.push_back(n);
        if (dls(n, goal, depth - 1, path)) return true;
        path.pop_back();
    }
    return false;
}

int main() {
    totalPeople = ask("Number of missionaries and cannibals", 3);
    boatCap = ask("Boat capacity", 2);
    int limit = ask("Depth limit", 3);
    State start = {totalPeople, totalPeople, 'L'}, goal = {0, 0, 'R'};
    vector<State> path = {start};
    if (!dls(start, goal, limit, path)) { cout << "No complete solution within depth " << limit << ".\n"; return 0; }
    for (auto [m, c, side] : path) cout << "(" << m << ", " << c << ", " << side << ")\n";
}

