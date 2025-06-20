#include <bits/stdc++.h>
using namespace std;

struct Nodo{
  int nodo, vecinos;
};

typedef long long ll;
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
    vector<vector<int>> v(n);
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
        v[house].push_back(a);
        inverse[a].push_back(house);
      }
    }
    int res = 1;
    vector<bool> visited1(n);

    vector<bool> visited2(n);

    vector<int> Recorrido;
    //Primero haces un dfs normal guardando el recorrido.
    for(int i = 0;i<n;i++){
      if(!visited1[i]){
        visited1[i] = true;
        dfs(v, i, visited1, Recorrido);
        //visited1[i] = true;
      }
      
    }

    //Luego inviertes el recorrido para empezar por el último.
    reverse(Recorrido.begin(), Recorrido.end());

    //Por último, haces un dfs en orden del Recorrido inverso, guardando en cada dfs el grupo ciclico cerrado que forman.
    for(int i : Recorrido){
      vector<int> aux;

      if(!visited2[i]){
        visited2[i] = true;
        dfs(inverse, i, visited2, aux);
        res = max(res,(int) aux.size());
        //visited2[i] = true;
      }
    }
    cout << res << endl;
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
