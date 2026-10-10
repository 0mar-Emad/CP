struct Node {
  int64_t v;
  int lc, rc;
  Node(int64_t nt = 0) : v(nt), lc(-1), rc(-1) {}
  Node &operator=(const Node &other) {
    v = other.v;
    return *this;
  }
};
struct Lazy {
  int64_t v;
  Lazy() : v(0) {}
  Lazy(int64_t x) : v(x) {}
  bool operator==(const Lazy &other) const {
    return v == other.v;
  }
};
template<typename T, typename L, auto merge, auto compose, auto apply>
struct SegmentTree {
  int64_t n;
  vector<T> tree;
  vector<L> lazy;
  SegmentTree() {}
  SegmentTree(int64_t sz) { init(sz); }
  void update(int64_t lx, int64_t rx, const L &op) { update(0, 0, n - 1, lx, rx, op); }
  T query(int64_t lx, int64_t rx) { return query(0, 0, n - 1, lx, rx); }
  void init(int64_t sz) {
    n = sz;
    tree.assign(1, T());
    lazy.assign(1, L());
  }
  void extend(int x, int t) {
    if (t == 0) {
      if (tree[x].lc == -1) {
        tree[x].lc = tree.size();
        tree.push_back(T());
        lazy.push_back(L());
      }
    } else {
      if (tree[x].rc == -1) {
        tree[x].rc = tree.size();
        tree.push_back(T());
        lazy.push_back(L());
      }
    }
  }
  void act(int node, const L &op, int64_t l, int64_t r) {
    tree[node] = apply(tree[node], op, r - l + 1);
    lazy[node] = compose(lazy[node], op);
  }
  void push(int node, int64_t l, int64_t r) {
    if (l == r || lazy[node] == L()) {
      return;
    }
    extend(node, 0);
    extend(node, 1);
    int64_t m = l + r >> 1;
    act(tree[node].lc, lazy[node], l, m);
    act(tree[node].rc, lazy[node], m + 1, r);
    lazy[node] = L();
  }
  void update(int node, int64_t l, int64_t r, int64_t lx, int64_t rx, const L &op) {
    if (l > rx || r < lx) {
      return;
    }
    if (l >= lx && r <= rx) {
      act(node, op, l, r);
      return;
    }
    push(node, l, r);
    int64_t m = l + r >> 1;
    if (lx <= m) {
      extend(node, 0);
      update(tree[node].lc, l, m, lx, rx, op);
    }
    if (rx > m) {
      extend(node, 1);
      update(tree[node].rc, m + 1, r, lx, rx, op);
    }
    tree[node] = merge(tree[tree[node].lc], tree[tree[node].rc]);
  }
  T query(int node, int64_t l, int64_t r, int64_t lx, int64_t rx) {
    if (node == -1 || l > rx || r < lx) {
      return T();
    }
    if (l >= lx && r <= rx) {
      return tree[node];
    }
    push(node, l, r);
    int64_t m = l + r >> 1;
    T l_ans = query(tree[node].lc, l, m, lx, rx);
    T r_ans = query(tree[node].rc, m + 1, r, lx, rx);
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