// Stack implementation with Min / Max query
// Useful with Queue.h or Deque.h

template<class T> struct Stack {
  vector<pair<T, T>> stk;

  void push(const T &x) {
    auto p = make_pair(x, x);
    if (!stk.empty()) p.second = min(p.second, stk.back().second);
    stk.emplace_back(p);
  }
  void pop() { stk.pop_back(); }

  T top() const { return stk.back().first; }
  T Min() const { return empty() ? INF : stk.back().second; }
  int size() const { return stk.size(); }
  bool empty() const { return size() == 0; }
};
