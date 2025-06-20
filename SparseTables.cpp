#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<typename T, typename Op>

class SparseTable {
public:
    vector<vector<T>> table;
    vector<T> log;
    Op op;
    
    SparseTable(const vector<T>& arr, Op _op = Op()) : op(_op) {
      int n = arr.size();
      int maxLog = log2(n) + 1;
      table.resize(n, vector<T>(maxLog));
      log.resize(n + 1);
      
      for (int i = 0; i < n; ++i) {
      table[i][0] = arr[i];
      }

      for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
          table[i][j] = op(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
      }

      log[1] = 0;
      for (int i = 2; i <= n; ++i) {
        log[i] = log[i / 2] + 1;
      }
    }

    T query(int L, int R) {
      int j = log[R - L + 1];
      return op(table[L][j], table[R - (1 << j) + 1][j]);
    }
};

struct MinOp {
    using T = ll;

    T operator()(T a, T b) const {
        return min(a, b);
    }

    T id() const {
        return LLONG_MAX;
    }
};

struct MaxOp {
    using T = ll;

    T operator()(T a, T b) const {
        return max(a, b);
    }

    T id() const {
        return INT_MIN;
    }
};
 
void solve() {
  int n;
  cin >> n;
  string x;
  cin >> x;
  vector<ll> v;
  for(int i = 0;i<n;i++){
    v.push_back(x[i]-'0');
  }
  //cout << v[0] << endl;
  SparseTable<ll, MaxOp> st(v);
  cout << st.query(0,n-1) << endl;
  
}
 
int main(){
  ll t;
  cin >> t;
  for(int i = 0;i<t;i++){
    solve();
  }
  return 0;
}
