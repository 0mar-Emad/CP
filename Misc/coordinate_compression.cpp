auto t(v);
sort(t.begin(), t.end());
t.erase(unique(t.begin(), t.end()), t.end());

auto idx = [&](int x) {
  return lower_bound(t.begin(), t.end(), x) - t.begin();
};

// or if i don’t need original values
for (int i = 0; i < n; i++) {
  v[i] = lower_bound(t.begin(), t.end(), v[i]) - t.begin();
}