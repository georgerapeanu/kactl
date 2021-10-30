template<class T>
struct MedianHeap {
  PriorityQueue<T> lo;
  PriorityQueue<T, vector<T>, greater<T>> hi; 

  void Fix() {
    while (hi.size() > lo.size()) lo.emplace(hi.top()), hi.pop();
    while (lo.size() > hi.size() + 1) hi.emplace(lo.top()), lo.pop();
  }
  
  void emplace(const T &val) {
    if (lo.size() == 0 || val <= lo.top()) lo.emplace(val);
    else hi.emplace(val);
    Fix();
  }

  void erase(const T &val) {
    if (lo.size() && val <= lo.top()) lo.erase(val);
    else hi.erase(val);
    Fix();
  }

  T top() { return lo.top(); }
};