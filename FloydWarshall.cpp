#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<long long> prefixSum(vector<long long> v){
  vector<long long> Prefix = v;
  for(int i = 1;i<v.size();i++){
    Prefix[i] = Prefix[i] + Prefix[i-1];
  }
  return Prefix;
}


void solve(){
  ll n, m, q;
  cin >> n >> m >> q;
  vector<vector<ll>> v(n, vector<ll>(n, LLONG_MAX));
  for(int i = 0;i<m;i++){
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    v[a][b] = min(v[a][b],c);
    v[b][a] = min(v[b][a],c);
  }
  for(int j = 0;j<n;j++){
    v[j][j] = 0;
  }
  for(int k = 0;k<n;k++){
    for(int i = 0;i<n;i++){
      for(int j = 0;j<n;j++){
        if(v[i][k] != LLONG_MAX && v[k][j] != LLONG_MAX){
          v[i][j] = min(v[i][j], v[i][k] + v[k][j]);
        }
      }
    }
  }
  for(int i = 0;i<q;i++){
    ll u, p;
    cin >> u >> p;
    u--, p--;
    v[u][p] == LLONG_MAX ? cout << -1 : cout << v[u][p];
    cout << endl;
  }
}
 
 
int main(){
  int t;
  t = 1;
  for(int i = 0;i<t;i++){
    solve();
  }
  return 0;
}  
