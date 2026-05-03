// Q32. Interactive expert system for Sentiment Analysis.
// Positive words add 1, negative words subtract 1, and the final score gives sentiment.
#include <bits/stdc++.h>
using namespace std;

string ask(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : s;
}

set<string> wordSet(string s) {
    set<string> f; string x; stringstream ss(s);
    while (getline(ss, x, ',')) if (!x.empty()) f.insert(x);
    return f;
}

int main() {
    string text = ask("Enter sentence", "I love this excellent project but the delay was bad");
    set<string> pos = wordSet(ask("Positive words", "good,great,happy,love,excellent,nice"));
    set<string> neg = wordSet(ask("Negative words", "bad,sad,hate,poor,angry,terrible"));
    int score = 0; string w; stringstream ss(text);
    while (ss >> w) {
        for (char& ch : w) ch = tolower(ch);
        w.erase(remove_if(w.begin(), w.end(), ::ispunct), w.end());
        score += pos.count(w); score -= neg.count(w);
    }
    cout << "Sentiment: " << (score > 0 ? "Positive" : score < 0 ? "Negative" : "Neutral") << "\nScore: " << score << "\n";
}

