struct Node {
  int64_t v;
  Node() : v(0) {}
  Node(int64_t x) : v(x) {}
  operator int64_t() const { return v; }
};
struct Lazy {
  int64_t v;
  Lazy() : v(0) {}
  Lazy(int64_t x) : v(x) {}
  operator int64_t() const { return v; }
  // bool operator==(const Lazy &other) const {
  //   return v == other.v;
  // }
};
template<typename T, typename L, typename U, auto merge, auto compose, auto apply>
struct SegmentTree {
  int n;
  vector<T> tree;
  vector<L> lazy;
  SegmentTree() {};
  SegmentTree(const vector<U> &v) { init(v); }
  void update(int l, int r, const L &op) { update(1, 0, n - 1, l, r, op); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
  void init(const vector<U> &v) {
    n = v.size();
    tree.assign(n << 2, T());
    lazy.assign(n << 2, L());
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
  void act(int node, const L &op, int l, int r) {
    tree[node] = apply(tree[node], op, r - l + 1);
    lazy[node] = compose(lazy[node], op);
  }
  void push(int node, int l, int r) {
    if (l == r || lazy[node] == L()) {
      return;
    }
    int m = l + r >> 1;
    act(node << 1, lazy[node], l, m);
    act(node << 1 | 1, lazy[node], m + 1, r);
    lazy[node] = L();
  }
  void update(int node, int l, int r, int lx, int rx, const L &op) {
    push(node, l, r);
    if (l > rx || r < lx) {
      return;
    }
    if (l >= lx && r <= rx) {
      act(node, op, l, r);
      return;
    }
    int m = l + r >> 1;
    update(node << 1, l, m, lx, rx, op);
    update(node << 1 | 1, m + 1, r, lx, rx, op);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
  }
  T query(int node, int l, int r, int lx, int rx) {
    push(node, l, r);
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
inline Node mrg(const Node &a, const Node &b) {
  // merge queries
}
inline Lazy comp(const Lazy &a, const Lazy &b) {
  // a is the old lazy.
  // b is the new lazy.
  // merge updates.
}
inline Node app(const Node &a, const Lazy &op, int len) {
  // apply lazy update to a tree node
}