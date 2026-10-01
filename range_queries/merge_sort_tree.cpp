struct MergeSortTree {
  int n;
  vector<vector<int>> tree;
  MergeSortTree(const vector<int> &v) { init(v); }
  int query(int l, int r, int k) { return query(1, 0, n - 1, l, r, k); }
  void init(const vector<int> &v) {
    n = v.size();
    tree.resize(n << 2);
    build(1, 0, n - 1, v);
  }
  void build(int node, int l, int r, const vector<int> &v) {
    if (l == r) {
      tree[node].push_back(v[l]);
      return;
    }
    int m = l + r >> 1;
    build(node << 1, l, m, v);
    build(node << 1 | 1, m + 1, r, v);
    vector<int>& a = tree[node << 1];
    vector<int>& b = tree[node << 1 | 1];
    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(tree[node]));
  }
  int less(vector<int> &v, int k) {
    return lower_bound(v.begin(), v.end(), k) - v.begin();
    // less equal -> upperbound
  }
  int greater(vector<int> &v, int k) {
    return v.end() - upper_bound(v.begin(), v.end(), k);
    // greater equal -> lowerbound
  }
  int equal(vector<int> &v, int k) {
    return upper_bound(v.begin(), v.end(), k) - lower_bound(v.begin(), v.end(), k);
  } 
  int query(int node, int l, int r, int lx, int rx, int k) {
    if (l > rx || r < lx) {
      return 0;
    }
    if (l >= lx && r <= rx) {
      return less(tree[node], k);
      // don't forget to change this
    }
    int m = l + r >> 1;
    int l_ans = query(node << 1, l, m, lx, rx, k);
    int r_ans = query(node << 1 | 1, m + 1, r, lx, rx, k);
    return l_ans + r_ans;
  }
};