// Q05. Interactive BFS for Missionaries and Cannibals.
// State is (missionaries_left, cannibals_left, boat_side); BFS gives shortest safe crossings.
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
    auto [m, c, side] = s;
    vector<State> out;
    for (int dm = 0; dm <= boatCap; dm++) for (int dc = 0; dc <= boatCap; dc++) if (dm + dc >= 1 && dm + dc <= boatCap) {
        int nm = side == 'L' ? m - dm : m + dm, nc = side == 'L' ? c - dc : c + dc;
        if (safe(nm, nc)) out.push_back({nm, nc, side == 'L' ? 'R' : 'L'});
    }
    return out;
}

int main() {
    totalPeople = ask("Number of missionaries and cannibals", 3);
    boatCap = ask("Boat capacity", 2);
    State start = {totalPeople, totalPeople, 'L'}, goal = {0, 0, 'R'};
    queue<State> q; map<State, State> parent; State none = {-1, -1, 'X'};
    q.push(start); parent[start] = none;
    while (!q.empty()) {
        State s = q.front(); q.pop();
        if (s == goal) break;
        for (State n : children(s)) if (!parent.count(n)) parent[n] = s, q.push(n);
    }
    if (!parent.count(goal)) { cout << "No solution.\n"; return 0; }
    vector<State> path; for (State s = goal; s != none; s = parent[s]) path.push_back(s);
    reverse(path.begin(), path.end());
    for (auto [m, c, side] : path) cout << "(" << m << ", " << c << ", " << side << ")\n";
}

