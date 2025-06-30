#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

//Crea los conjuntos.
template<typename T>
void make_set(vector<T> &dsu, vector<T> &size, T v) {
  dsu[v] = v;
  size[v] = 1;
}

//Busca el "padre"/conjunto de un nodo.
template<typename T>
int find_set(vector<T> &dsu, T v) {
  if (v == dsu[v]) return v;
  return dsu[v] = find_set(dsu, dsu[v]);
}

//Une dos conjuntos. El que más tamaño tenga será el padre.
template<typename T>
void union_sets(vector<T> &dsu, vector<T> &size, T a, T b) {
  a = find_set(dsu, a);
  b = find_set(dsu, b);
  if (a != b) {
    if (size[a] < size[b]) swap(a, b);
    dsu[b] = a;
    size[a] += size[b];
  }
}

void solve() {
  int n, m;
  cin >> n;
  cin >> m;
  vector<ll> dsu(n);
  vector<ll> size(n);

  //Crea los sets inicialmente siendo el padre el mismo nodo y con tamaño 1.
  for(ll i = 0;i<n;i++){
    make_set(dsu,size,i);
  }
  set<ll> grupos;
  for(int i = 0;i<m;i++){
    ll a, b;
    cin >> a >> b;
    a--,b--;
    union_sets(dsu, size, a, b);
  }
  //guardamos en un set los conjuntos o, lo que es lo mismo, los padres de estos.
  for(int i = 0;i<dsu.size();i++){
    grupos.insert(dsu[i]);
  }
  cout << grupos.size()-1 << endl;
  for(ll x : grupos){ 
    cout << x << endl;
  } 
  
} 

int main(){
  solve();
  return 0;
}
