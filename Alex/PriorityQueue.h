template<class T, class Container = vector<T>, class Compare = less<T>>
struct PriorityQueue {
  int sz = 0;
  priority_queue<T, Container, Compare> pq, del;

  void emplace(const T &val) { pq.emplace(val); ++sz; }
  void erase(const T &val) { del.emplace(val); --sz; }
  void pop() { erase(top()); }
  T top() {
    while (!del.empty() && !pq.empty() && del.top() == pq.top()) del.pop(), pq.pop();
    return pq.top();
  }
  int size() const {return sz;}
};