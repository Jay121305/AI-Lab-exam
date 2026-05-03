// Q28. Interactive expert system for Skillset-Job matching.
// Jobs are ranked by how many required skills match the candidate's skills.
#include <bits/stdc++.h>
using namespace std;

string ask(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : s;
}

set<string> skillSet(string s) {
    set<string> f; string x; stringstream ss(s);
    while (getline(ss, x, ',')) if (!x.empty()) f.insert(x);
    return f;
}

int main() {
    set<string> candidate = skillSet(ask("Candidate skills", "python,sql,statistics,machine_learning"));
    map<string,set<string>> jobs = {
        {"Data Scientist", {"python","statistics","machine_learning","sql"}},
        {"Web Developer", {"html","css","javascript","python"}},
        {"Cyber Security Analyst", {"networking","linux","security","python"}}
    };
    vector<tuple<double,string,vector<string>,vector<string>>> rank;
    for (auto& [job, req] : jobs) {
        string def; for (string s : req) def += s + ",";
        req = skillSet(ask("Required skills for " + job, def));
        vector<string> matched, missing;
        for (string s : req) (candidate.count(s) ? matched : missing).push_back(s);
        rank.push_back({(double)matched.size() / req.size(), job, matched, missing});
    }
    sort(rank.rbegin(), rank.rend());
    for (auto [score, job, matched, missing] : rank) {
        cout << job << ": " << fixed << setprecision(0) << score * 100 << "% match, matched=";
        for (string s : matched) cout << s << " "; cout << "missing="; for (string s : missing) cout << s << " "; cout << "\n";
    }
}

