// Created Tue Jul 23 1:00 PM 2019
// @Author: Alex-Nicolae Pop

template<class T, bool maximum> // LiChao<tip data, 1 - query max / 0 - query min>
struct LiChao {
  struct Line {
    T a, b;
    Line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {} // check initial values for lines
    T operator()(T x) {
      return a * x + b;
    }
  };
  int n;
  vector<Line> tree;
  vector<T> queries;
  LiChao(vector<T> &queries_) : n(queries_.size()), queries(queries_) {
    int sz = 1;
    while (sz < n) {
      sz <<= 1;
    }
    tree.resize(2 * sz - 1);
  }
  bool Compare(T a, T b) {
    if (maximum) return a > b;
    return a < b;
  }
  void Update(int node, int left, int right, Line nline) {
    int mid = left + (right - left) / 2;
    T lf = queries[left];
    T md = queries[mid];
    bool l = Compare(nline(lf), tree[node](lf));
    bool m  = Compare(nline(md), tree[node](md));
    if (m) {
      swap(tree[node], nline);
    }
    if (left == right) {
      return;
    }
    if (l != m) {
      Update(2 * node + 1, left, mid, nline);
    } else {
      Update(2 * node + 2, mid + 1, right, nline);
    }
  }
  T Best(T a, T b) {
    return Compare(a, b) ? a : b;
  }
  T Query(int node, int left, int right, int pos) {
    T curr = tree[node](queries[pos]);
    if (left == right) {
      return curr;
    }
    int mid = left + (right - left) / 2;
    if (pos <= mid) {
      return Best(curr, Query(2 * node + 1, left, mid, pos));
    } else {
      return Best(curr, Query(2 * node + 2, mid + 1, right, pos));
    }
  }
  void Update(T a, T b) {
    Update(0, 0, n - 1, Line(a, b));
  }
  T Query(T x) {
    int pos = lower_bound(queries.begin(), queries.end(), x) - queries.begin();
    assert(queries[pos] == x);
    return Query(0, 0, n - 1, pos);
  }
};
