#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <set>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}

ll computeValue(string op, ll a, ll b) {
    if (op == "sum") return a + b;
    if (op == "multiply") return a * b;
    if (op == "gcd") return gcd(a, b);
    throw invalid_argument("Unsupported operation");
}

// Lagrange Interpolation at x = 0
ll lagrangeInterpolation(vector<pair<ll, ll>> &points) {
    ll result = 0;
    int k = points.size();
    for (int i = 0; i < k; ++i) {
        ll xi = points[i].first;
        ll yi = points[i].second;

        ll num = 1, den = 1;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                num *= -points[j].first;
                den *= (xi - points[j].first);
            }
        }
        result += yi * (num / den);
    }
    return result;
}

// Generate all combinations of size k
void generateCombinations(vector<pair<ll, ll>>& input, int k,
                          vector<vector<pair<ll, ll>>>& result,
                          int start = 0, vector<pair<ll, ll>> temp = {}) {
    if (temp.size() == k) {
        result.push_back(temp);
        return;
    }
    for (int i = start; i < input.size(); ++i) {
        temp.push_back(input[i]);
        generateCombinations(input, k, result, i + 1, temp);
        temp.pop_back();
    }
}

// Very basic JSON parser (specific to this input structure)
map<ll, pair<string, pair<ll, ll>>> parseJSON() {
    string json = R"({
        "n": 5,
        "k": 3,
        "shares": {
            "1": { "op": "sum", "a": 1000000000000000000, "b": 29 },
            "2": { "op": "multiply", "a": 7, "b": 900000000000000003 },
            "3": { "op": "gcd", "a": 391, "b": 17 },
            "4": { "op": "sum", "a": 2, "b": 3 },
            "5": { "op": "multiply", "a": 9, "b": 6 }
        }
    })";

    map<ll, pair<string, pair<ll, ll>>> shares;
    istringstream ss(json);
    string line;
    while (getline(ss, line)) {
        size_t quotePos = line.find("\"");
        if (quotePos != string::npos && isdigit(line[quotePos + 1])) {
            ll key = line[quotePos + 1] - '0';
            getline(ss, line); size_t opPos = line.find(":");
            string op = line.substr(opPos + 3); op.pop_back(); op.pop_back();

            getline(ss, line); opPos = line.find(":");
            ll a = stoll(line.substr(opPos + 2));

            getline(ss, line); opPos = line.find(":");
            ll b = stoll(line.substr(opPos + 2));

            shares[key] = { op, {a, b} };
        }
    }
    return shares;
}

int main() {
    auto parsed = parseJSON();

    vector<pair<ll, ll>> evaluated;
    for (auto& [id, val] : parsed) {
        string op = val.first;
        ll a = val.second.first;
        ll b = val.second.second;
        ll res = computeValue(op, a, b);
        evaluated.push_back({ id, res });
    }

    int n = evaluated.size();
    int k = 3; // From JSON; adjust if parsing dynamically

    vector<vector<pair<ll, ll>>> combos;
    generateCombinations(evaluated, k, combos);

    map<ll, int> secretFreq;
    for (auto& combo : combos) {
        try {
            ll secret = lagrangeInterpolation(combo);
            secretFreq[secret]++;
        } catch (...) {
            continue;
        }
    }

    // Find the most common secret
    ll finalSecret = -1;
    int maxFreq = 0;
    for (auto& [secret, freq] : secretFreq) {
        if (freq > maxFreq) {
            maxFreq = freq;
            finalSecret = secret;
        }
    }

    cout << "The secret is: " << finalSecret << endl;
    return 0;
}

