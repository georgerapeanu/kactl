template <class T, class F = function<T(const T&, const T&)>>
struct SparseTable {
  int n;
  F func;
  vector<vector<T>> a;
 
  SparseTable(const vector<T> &v, const F &f) : func(f) {
    n = (int)v.size();
    int max_log = 32 - __builtin_clz(n);
    a.resize(max_log);
    a[0] = v;
    for (int bit = 1; bit < max_log; bit++) {
      a[bit].resize(n - (1 << bit) + 1);
      for (int i = 0; i + (1 << bit) - 1 < n; i++) {
        a[bit][i] = func(a[bit - 1][i], a[bit - 1][i + (1 << (bit - 1))]);
      }
    }
  }
 
  T Get(int l, int r) const {
    assert(0 <= l && l <= r && r < n);
    int lg = 31 - __builtin_clz(r - l + 1);
    return func(a[lg][l], a[lg][r - (1 << lg) + 1]);
  }
};
