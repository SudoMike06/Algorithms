#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Bridge {
  ll u, v, c;
};

void solve(){
  ll n, m;
  cin >> n >> m;
  vector<ll> dist(n, LLONG_MIN);
  vector<Bridge> aristas;
  for(int i = 0;i<m;i++){
    ll a, b, x;
    cin >> a >> b >> x;
    a--, b--;
    aristas.push_back({a,b,x});
  }
  dist[0] = 0;
  for(int i = 0;i<n-1;i++){
    for(auto [u,v,c] : aristas){
      if(dist[u] != LLONG_MIN && dist[u] + c > dist[v]){
        dist[v] = dist[u] + c;
      }
    }
  }
  vector<bool> ciclo(n,false);
  for(auto [u,v,c] : aristas){
    if(dist[u] != LLONG_MIN && dist[u] + c > dist[v]){
      ciclo[v] = true;
    }
  }
  for(int i = 0;i<n;i++){
    if(ciclo[i]){
      for(auto [u, v, c] : aristas){
        if(ciclo[u]) ciclo[v] = true;
      }
    }
  }
  ciclo[n-1] ? cout << -1 : cout << dist[n-1];
  cout << endl;
}
int main(){
  long long t;
  //cin >> t;
  t = 1;
  for(int i = 0;i<t;i++){
    solve();
  } 
   
}
