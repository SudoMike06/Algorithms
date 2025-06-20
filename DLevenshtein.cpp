#include <bits/stdc++.h>
using namespace std;

long long Levenshtein(const string &x, const string &y, int i, int j, vector<vector<long long>> &dp) {
    if (i == 0) return j;
    if (j == 0) return i;
    if (dp[i][j] != -1) return dp[i][j];

    if (x[i - 1] == y[j - 1]) dp[i][j] = Levenshtein(x, y, i - 1, j - 1, dp);
    else dp[i][j] = 1 + min({Levenshtein(x, y, i - 1, j - 1, dp), Levenshtein(x, y, i, j - 1, dp), Levenshtein(x, y, i - 1, j, dp)});   
    
    return dp[i][j];
}

void solve() {
    string x, y;
    cin >> x >> y;
    vector<vector<long long>> dp(x.length() + 1, vector<long long>(y.length() + 1, -1));
    cout << Levenshtein(x, y, x.length(), y.length(), dp) << endl;
}

int main() {
    long long t;
    //cin >> t;
    t = 1;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}












