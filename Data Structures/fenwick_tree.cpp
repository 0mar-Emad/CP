template<typename T>
struct BIT {
  int n;
  vector<T> tree;
  BIT(int sz) : n(sz + 5), tree(n) {}
  BIT(vector<int> &v) : n(v.size() + 5), tree(n) {
    for (int i = 1; i <= v.size(); i++) {
      tree[i] += v[i - 1];
      int r = i + (i & -i);
      if (r < n) tree[r] += tree[i];
    }
  }
  void update(int i, T val) {
    for (++i; i <= n; i += i & -i) {
      tree[i] += val;
    }
  }
  int query(int r) {
    T ret = 0;
    for (++r; r > 0; r -= r & -r) {
      ret += tree[r];
    }
    return ret;
  }
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
  int lower_bound(T x) {
    T ret = 0;
    int pos = 0;
    for (int i = __lg(n); ~i; i--) {
      if (pos + (1 << i) < n && sum + tree[pos + (1 << i)] < x) {
        pos += 1 << i;
        sum += tree[pos];
      }
    }
    return pos;
  }
};