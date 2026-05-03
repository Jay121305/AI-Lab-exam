// Q22. Interactive Cryptarithmetic CSP.
// Each letter is a variable, digits are values, and the equation is the constraint.
#include <bits/stdc++.h>
using namespace std;

string ask(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : s;
}

vector<string> split(string s, char sep) {
    vector<string> out; string part; stringstream ss(s);
    while (getline(ss, part, sep)) if (!part.empty()) out.push_back(part);
    return out;
}

long long value(string word, map<char,int>& assign) {
    long long n = 0;
    for (char ch : word) n = n * 10 + assign[ch];
    return n;
}

bool dfs(int i, vector<char>& letters, set<char>& leading, vector<int>& used, map<char,int>& assign, vector<string>& add, string result) {
    if (i == (int)letters.size()) {
        long long sum = 0; for (string w : add) sum += value(w, assign);
        if (sum == value(result, assign)) {
            for (auto [ch, d] : assign) cout << ch << "=" << d << " ";
            cout << "\n";
            for (int k = 0; k < (int)add.size(); k++) {
                if (k) cout << " + ";
                cout << value(add[k], assign);
            }
            cout << " = " << value(result, assign) << "\n";
            return true;
        }
        return false;
    }
    char ch = letters[i];
    for (int d = 0; d <= 9; d++) if (!used[d] && !(d == 0 && leading.count(ch))) {
        used[d] = 1; assign[ch] = d;
        if (dfs(i + 1, letters, leading, used, assign, add, result)) return true;
        used[d] = 0; assign.erase(ch);
    }
    return false;
}

int main() {
    string eq = ask("Equation like SEND+MORE=MONEY", "SEND+MORE=MONEY");
    eq.erase(remove(eq.begin(), eq.end(), ' '), eq.end());
    transform(eq.begin(), eq.end(), eq.begin(), ::toupper);
    vector<string> sides = split(eq, '='), add = split(sides[0], '+');
    string result = sides[1];
    set<char> all, leading;
    for (string w : add) { for (char ch : w) all.insert(ch); if (w.size() > 1) leading.insert(w[0]); }
    for (char ch : result) all.insert(ch); if (result.size() > 1) leading.insert(result[0]);
    vector<char> letters(all.begin(), all.end());
    if (letters.size() > 10) { cout << "Too many letters for digits.\n"; return 0; }
    vector<int> used(10); map<char,int> assign;
    if (!dfs(0, letters, leading, used, assign, add, result)) cout << "No solution.\n";
}
