template<typename T, auto merge>
struct BIT {
  int n;
  vector<T> tree;
  BIT(int n) : n(n), tree(n + 1, 0) {}
  void update(int i, T val) {
    for (++i; i <= n; i += i & -i) {
      tree[i] = merge(tree[i], val);
    }
  }
  T query(int r) {
    int res = 0;
    for (++r; r > 0; r -= r & -r) {
      res = merge(res, tree[r]);
    }
    return res;
  }
  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
};
inline int merge(int a, int b) {
  // merge queries
}