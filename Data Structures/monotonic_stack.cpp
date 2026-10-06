vector<int> nextMax(vector<int> &a, int n) {
  stack<int> st;
  vector<int> ret(n + 2, n + 1);
  for (int j = 1; j <= n; j++) {
    while (!st.empty() && a[st.top()] < a[j]) {
      ret[st.top()] = j;
      st.pop();
    }
    st.push(j);
  }
  return ret;
}
vector<int> prevMax(vector<int> &a, int n) {
  stack<int> st;
  vector<int> ret(n + 2, 0);
  for (int j = n; j >= 1; j--) {
    while (!st.empty() && a[st.top()] <= a[j]) {
      ret[st.top()] = j;
      st.pop();
    }
    st.push(j);
  }
  return ret;
}
