inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
  if (pow == 0) return 0;
  int hpow = 1 << (pow-1);
  int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2*pow - 2);
  int64_t ans = seg * subSquareSize;
  int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}
struct Query {
  int l, r, idx;
  int64_t ord;
  inline void calcOrder() {
    ord = hilbertOrder(l, r, 21, 0);
  }
  bool operator<(const Query &other) const {
    return ord < other.ord;
  }
};

// in main
sort(queries.begin(), queries.end());
auto update = [&](int i, int d) {
  // update logic
};
int l = 0, r = -1;
vector<int> ans(q);
for (auto &[lx, rx, idx, ord] : queries) {
  while (l > lx) update(--l, 1);
  while (r < rx) update(++r, 1);
  while (l < lx) update(l++, -1);
  while (r > rx) update(r--, -1);
  // get answer
}