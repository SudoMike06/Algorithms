#include <bits/stdc++.h>
using namespace std;
vector<long long> NodoPadre;
set<long long> carreteras;

struct Carretera {
  long long a, b, d, i;
  Carretera(long long a1, long long b1, long long d1, long long i1){
    a = a1;
    b = b1;
    d = d1;
    i = i1;
  }
};

priority_queue<Carretera, vector<Carretera>, function<bool(Carretera, Carretera)>> pq([](const Carretera& c1, const Carretera &c2){
     return c1.d > c2.d;
});


void make_set(long long a){
  NodoPadre[a] = a;
}

long long find_set(long long a){
  if(NodoPadre[a] == a){
    return a;
  }
  else{
    return NodoPadre[a] = find_set(NodoPadre[a]);
  }
}

void union_sets(long long a, long long b){
  a = find_set(a);
  b = find_set(b);
  if(a != b){
    NodoPadre[b] = a;
  }
}

void Kruskal(long long& total){
   
  while(!pq.empty()){
    Carretera actual = pq.top();
    pq.pop();
   
    long long nodo1 = find_set(actual.a);
    long long nodo2 = find_set(actual.b);

    if(nodo1 != nodo2){
      total++;
      union_sets(actual.a, actual.b);
      carreteras.insert(actual.i + 1);
    } 
  }
}



void solve() {
  int n, m;
  cin >> n;
  cin >> m;
  NodoPadre = vector<long long>(n+1);
  long long total = 0;
  for(long long i = 0;i<m;i++){
    long long a, b, d;
    cin >> a;
    cin >> b;
    cin >> d;
    
    make_set(a);
    make_set(b);
    pq.push(Carretera(a, b, d, i));
  }
 
  Kruskal(total);
  cout << total << endl;
  for(long long x : carreteras){
    cout << x << endl;
  }
} 

int main(){
  solve();
  return 0;
}
