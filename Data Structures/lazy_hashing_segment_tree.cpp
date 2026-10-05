mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t rnd(int64_t l, int64_t r) { return uniform_int_distribution<int64_t>(l, r)(rng); }
const int64_t mod1 = 1e9 + 7, mod2 = 1e9 + 9;
const int64_t base1 = rnd(mod1 / 4, mod1 * 3 / 4);
const int64_t base2 = rnd(mod2 / 4, mod2 * 3 / 4);
const int N = 1e5 + 5;
int64_t pw1[N], pw2[N], pfx1[N], pfx2[N];
bool init = false;
void prePw() {
  if (init) return;
  pw1[0] = pw2[0] = pfx1[0] = pfx2[0] = 1;
  for (int i = 1; i < N; i++) {
    pw1[i] = pw1[i - 1] * base1 % mod1;
    pw2[i] = pw2[i - 1] * base2 % mod2;
    pfx1[i] = (pfx1[i - 1] + pw1[i]) % mod1;
    pfx2[i] = (pfx2[i - 1] + pw2[i]) % mod2;
   }
  init = true;
}
struct Hash {
  int64_t h1, h2;
  int len;
  Hash() : h1(0), h2(0), len(0) {}
  Hash(char c) : len(1) {
    h1 = h2 = c - '0' + 1;
  }
  bool operator==(const Hash &o) const {
    return h1 == o.h1 && h2 == o.h2 && len == o.len;
  }
};
struct SegmentTree {
  int n;
  vector<Hash> tree;
  vector<char> lazy;
  SegmentTree() {}
  SegmentTree(const string &s) { init(s); }
  void update(int l, int r, char ch) { update(1, 0, n - 1, l, r, ch); }
  Hash query(int l, int r) { return query(1, 0, n - 1, l, r); }
  void init(const string &s) {
    prePw();
    n = s.size();
    tree.assign(n << 2, Hash());
    lazy.assign(n << 2, '\0');
    build(1, 0, n - 1, s);
  }
  void build(int node, int l, int r, const string &s) {
    if (l == r) {
      tree[node] = s[l];
      return;
    }
    int m = l + r >> 1;
    build(node << 1, l, m, s);
    build(node << 1 | 1, m + 1, r, s);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
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
  void act(int node, char ch) {
    auto &[h1, h2, len] = tree[node];
    if (len == 0) return;
    int64_t val = ch - '0' + 1;
    h1 = val * pfx1[len - 1] % mod1;
    h2 = val * pfx2[len - 1] % mod2;
    lazy[node] = ch;
  }
  void push(int node, int l, int r) {
    if (l == r || lazy[node] == '\0') {
      return;
    }
    int m = l + r >> 1;
    act(node << 1, lazy[node]);
    act(node << 1 | 1, lazy[node]);
    lazy[node] = '\0';
  }
  void update(int node, int l, int r, int lx, int rx, char ch) {
    push(node, l, r);
    if (l > rx || r < lx) {
      return;
    }
    if (l >= lx && r <= rx) {
      act(node, ch);
      return;
    }
    int m = l + r >> 1;
    update(node << 1, l, m, lx, rx, ch);
    update(node << 1 | 1, m + 1, r, lx, rx, ch);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
  }
  Hash query(int node, int l, int r, int lx, int rx) {
    push(node, l, r);
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