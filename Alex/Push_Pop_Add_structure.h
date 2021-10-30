// Push element in structure
// Pop minimum element from structure
// Add value to all the elements in structure
struct Solver {
  priority_queue<int, vector<int>, greater<int>> st;
  int add_so_far = 0;
  int Pop() {
    int x = st.top();
    st.pop();
    return x + add_so_far;
  }
  void Push(int x) {
    st.emplace(x - add_so_far)
  }
  void Add(int x) {
    add_so_far += x;
  }
};
