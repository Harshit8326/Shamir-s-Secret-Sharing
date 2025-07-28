#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

// Function to convert string in given base to decimal
ll baseToDecimal(const string& value, int base) {
    ll result = 0;
    for (char ch : value) {
        ll digit;
        if (isdigit(ch))
            digit = ch - '0';
        else if (isalpha(ch))
            digit = tolower(ch) - 'a' + 10;
        else
            throw invalid_argument("Invalid character in base string");

        if (digit >= base) throw invalid_argument("Digit exceeds base");

        result = result * base + digit;
    }
    return result;
}

// Lagrange interpolation at x = 0
ll lagrangeInterpolation(const vector<pair<ll, ll>>& points) {
    ll result = 0;
    int k = points.size();
    for (int i = 0; i < k; ++i) {
        ll xi = points[i].first;
        ll yi = points[i].second;

        ll num = 1, den = 1;
        for (int j = 0; j < k; ++j) {
            if (i == j) continue;
            num *= -points[j].first;
            den *= (xi - points[j].first);
        }

        result += yi * (num / den);
    }
    return result;
}

// Parse JSON manually
map<ll, pair<int, string>> parseJSON(const string& filename, int& n, int& k) {
    ifstream file(filename);
    string line;
    map<ll, pair<int, string>> data;

    while (getline(file, line)) {
        if (line.find("\"n\"") != string::npos) {
            size_t pos = line.find(":");
            n = stoi(line.substr(pos + 1));
        } else if (line.find("\"k\"") != string::npos) {
            size_t pos = line.find(":");
            k = stoi(line.substr(pos + 1));
        } else if (line.find("\"") != string::npos && isdigit(line[line.find("\"") + 1])) {
            ll x = stoll(line.substr(line.find("\"") + 1));
            getline(file, line); // base line
            int base = stoi(line.substr(line.find(":") + 2));
            getline(file, line); // value line
            size_t start = line.find(":") + 3;
            string value = line.substr(start, line.find("\"", start) - start);
            data[x] = { base, value };
        }
    }

    return data;
}

int main() {
    vector<string> files = {"testcase1.json", "testcase2.json"};

    for (const string& filename : files) {
        int n = 0, k = 0;
        auto rawPoints = parseJSON(filename, n, k);

        vector<pair<ll, ll>> points;
        for (const auto& [x, bv] : rawPoints) {
            int base = bv.first;
            const string& val = bv.second;
            ll y = baseToDecimal(val, base);
            points.push_back({ x, y });
        }

        // Try all combinations of size k
        vector<ll> xlist, ylist;
        for (auto& [x, y] : points) {
            xlist.push_back(x);
            ylist.push_back(y);
        }

        // Only need one combination, since interpolation is deterministic for k points
        vector<pair<ll, ll>> subset;
        for (int i = 0; i < k; ++i) {
            subset.push_back(points[i]);
        }

        ll secret = lagrangeInterpolation(subset);
        cout << "Secret from " << filename << ": " << secret << endl;
    }

    return 0;
}
