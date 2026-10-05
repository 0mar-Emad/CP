struct BIT {
  int n;
  vector<int> tree;
  BIT(int n) : n(n), tree(n + 1) {}
  void update(int i, int val) {
    for (++i; i <= n; i += i & -i) {
      tree[i] += val;
    }
  }
  int query(int r) {
    int res = 0;
    for (++r; r > 0; r -= r & -r) {
      res += tree[r];
    }
    return res;
  }
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
};