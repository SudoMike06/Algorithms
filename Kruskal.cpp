#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

set<ll> carreteras;

struct Carretera {
  long long a, b, d, i; 
};

//Ordena las Carreteras por distancias ya que buscamos los caminos con menor distancia (condición del problema).
priority_queue<Carretera, vector<Carretera>, function<bool(Carretera, Carretera)>> pq([](const Carretera& c1, const Carretera &c2){
     return c1.d > c2.d;
});

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

//Algorimo Kruskal: buscamos el Arbol de Expansión Mínimo.
void Kruskal(ll& total, vector<ll>& dsu, vector<ll>& size){
  
  //Mientras no se hayan procesado todas las carreteras, no se detiene.
  while(!pq.empty()){
    Carretera actual = pq.top();
    pq.pop();
   
    //Se buscan los padres de cada uno de los extremos de la carretera (nodos).
    ll nodo1 = find_set(dsu, actual.a);
    ll nodo2 = find_set(dsu, actual.b);

    //Si estos no tienen el mismo padre entonces, al total se le suma uno (nº de carreteras) y se unen. Objetivo: Encontrar el mínimo número de carreteras
    //faltantes para que el "grafo" sea conexo y mínimo, es decir, que desde cualquier nodo se pueda llegar cualquier otro acortando la distancia al mínimo.
    if(nodo1 != nodo2){
      total++;
      union_sets(dsu, size, actual.a, actual.b);
      carreteras.insert(actual.i + 1);
    } 
  }
}



void solve() {
  ll n, m;
  cin >> n >> m;

  vector<ll> dsu(n);
  vector<ll> size(n);
  
  for(ll i = 0;i<n;i++){
    make_set(dsu,size,i);
  }

  ll total = 0;
  for(ll i = 0;i<m;i++){
    ll a, b, d;
    cin >> a >> b >> d;
    
    a--, b--; 
    pq.push({a, b, d, i});
  }
 
  Kruskal(total, dsu, size);
  cout << total << endl;
  for(ll x : carreteras){
    cout << x << endl;
  }
} 

int main(){
  solve();
  return 0;
}
