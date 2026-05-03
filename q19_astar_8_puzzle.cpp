// Q19. Interactive A* Search for 8-Puzzle.
// A* uses f = moves_so_far + Manhattan distance, giving an optimal solution.
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

int inversions(State a) {
    vector<int> v; for (int x : a) if (x) v.push_back(x);
    int inv = 0; for (int i = 0; i < (int)v.size(); i++) for (int j = i + 1; j < (int)v.size(); j++) inv += v[i] > v[j];
    return inv;
}

vector<State> children(State s) {
    int z = find(s.begin(), s.end(), 0) - s.begin(); vector<State> out;
    for (int n : moves[z]) { State t = s; swap(t[z], t[n]); out.push_back(t); }
    return out;
}

int h(State s, State goal) {
    int pos[9]; for (int i = 0; i < 9; i++) pos[goal[i]] = i;
    int sum = 0; for (int i = 0; i < 9; i++) if (s[i]) sum += abs(i / 3 - pos[s[i]] / 3) + abs(i % 3 - pos[s[i]] % 3);
    return sum;
}

int main() {
    State start = readBoard("Start board", "1 2 3 4 0 6 7 5 8"), goal = readBoard("Goal board", "1 2 3 4 5 6 7 8 0");
    if (inversions(start) % 2 != inversions(goal) % 2) { cout << "No solution.\n"; return 0; }
    using Node = tuple<int,int,State,vector<State>>;
    priority_queue<Node, vector<Node>, greater<Node>> pq; map<State,int> best;
    pq.push({h(start, goal), 0, start, {start}}); best[start] = 0;
    while (!pq.empty()) {
        auto [f, g, s, path] = pq.top(); pq.pop();
        if (s == goal) { cout << "Optimal moves: " << path.size() - 1 << "\n"; for (State x : path) { for (int v : x) cout << v << ' '; cout << "\n"; } return 0; }
        for (State n : children(s)) if (!best.count(n) || g + 1 < best[n]) {
            best[n] = g + 1; auto p = path; p.push_back(n); pq.push({g + 1 + h(n, goal), g + 1, n, p});
        }
    }
}

