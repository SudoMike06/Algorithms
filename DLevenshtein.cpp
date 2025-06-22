#include <bits/stdc++.h>
using namespace std;

//Calcula la distancia mínima para pasar de un string a otro (Recursivamente).
long long Levenshtein(const string &x, const string &y, int i, int j, vector<vector<long long>> &dp) {
    //Si i o j están vacios, se necesitan j y i inserciones (respectivamente). Caso base.
    if (i == 0) return j;
    if (j == 0) return i;

    //Si ya está calculado lo devolvemos (Memoización).
    if (dp[i][j] != -1) return dp[i][j];
    
    //Si coinciden no hacemos nada.
    if (x[i - 1] == y[j - 1]) dp[i][j] = Levenshtein(x, y, i - 1, j - 1, dp);

    //Si no coindiciden la distancia será la mínima distancia entre el remplazo, la inserción o la eliminación (respectivamente), más uno.
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
    t = 1;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}












