// Q03. Interactive BFS for 8-Puzzle.
// Each board arrangement is a state; BFS gives the fewest blank-tile moves.
#include <bits/stdc++.h>
using namespace std;
using State = array<int, 9>;

vector<vector<int>> moves = {{1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7}};

State readBoard(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s); if (s.empty()) s = def;
    stringstream ss(s); State a{};
    for (int i = 0; i < 9; i++) ss >> a[i];
    return a;
}

int inversions(State a) {
    vector<int> v; for (int x : a) if (x) v.push_back(x);
    int inv = 0; for (int i = 0; i < (int)v.size(); i++) for (int j = i + 1; j < (int)v.size(); j++) inv += v[i] > v[j];
    return inv;
}

vector<State> children(State s) {
    int z = find(s.begin(), s.end(), 0) - s.begin();
    vector<State> out;
    for (int n : moves[z]) { State t = s; swap(t[z], t[n]); out.push_back(t); }
    return out;
}

void print(State s) { for (int x : s) cout << x << ' '; cout << "\n"; }

int main() {
    State start = readBoard("Start board", "1 2 3 4 0 6 7 5 8");
    State goal = readBoard("Goal board", "1 2 3 4 5 6 7 8 0");
    if (inversions(start) % 2 != inversions(goal) % 2) { cout << "No solution.\n"; return 0; }
    queue<State> q; map<State, State> parent; State none; none.fill(-1);
    q.push(start); parent[start] = none;
    while (!q.empty()) {
        State s = q.front(); q.pop();
        if (s == goal) break;
        for (State n : children(s)) if (!parent.count(n)) parent[n] = s, q.push(n);
    }
    if (!parent.count(goal)) { cout << "No solution.\n"; return 0; }
    vector<State> path; for (State s = goal; s != none; s = parent[s]) path.push_back(s);
    reverse(path.begin(), path.end());
    cout << "Moves: " << path.size() - 1 << "\n";
    for (State s : path) print(s);
}

