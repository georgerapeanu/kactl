// Queue implementation using 2 stacks
// Suports basic operations + Min / Max
// To be used with Stack.h

template<class T> struct Queue {
  Stack<T> fr, bk;

  void Fix(Stack<T> &to, Stack<T> &from) {
    while (!from.empty()) to.push(from.top()), from.pop();
  }

  void push(const T &x) { bk.push(x); }
  void pop() {
    if (fr.empty()) Fix(fr, bk);
    fr.pop();
  }
  T front() {
    if (fr.empty()) Fix(fr, bk);
    return fr.top();
  }

  int size() const { return fr.size() + bk.size(); }
  bool empty() const { return size() == 0; }

  T Min() const { return min(fr.Min(), bk.Min()); }
};
