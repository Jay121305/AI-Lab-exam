// Q01. Interactive Tic-Tac-Toe: user plays X, AI plays O.
// Minimax checks all future legal moves so O chooses the safest/best move.
#include <bits/stdc++.h>
using namespace std;

vector<array<int, 3>> winLines = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

char winner(vector<char>& b) {
    for (auto l : winLines) if (b[l[0]] != ' ' && b[l[0]] == b[l[1]] && b[l[1]] == b[l[2]]) return b[l[0]];
    return count(b.begin(), b.end(), ' ') ? ' ' : 'D'; // D means draw.
}

int minimax(vector<char>& b, char turn) {
    char w = winner(b);
    if (w != ' ') return w == 'O' ? 1 : (w == 'X' ? -1 : 0);
    vector<int> scores;
    for (int i = 0; i < 9; i++) if (b[i] == ' ') {
        b[i] = turn;
        scores.push_back(minimax(b, turn == 'O' ? 'X' : 'O'));
        b[i] = ' ';
    }
    return turn == 'O' ? *max_element(scores.begin(), scores.end()) : *min_element(scores.begin(), scores.end());
}

int bestMove(vector<char>& b) {
    int best = -2, pos = -1;
    for (int i = 0; i < 9; i++) if (b[i] == ' ') {
        b[i] = 'O';
        int score = minimax(b, 'X');
        b[i] = ' ';
        if (score > best) best = score, pos = i;
    }
    return pos;
}

void show(vector<char>& b) {
    for (int i = 0; i < 9; i++) {
        cout << (b[i] == ' ' ? char('1' + i) : b[i]) << (i % 3 == 2 ? "\n" : " | ");
    }
}

int main() {
    vector<char> board(9, ' ');
    cout << "You are X. Enter positions 1 to 9.\n";
    while (winner(board) == ' ') {
        show(board);
        cout << "Your move: ";
        int move;
        if (!(cin >> move)) return 0;
        move--;
        if (move < 0 || move >= 9 || board[move] != ' ') { cout << "Invalid move.\n"; continue; }
        board[move] = 'X';
        if (winner(board) == ' ') board[bestMove(board)] = 'O';
    }
    show(board);
    char w = winner(board);
    cout << "Result: " << (w == 'D' ? "Draw" : string(1, w)) << "\n";
}

