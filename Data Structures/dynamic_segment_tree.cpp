struct Node {
  int64_t v;
  int lc, rc;
  Node(int64_t nt = 0) : v(nt), lc(-1), rc(-1) {}
  Node &operator=(const Node &other) {
    v = other.v;
    return *this;
  }
};
template<typename T, typename U, auto merge>
struct SegmentTree {
  int64_t n;
  vector<T> tree;
  SegmentTree() {}
  SegmentTree(int64_t sz) { init(sz); }
  void update(int64_t idx, U val) { update(0, 0, n - 1, idx, val); }
  T query(int64_t l, int64_t r) { return query(0, 0, n - 1, l, r); }
  void init(int64_t sz) {
    n = sz;
    tree.assign(1, T());
  }
  void extend(int x) {
    if (tree[x].lc == -1) {
      tree[x].lc = tree.size();
      tree.push_back(T());
    }
    if (tree[x].rc == -1) {
      tree[x].rc = tree.size();
      tree.push_back(T());
    }
  }
  void update(int node, int64_t l, int64_t r, int64_t idx, U val) {
    if (l == r) {
      tree[node] = T(val);
      return;
    }
    extend(node);
    int64_t m = l + r >> 1;
    if (idx <= m) {
      update(tree[node].lc, l, m, idx, val);
    } else {
      update(tree[node].rc, m + 1, r, idx, val);
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
    int64_t m = l + r >> 1;
    T l_ans = query(tree[node].lc, l, m, lx, rx);
    T r_ans = query(tree[node].rc, m + 1, r, lx, rx);
    return merge(l_ans, r_ans);
  }
};
inline Node merge(const Node &a, const Node &b) {
  // merge queries
}