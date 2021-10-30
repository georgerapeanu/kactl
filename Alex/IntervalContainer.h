template<class T>
struct IntervalContainer {
  map<T, T> s;
  using iterator = typename map<T, T>::iterator;
  
  iterator emplace(T l, T r) {
    if (l == r) return end();
    auto it = s.lower_bound(l);
    while (it != end() && it->first <= r) {
      r = max(r, it->second);
      it = s.erase(it);
    }
    while (it != begin() && (--it)->second >= l) {
      l = min(l, it->first);
      r = max(r, it->second);
      it = s.erase(it);
    }
    return s.emplace(l, r).first;
  }
  
  void erase(T l, T r) {
    if (l == r) return;
    auto it = emplace(l, r);
    T L = it->first, R = it->second;
    s.erase(it);
    if (L != l) emplace(L, l);
    if (r != R) emplace(r, R);
  }
  
  iterator find(T x) {
    auto it = s.upper_bound(x);
    if (it == begin() || (--it)->second <= x)
      return end();
    return it;
  }
  
  iterator begin() { return s.begin(); }
  iterator end() { return s.end(); }
};
