struct TwoSAT {
public:
  int n;
  std::vector<bool> res;
  StronglyConnectedComponents scc;
  TwoSAT(int _n) :n(_n), res(n), scc(2 * n) {}

  void add_clause(int i, bool f, int j, bool g) {
    scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
    scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
  }

  bool satisfiable() {
    scc.build();
    for (int i = 0; i < n; i++) {
      if (scc[i * 2 + 0] == scc[i * 2 + 1]) return false;
      res[i] = scc[i * 2 + 0] < scc[i * 2 + 1];
    }
    return true;
  }
  bool operator[](int i) { return res[i]; }
};