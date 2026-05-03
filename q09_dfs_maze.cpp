// Q09. Interactive DFS for a maze.
// DFS keeps each path on the stack so it can print a route after reaching G.
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

int main() {
    vector<string> def = {"S..#", ".#..", "...G"}, maze;
    int rows = askInt("Number of rows", 3);
    cout << "Enter rows using S, G, #, .\n";
    for (int i = 0; i < rows; i++) {
        cout << "Row " << i + 1 << " [" << (i < 3 ? def[i] : ".") << "]: ";
        string s; getline(cin, s); maze.push_back(s.empty() ? (i < 3 ? def[i] : ".") : s);
    }
    pair<int,int> start = findCell(maze, 'S'), goal = findCell(maze, 'G');
    stack<pair<pair<int,int>, vector<pair<int,int>>>> st; set<pair<int,int>> seen; st.push({start, {start}});
    int dr[] = {1,0,-1,0}, dc[] = {0,1,0,-1};
    while (!st.empty()) {
        auto [cell, path] = st.top(); st.pop();
        auto [r, c] = cell; if (seen.count(cell)) continue; seen.insert(cell);
        if (cell == goal) { for (auto [x, y] : path) cout << "(" << x << ", " << y << ") "; cout << "\n"; return 0; }
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < (int)maze[nr].size() && maze[nr][nc] != '#') { auto p = path; p.push_back({nr,nc}); st.push({{nr,nc}, p}); }
        }
    }
    cout << "No path.\n";
}

