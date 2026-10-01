const int SQ; // update this 1e5 -> 317, 2e5 -> 450
struct Query {
  int l, r, idx;
  bool operator<(const Query &other) const {
    if (l / SQ != other.l / SQ) {
      return l / SQ < other.l / SQ;
    }
    return l / SQ & 1 ? r < other.r : r > other.r;
  }
};

// in main
sort(queries.begin(), queries.end());
auto update = [&](int i, int d) {
  // update logic
};
int l = 0, r = -1;
vector<int> ans(q);
for (auto &[lx, rx, idx] : queries) {
  while (l > lx) update(--l, 1);
  while (r < rx) update(++r, 1);
  while (l < lx) update(l++, -1);
  while (r > rx) update(r--, -1);
  // get answer
}