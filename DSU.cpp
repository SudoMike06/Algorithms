#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<ll> nodoPadre;

void make_set(int v) {
    nodoPadre[v] = v;
}

int find_set(int v) {
    if (v == nodoPadre[v]) return v;
    return find_set(nodoPadre[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) nodoPadre[b] = a;
}
void solve() {
  int n, m;
  cin >> n;
  cin >> m;
  nodoPadre = vector<ll>(n+1);
  set<ll> grupos;
  for(int i = 1;i<m+1;i++){
    ll a, b;
    cin >> a >> b;
    make_set(a);
    make_set(b);
    union_sets(a,b);
  }
  for(int i = 1;i<nodoPadre.size();i++){
    grupos.insert(find_set(nodoPadre[i]));
  }
  grupos.erase(0);
  cout << grupos.size()-1 << endl;
  for(ll x : grupos){
    /*if(x != 1){
      cout << 1 << " " << x << endl;
    }*/
    cout << x << endl;
  } 
  
} 

int main(){
  solve();
  return 0;
}
