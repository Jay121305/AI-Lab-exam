// Q04. Interactive BFS for a maze.
// BFS finds the shortest path because each grid move has equal cost.
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
    queue<pair<int,int>> q; map<pair<int,int>, pair<int,int>> parent;
    q.push(start); parent[start] = {-1, -1};
    int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (make_pair(r, c) == goal) break;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < (int)maze[nr].size() && maze[nr][nc] != '#' && !parent.count({nr,nc}))
                parent[{nr,nc}] = {r,c}, q.push({nr,nc});
        }
    }
    if (!parent.count(goal)) { cout << "No path.\n"; return 0; }
    vector<pair<int,int>> path; for (auto p = goal; p.first != -1; p = parent[p]) path.push_back(p);
    reverse(path.begin(), path.end());
    for (auto [r, c] : path) cout << "(" << r << ", " << c << ") ";
    cout << "\n";
}

