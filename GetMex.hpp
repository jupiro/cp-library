template<typename T>
int GetMex(const std::vector<T>& a) {
  const int n = a.size();
  std::vector<bool> used(n + 1);
  for (auto& e : a) if(e <= n) used[e] = true;
  int res = -1;
  for (int i = 0; i <= n; i++) {
    if (!used[i]) {
      res = i;
      break;
    }
  }
  return res;
}
