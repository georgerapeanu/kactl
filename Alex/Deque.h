// Implementation of deque using 3 stacks
// It can also return the minimum / maximum in the structure
// To be used with Stack.h

template<class T> void Move(Stack<T> &from, Stack<T> &to, int cnt) {
  while (cnt--) to.push(from.top()), from.pop();
}

template<class T> struct Deque {
  Stack<T> fr, aux, bk;

  void Fix(Stack<T> &to, Stack<T> &from) {
    Move(from, aux, from.size() / 2); 
    Move(from, to, from.size());
    Move(aux, from, aux.size());
  }

  void emplace_back(const T &x) { bk.push(x); }
  void pop_back() {
    if (bk.empty()) Fix(bk, fr);
    bk.pop();
  }
  T back() {
    if (bk.empty()) Fix(bk, fr);
    return bk.top();
  }

  void emplace_front(const T &x) { fr.push(x); }
  void pop_front() {
    if (fr.empty()) Fix(fr, bk);
    fr.pop();
  }
  T front() {
    if (fr.empty()) Fix(fr, bk);
    return fr.top();
  }

  int size() const { return fr.size() + bk.size(); }
  bool empty() const { return size() == 0; }
  int Min() const { return min(fr.Min(), bk.Min()); }
};
