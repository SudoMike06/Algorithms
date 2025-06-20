#include <bits/stdc++.h>
using namespace std;

map<long long, bool> primos;
typedef long long ll;

const ll MOD = 1e9 + 7;

bool isPrime(ll n) {
    if (primos.count(n)) return primos[n];
    if (n == 1){
      primos[n] = false;
      return false;
    }
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0){
          primos[n] = false;
          return false;
        }
    }
    primos[n] = true;
    return true;
}

ll modExp(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

template <typename T, typename Op>
class SegTree {
public:
    vector<T> tree, lazy; // Añadir el vector `lazy` para actualizaciones diferidas
    int n;
    Op op;

    SegTree(const vector<T> &v) {
        n = v.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, op.id()); // Inicializamos lazy con el valor neutro de la operación
        build(v, 0, 0, n - 1);
    }

    void build(const vector<T>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;

            build(arr, leftChild, start, mid);
            build(arr, rightChild, mid + 1, end);

            tree[node] = op(tree[leftChild], tree[rightChild]);
        }
    }

    void propagate(int node, int start, int end) {
      if(lazy[node] == op.id()) return;
        // Aplica la operación pendiente al nodo actual
      tree[node] = op(tree[node], lazy[node]);

      if (start != end) { // Si no es un nodo hoja
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;

        // Propaga la actualización a los hijos
        lazy[leftChild] = op(lazy[leftChild], lazy[node]);
        lazy[rightChild] = op(lazy[rightChild], lazy[node]);
      }

    // Limpia la actualización pendiente en el nodo actual
      lazy[node] = op.id();
    }
    void update(int idx, T val) {
      update(0, 0, n - 1, idx, val);
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;

            if (start <= idx && idx <= mid) {
                update(leftChild, start, mid, idx, val);
            } else {
                update(rightChild, mid + 1, end, idx, val);
            }

            tree[node] = op(tree[leftChild], tree[rightChild]);
        }
    }
    void updateRange(int l, int r, T val) {
        updateRange(0, 0, n - 1, l, r, val);
    }

    void updateRange(int node, int start, int end, int l, int r, T val) {
        propagate(node, start, end); // Propagar cualquier actualización pendiente

        if (start > end || start > r || end < l) return; // Fuera del rango

        if (start >= l && end <= r) { // Completamente dentro del rango
            lazy[node] = op(lazy[node],val); // Acumular la actualización en el nodo actual
            propagate(node, start, end); // Aplicar la actualización ahora
            return;
        }

        // Parcialmente dentro del rango
        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;

        updateRange(leftChild, start, mid, l, r, val);
        updateRange(rightChild, mid + 1, end, l, r, val);

        // Actualizar el nodo actual basado en los hijos
        tree[node] = op(tree[leftChild], tree[rightChild]);
    }

    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    T query(int node, int start, int end, int L, int R) {
        propagate(node, start, end); // Propagar cualquier actualización pendiente

        if (R < start || end < L) {
            return op.id(); // Fuera del rango
        }

        if (L <= start && end <= R) { // Completamente dentro del rango
            return tree[node];
        }

        // Parcialmente dentro del rango
        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;

        T leftResult = query(leftChild, start, mid, L, R);
        T rightResult = query(rightChild, mid + 1, end, L, R);

        return op(leftResult, rightResult);
    }
};
struct XorSumOp {
  using T = ll;

  T operator()(T a, T b) const {
    return a ^ b;
  }

  T id() const {
    return 0;
  }
};

struct SumOp {
    using T = ll;

    T operator()(T a, T b) const {
        return a + b;
    }

    T id() const {
        return 0;
    }
};

struct Primos {
    using T = pair<long long, bool>;
    T operator()(T a, T b) const {
        ll numNew = 0;
        if(!a.second || isPrime(a.first)){
          numNew += a.first;
        }
        if(!b.second || isPrime(b.first)){
          numNew += b.first;
        }
        return {numNew, false};
    }

    T id() const {
        return make_pair(0LL, true);
    }
};

struct MinOp {
    using T = ll;

    T operator()(T a, T b) const {
        return min(a, b);
    }

    T id() const {
        return INT_MAX;
    }
};

#define TESTCASES 0

void solve(){
  ll n, q;
  cin >> n >> q;
  vector<ll> v(n*n);
  //cout << n << endl;
  for(int i = 0;i<n;i++){
    string x;
    cin >> x;
    //cout << x << endl;
    for(int j = 0;j<n;j++){
      x[j] == '.' ? v[i+j] = 0 : v[i+j] = 1;
    }
  }
  SegTree<ll, SumOp> tree(v);
  for(int i = 0;i<q;i++){
    ll y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    y1--, x1--, y2--, x2--;
    cout << tree.query((y1+x1),(y2+x2)) << endl;
  } 
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    if (TESTCASES) cin >> t;
    while (t--) solve();
    return 0;
}
