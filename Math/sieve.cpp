bitset<N> comp;
comp[0] = comp[1] = 1;
for (int i = 2; i * i < N; i++) {
  if (comp[i]) continue;
  for (int j = i * i; j < N; j += i) {
    comp[j] = 1;
  }
}