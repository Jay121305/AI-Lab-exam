// Q13. Interactive Depth Limited Search for 8-Puzzle.
// The default cutoff is 3; if the board needs more moves, DLS says so.
#include <bits/stdc++.h>
using namespace std;
using State = array<int, 9>;

vector<vector<int>> moves = {{1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7}};

int ask(string msg, int def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : stoi(s);
}

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
    State start = readBoard("Start board", "1 2 3 4 5 6 0 7 8"), goal = readBoard("Goal board", "1 2 3 4 5 6 7 8 0");
    int limit = ask("Depth limit", 3);
    vector<State> path = {start};
    if (!dls(start, goal, limit, path)) { cout << "Not found within depth " << limit << ".\n"; return 0; }
    cout << "Moves: " << path.size() - 1 << "\n";
    for (State s : path) { for (int x : s) cout << x << ' '; cout << "\n"; }
}

