// Q31. Interactive expert system for Disease Classification.
// Educational rule base only: it chooses the disease rule with highest symptom overlap.
#include <bits/stdc++.h>
using namespace std;

string ask(string msg, string def) {
    cout << msg << " [" << def << "]: ";
    string s; getline(cin, s);
    return s.empty() ? def : s;
}

set<string> symptoms(string s) {
    set<string> f; string x; stringstream ss(s);
    while (getline(ss, x, ',')) if (!x.empty()) f.insert(x);
    return f;
}

int main() {
    set<string> patient = symptoms(ask("Patient symptoms", "fever,cough,fatigue"));
    map<string,set<string>> disease = {
        {"Common Cold", {"cough","sneezing","runny_nose"}},
        {"Flu", {"fever","cough","body_pain","fatigue"}},
        {"Migraine", {"headache","nausea","light_sensitivity"}}
    };
    string best; int bestCount = -1;
    for (auto& [name, rule] : disease) {
        string def; for (string s : rule) def += s + ",";
        rule = symptoms(ask("Rule symptoms for " + name, def));
        int match = 0; for (string s : patient) match += rule.count(s);
        if (match > bestCount) bestCount = match, best = name;
    }
    cout << "Likely class: " << best << "\nMatched symptoms: " << bestCount << "\n";
}

