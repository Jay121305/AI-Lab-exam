// Q12. Interactive Depth Limited Search for Water-Jug.
// DLS is DFS with a cutoff; default depth is 3 as required.
#include <bits/stdc++.h>
using namespace std;

int ask(string msg, int def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : stoi(s);
}

vector<pair<int,int>> nextStates(pair<int,int> s, int ca, int cb) {
    auto [a, b] = s; int ab = min(a, cb - b), ba = min(b, ca - a);
    vector<pair<int,int>> v = {{ca,b},{a,cb},{0,b},{a,0},{a-ab,b+ab},{a+ba,b-ba}};
    sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

bool dls(pair<int,int> s, int depth, int ca, int cb, int goal, vector<pair<int,int>>& path) {
    if (s.first == goal || s.second == goal) return true;
    if (depth == 0) return false;
    for (auto n : nextStates(s, ca, cb)) if (find(path.begin(), path.end(), n) == path.end()) {
        path.push_back(n);
        if (dls(n, depth - 1, ca, cb, goal, path)) return true;
        path.pop_back();
    }
    return false;
}

int main() {
    int ca = ask("Capacity of jug A", 4), cb = ask("Capacity of jug B", 3);
    int goal = ask("Required amount", 1), limit = ask("Depth limit", 3);
    vector<pair<int,int>> path = {{0,0}};
    if (!dls({0,0}, limit, ca, cb, goal, path)) { cout << "No path within depth " << limit << ".\n"; return 0; }
    for (auto [a, b] : path) cout << "(" << a << ", " << b << ")\n";
}

