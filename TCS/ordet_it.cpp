#include <bits/stdc++.h>
using namespace std;

int encode(const vector<int> &perm, const vector<int> &fact) {
    int n = perm.size();
    int code = 0;
    vector<bool> used(n, false);
    for (int i = 0; i < n; ++i) {
        int smaller = 0;
        for (int v = 0; v < perm[i]; ++v)
            if (!used[v]) smaller++;
        used[perm[i]] = true;
        code += smaller * fact[n - 1 - i];
    }
    return code;
}

int expand(queue<vector<int>> &q,
           vector<int> &distThis,
           vector<int> &distOther,
           const vector<int> &fact,
           int n)
{
    int size = q.size();
    while (size--) {
        vector<int> cur = q.front();
        q.pop();
        int curDepth = distThis[encode(cur, fact)];

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int len = j - i + 1;

                vector<int> remain;
                remain.reserve(n - len);
                for (int k = 0; k < n; k++) {
                    if (k < i || k > j) remain.push_back(cur[k]);
                }

                for (int k = 0; k <= (int)remain.size(); k++) {
                    if (k == i) continue; // no change
                    vector<int> next;
                    next.reserve(n);

                    // prefix
                    for (int t = 0; t < k; t++) next.push_back(remain[t]);
                    // moved segment
                    for (int t = i; t <= j; t++) next.push_back(cur[t]);
                    // suffix
                    for (int t = k; t < (int)remain.size(); t++) next.push_back(remain[t]);

                    int code = encode(next, fact);
                    if (distThis[code] != -1) continue;

                    distThis[code] = curDepth + 1;
                    if (distOther[code] != -1) {
                        return distThis[code] + distOther[code];
                    }
                    q.push(next);
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = -1;
    string line;

    // --- Read n ---
    while (getline(cin, line)) {
        if (line.empty()) continue;
        try {
            n = stoi(line);
            break;
        } catch (...) {
            continue;
        }
    }
    if (n <= 0) return 0;

    // Read until "shuffled"
    while (getline(cin, line)) {
        string t = line;
        transform(t.begin(), t.end(), t.begin(), ::tolower);
        if (t == "shuffled") break;
    }

    vector<string> shuffled;
    while ((int)shuffled.size() < n && getline(cin, line)) {
        if (!line.empty()) shuffled.push_back(line);
    }

    // Read until "original"
    while (getline(cin, line)) {
        string t = line;
        transform(t.begin(), t.end(), t.begin(), ::tolower);
        if (t == "original") break;
    }

    vector<string> original;
    while ((int)original.size() < n && getline(cin, line)) {
        if (!line.empty()) original.push_back(line);
    }

    unordered_map<string, int> indexMap;
    for (int i = 0; i < n; i++) indexMap[original[i]] = i;

    vector<int> start(n);
    for (int i = 0; i < n; i++) {
        string key = shuffled[i];
        if (!indexMap.count(key)) {
            for (auto &p : indexMap)
                if (strcasecmp(p.first.c_str(), key.c_str()) == 0)
                    key = p.first;
        }
        start[i] = indexMap[key];
    }

    vector<int> target(n);
    iota(target.begin(), target.end(), 0);

    if (start == target) {
        cout << 0;
        return 0;
    }

    vector<int> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    int totalStates = fact[n];

    vector<int> distA(totalStates, -1), distB(totalStates, -1);

    int startCode = encode(start, fact);
    int targetCode = encode(target, fact);
    distA[startCode] = 0;
    distB[targetCode] = 0;

    queue<vector<int>> qa, qb;
    qa.push(start);
    qb.push(target);

    while (!qa.empty() && !qb.empty()) {
        if (qa.size() <= qb.size()) {
            int res = expand(qa, distA, distB, fact, n);
            if (res != -1) {
                cout << res;
                return 0;
            }
        } else {
            int res = expand(qb, distB, distA, fact, n);
            if (res != -1) {
                cout << res;
                return 0;
            }
        }
    }

    cout << -1;
    return 0;
}
