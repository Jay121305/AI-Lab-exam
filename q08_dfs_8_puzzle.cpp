// Q08. Interactive DFS for 8-Puzzle.
// DFS may not be shortest, but it shows stack-based state-space search.
#include <bits/stdc++.h>
using namespace std;
using State = array<int, 9>;

vector<vector<int>> moves = {{1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7}};

State readBoard(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s); if (s.empty()) s = def;
    stringstream ss(s); State a{}; for (int i = 0; i < 9; i++) ss >> a[i];
    return a;
}

vector<State> children(State s) {
    int z = find(s.begin(), s.end(), 0) - s.begin(); vector<State> out;
    for (int n : moves[z]) { State t = s; swap(t[z], t[n]); out.push_back(t); }
    return out;
}

int main() {
    State start = readBoard("Start board", "1 2 3 4 5 6 7 0 8"), goal = readBoard("Goal board", "1 2 3 4 5 6 7 8 0");
    stack<pair<State, vector<State>>> st; set<State> seen; st.push({start, {start}});
    while (!st.empty() && seen.size() < 50000) {
        auto [s, path] = st.top(); st.pop();
        if (seen.count(s)) continue;
        seen.insert(s);
        if (s == goal) { cout << "Moves: " << path.size() - 1 << "\n"; for (State x : path) { for (int v : x) cout << v << ' '; cout << "\n"; } return 0; }
        for (State n : children(s)) { auto p = path; p.push_back(n); st.push({n, p}); }
    }
    cout << "Not found within limit.\n";
}

