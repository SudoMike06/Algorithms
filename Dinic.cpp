#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Nodo{
  int nodo;
  ll velocidad; //capacidad.
  int rev; //índice del arco inverso.
};

//Primero hacemos un bfs para calcular los niveles de cada nodo y así facilitar el dfs.
void bfs(vector<vector<Nodo>>& adj, int& source, vector<int>& level){
  queue<Nodo> q;
  q.push({source,LLONG_MAX});

  while(!q.empty()){
    Nodo actual = q.front();
    q.pop();

    
    for(Nodo x : adj[actual.nodo]){
      if(x.velocidad > 0 && level[x.nodo] == -1){
        level[x.nodo] = level[actual.nodo]+1;
        q.push(x);
      }
    }
  }
}
//Para obtener las aristas mínimas para separar el conjunto S (inicio) del conjunto T (final).
//El número mínimo de aristas será igual al flujo máximo.
void getMinCut(vector<vector<Nodo>>& adj, int& source) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;

    //visitamos todos los nodos visitables desde el inicio (capacidad > 0) y luego vemos los adyacentes no visitados de estos nodos.
    while (!q.empty()) {
        int actual = q.front(); 
        q.pop();
        for (Nodo x : adj[actual]) {
            if (x.velocidad > 0 && !visited[x.nodo]) {
                visited[x.nodo] = true;
                q.push(x.nodo);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) continue;
        
        for (Nodo x : adj[i]) {
            if (!visited[x.nodo]) {
                cout << i + 1 << " " << x.nodo + 1 << endl;
            }
        }
    }
}
//Para imprimir las parejas (matching Bipartito) máximas.
void printMatching(const vector<vector<Nodo>>& adj, int& n, int& m) {
    for (int i = 1; i <= n; i++) {
        for (Nodo x : adj[i]) {
            if (x.nodo >= n + 1 && x.nodo <= n + m && x.velocidad == 0) {
                //ajustando los indices.
                cout << i << " " << (x.nodo - n) << endl;
                break;
            }
        }
    }
}

//hacemos un dfs subiendo de nivel hasta llegar a el destino. Se procesa unicamente un camino para encontrar su mínimo,
//sumarlo al total y restarle a las aristas y sumarle a sus inversas del camino.
ll dfs(vector<int>& level, vector<vector<Nodo>>& adj, Nodo actual, int& sink, ll flow, vector<int>& next){ 

  if(actual.nodo == sink) return flow;

  for(int& i = next[actual.nodo];i<adj[actual.nodo].size();i++){
    
    Nodo x = adj[actual.nodo][i];

    if(x.velocidad > 0 && level[x.nodo] == level[actual.nodo] + 1){
      ll pushed = dfs(level, adj, x, sink, min(flow, x.velocidad), next);
      
      if(pushed > 0){

        adj[actual.nodo][i].velocidad -= pushed;
        adj[x.nodo][adj[actual.nodo][i].rev].velocidad += pushed;
        return pushed;

      }
    }
  }
  return 0;
}

void solve(){
  int n, m;
  cin >> n >> m;
  
  //Esto se añade cuando el ejercicio va sobre matching bipartito, creas dos nodos auxiliares (source (S) y sink (T)).
  int source = 0, sink = n-1;
  /*vector<vector<Nodo>> adj(2+n+m);
  sink = 1 + n + m;

  for(int i = 0; i < n; i++) {
    adj[source].push_back({i+1, 1, (int)adj[i+1].size()});
    adj[i+1].push_back({source, 0, (int)adj[source].size() - 1});
  }

  for(int i = 0; i < m; i++) {
    adj[n + 1 + i].push_back({sink, 1, (int)adj[sink].size()});
    adj[sink].push_back({n + 1 + i, 0, (int)adj[n + 1 + i].size() - 1});
  }*/

  vector<vector<Nodo>> adj(n);
  for(int i = 0;i<m;i++){
    int a, b, c;
    cin >> a >> b >> c;
    a--,b--;
    
    //Caso de matching bipartito (se cambia lo de adj por u y v).
    /*int u = a + 1;
    int v = n + b + 1;*/

    adj[a].push_back({b, c, (int) adj[b].size()}); //arista normal.
    adj[b].push_back({a, 0, (int) adj[a].size() - 1}); //arista invertida.
  }
  ll tot = 0;

  //Bucle activo siempre que se pueda llegar al destino.
  while(true){
    
    vector<int> level(adj.size(), -1);
    
    level[source] = 0;

    bfs(adj, source, level);
    if(level[adj.size()-1] == -1) break;
    
    vector<int> next(adj.size());
    //Bucle activo hasta que no se pueda llegar al destino sin actualizar los niveles (pushed == 0).
    //Agregamos al dfs un vector next para no repetir intentos con aristas ya descartadas, el cual se actualiza en el bucle.
    while(ll pushed = dfs(level, adj, {source, LLONG_MAX}, sink, LLONG_MAX, next)){
      tot += pushed;
    }
      
  }
  cout << tot << endl;
}

int main(){
  solve();
  return 0;
}
