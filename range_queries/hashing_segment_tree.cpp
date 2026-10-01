
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rnd(int64_t l, int64_t r) { return uniform_int_distribution<int64_t>(l, r)(rng); }
const int64_t mod1 = 1e9 + 7, mod2 = 1e9 + 9;
const int64_t base1 = rnd(mod1 / 4, mod1 * 3 / 4);
const int64_t base2 = rnd(mod2 / 4, mod2 * 3 / 4);
const int N = 1e5 + 5;
int64_t pw1[N], pw2[N];
bool init = false;
void prePw() {
  if (init) return;
  pw1[0] = 1; pw2[0] = 1;
  for (int i = 1; i < N; i++) {
    pw1[i] = pw1[i - 1] * base1 % mod1;
    pw2[i] = pw2[i - 1] * base2 % mod2;
  }
  init = true;
}
struct Hash {
  int64_t h1, h2;
  int len;
  Hash() : h1(0), h2(0), len(0) {}
  Hash(char c) : h1(c), h2(c), len(1) {}
  bool operator==(const Hash &o) const {
    return h1 == o.h1 && h2 == o.h2 && len == o.len;
  }
};
struct SegmentTree {
  int n;
  vector<Hash> tree;
  SegmentTree() {}
  SegmentTree(const string &s) { init(s); }
  void update(int idx, char ch) { update(1, 0, n - 1, idx, ch); }
  Hash query(int l, int r) { return query(1, 0, n - 1, l, r); }
  void init(const string &s) {
    prePw();
    n = s.size();
    tree.assign(n << 2, Hash());
    build(1, 0, n - 1, s);
  }
  inline Hash merge(const Hash &a, const Hash &b) {
    if (a.len == 0) return b;
    if (b.len == 0) return a;
    Hash res;
    res.len = a.len + b.len;
    res.h1 = (a.h1 * pw1[b.len] % mod1 + b.h1) % mod1;
    res.h2 = (a.h2 * pw2[b.len] % mod2 + b.h2) % mod2;
    return res;
  }
  void build(int node, int l, int r, const string &v) {
    if (l == r) {
      tree[node] = v[l];
      return;
    }
    int m = l + r >> 1;
    build(node << 1, l, m, v);
    build(node << 1 | 1, m + 1, r, v);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
  }
  void update(int node, int l, int r, int idx, char ch) {
    if (l == r) {
      tree[node] = ch;
      return;
    }
    int m = l + r >> 1;
    if (idx <= m) {
      update(node << 1, l, m, idx, ch);
    } else {
      update(node << 1 | 1, m + 1, r, idx, ch);
    }
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
  }
  Hash query(int node, int l, int r, int lx, int rx) {
    if (l > rx || r < lx) {
      return Hash();
    }
    if (l >= lx && r <= rx) {
      return tree[node];
    }
    int m = l + r >> 1;
    auto l_ans = query(node << 1, l, m, lx, rx);
    auto r_ans = query(node << 1 | 1, m + 1, r, lx, rx);
    return merge(l_ans, r_ans);
  }
};