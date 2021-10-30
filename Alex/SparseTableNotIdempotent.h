template<class T, class F = function<T(const T&, const T&)>>
struct SparseTable {
  int n;
  vector<vector<T>> st;
  F func;
  
  SparseTable(const vector<T> &v, const F &f) : n(v.size()), func(f) {
    int logn = 32 - __builtin_clz(n);
    st.resize(logn, vector<T>(n));
    st[0] = v;
    
    for (int h = 1; h < logn; ++h) {
      int half = 1 << h, full = 1 << (h + 1);
      for (int i = half; i < n; i += full) {
        st[h][i - 1] = v[i - 1];
        for (int j = i - 2; j >= i - half; --j) {
          st[h][j] = func(v[j], st[h][j + 1]);
        }
        st[h][i] = v[i];
        for (int j = i + 1; j < i + half && j < n; ++j) {
          st[h][j] = func(st[h][j - 1], v[j]);
        }
      }
    }
  }
  
  T Get(int l, int r) const {
    assert(0 <= l && l <= r && r < n);
    if (l == r) return st[0][l];
    int h = 31 - __builtin_clz(l ^ r);
    return func(st[h][l], st[h][r]);
  }
};
