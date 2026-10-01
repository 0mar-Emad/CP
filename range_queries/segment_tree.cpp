struct Node {
  int64_t v;
  Node() : v(0) {}
  Node(int64_t x) : v(x) {}
  operator int64_t() const { return v; }  
};
template<typename T, typename U, auto merge>
struct SegmentTree {
  int n;
  vector<T> tree;
  SegmentTree() {}
  SegmentTree(const vector<U> &v) { init(v); }
  void update(int idx, U val) { update(1, 0, n - 1, idx, val); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
  void init(const vector<U> &v) {
    n = v.size();
    tree.assign(n << 2, T());
    build(1, 0, n - 1, v);
  }
  void build(int node, int l, int r, const vector<U> &v) {
    if (l == r) {
      tree[node] = T(v[l]);
      return;
    }
    int m = l + r >> 1;
    build(node << 1, l, m, v);
    build(node << 1 | 1, m + 1, r, v);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
  }
  void update(int node, int l, int r, int idx, U val) {
    if (l == r) {
      tree[node] = T(val);
      return;
    }
    int m = l + r >> 1;
    if (idx <= m) {
      update(node << 1, l, m, idx, val);
    } else {
      update(node << 1 | 1, m + 1, r, idx, val);
    }
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
  }
  T query(int node, int l, int r, int lx, int rx) {
    if (l > rx || r < lx) {
      return T();
    }
    if (l >= lx && r <= rx) {
      return tree[node];
    }
    int m = l + r >> 1;
    T l_ans = query(node << 1, l, m, lx, rx);
    T r_ans = query(node << 1 | 1, m + 1, r, lx, rx);
    return merge(l_ans, r_ans);
  }
};
inline Node merge(const Node &a, const Node &b) {
  // merge queries
}