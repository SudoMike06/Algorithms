#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Nodo{
  int nodo, vecinos;
};

//Dfs recursivo que guarda el recorrido.
void dfs(vector<vector<int>>& adj, int ini, vector<bool>& visited, vector<int>& res){
  for(int neighbour : adj[ini]){
    if(visited[neighbour]) continue;
    visited[neighbour] = true;
    dfs(adj, neighbour, visited, res);
  }
  
  res.push_back(ini);
}



void solve() {
  int n;
  while(cin >> n){
    //Guardamos las carreteras y sus inversas.
    vector<vector<int>> aristas(n);
    vector<vector<int>> inverse(n);

    int house, carreteras;
    while(cin >> house){

      if(house == 0) break;
      house--;

      cin >> carreteras;
      for(int i = 0;i<carreteras;i++){
        int a;
        cin >> a;
        a--;
        aristas[house].push_back(a);
        inverse[a].push_back(house);
      }
    }

    int resultado = 1;
    vector<bool> visited1(n);

    vector<bool> visited2(n);

    vector<int> Recorrido;
    
    //Primero haces un dfs normal, desde todos los nodos, guardando el recorrido.
    for(int i = 0;i<n;i++){
      if(!visited1[i]){
        visited1[i] = true;
        dfs(aristas, i, visited1, Recorrido);
      }
      
    }

    //Luego inviertes el recorrido para empezar por el último.
    reverse(Recorrido.begin(), Recorrido.end());

    //Por último, haces un dfs en orden del Recorrido inverso, guardando en cada dfs el grupo ciclico cerrado que forman.
    for(int i : Recorrido){
      vector<int> aux;

      if(!visited2[i]){
        visited2[i] = true;
        //En el dfs, hacemos uso de las aristas inversas.
        dfs(inverse, i, visited2, aux);
        resultado = max(resultado, (int) aux.size());
      }
    }
    //El objetivo es encontrar el grupo ciclico cerrado más grande, es decir, la Componente Fuertemente Conexa con más elementos del grafo.
    cout << resultado << endl;
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
