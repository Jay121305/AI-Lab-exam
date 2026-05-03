// Q14. Interactive Depth Limited Search for a maze.
// DLS searches only up to the chosen depth, defaulting to 3.
#include <bits/stdc++.h>
using namespace std;

int askInt(string msg, int def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : stoi(s);
}

pair<int,int> findCell(vector<string>& maze, char ch) {
    for (int r = 0; r < (int)maze.size(); r++) for (int c = 0; c < (int)maze[r].size(); c++) if (maze[r][c] == ch) return {r, c};
    return {-1, -1};
}

bool dls(vector<string>& maze, pair<int,int> cell, pair<int,int> goal, int depth, vector<pair<int,int>>& path) {
    if (cell == goal) return true;
    if (depth == 0) return false;
    int dr[] = {0,1,0,-1}, dc[] = {1,0,-1,0};
    auto [r, c] = cell;
    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        pair<int,int> nxt = {nr, nc};
        if (nr >= 0 && nr < (int)maze.size() && nc >= 0 && nc < (int)maze[nr].size() && maze[nr][nc] != '#' && find(path.begin(), path.end(), nxt) == path.end()) {
            path.push_back(nxt);
            if (dls(maze, nxt, goal, depth - 1, path)) return true;
            path.pop_back();
        }
    }
    return false;
}

int main() {
    vector<string> def = {"S..", ".#G", "..."}, maze;
    int rows = askInt("Number of rows", 3);
    cout << "Enter rows using S, G, #, .\n";
    for (int i = 0; i < rows; i++) {
        cout << "Row " << i + 1 << " [" << (i < 3 ? def[i] : ".") << "]: ";
        string s; getline(cin, s); maze.push_back(s.empty() ? (i < 3 ? def[i] : ".") : s);
    }
    int limit = askInt("Depth limit", 3);
    pair<int,int> start = findCell(maze, 'S'), goal = findCell(maze, 'G');
    vector<pair<int,int>> path = {start};
    if (!dls(maze, start, goal, limit, path)) { cout << "Not found within depth " << limit << ".\n"; return 0; }
    for (auto [r, c] : path) cout << "(" << r << ", " << c << ") ";
    cout << "\n";
}

