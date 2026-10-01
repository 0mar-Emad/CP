template<typename T, auto merge>
struct SparseTable {
  int n, lg;
  vector<vector<T>> tbl;
  SparseTable() {}
  SparseTable(const vector<T> &v) { init(v); }
  void init(const vector<T> &v) {
    n = v.size();
    lg = __lg(n);
    tbl.assign(lg + 1, vector<T>(n));
    copy(v.begin(), v.end(), tbl[0].begin());
    for (int p = 1; p <= lg; p++) {
      for (int i = 0; i + (1 << p) <= n; i++) {
        tbl[p][i] = merge(tbl[p - 1][i], tbl[p - 1][i + (1 << (p - 1))]);
      }
    }
  }
  T query(int l, int r) {
    int p = __lg(r - l + 1);
    return merge(tbl[p][l], tbl[p][r - (1 << p) + 1]);
  }
};
inline int merge(int a, int b) {
  // merge queries
}