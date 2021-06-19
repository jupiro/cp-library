namespace KKT89
{
  template<typename Monoid, typename OperatorMonoid, typename F, typename G, typename H>
  struct LazySegmentTree {
    int sz, height;
    std::vector<Monoid> data;
    std::vector<OperatorMonoid> lazy;
    const F f;
    const G g;
    const H h;
    const Monoid MIE;
    const OperatorMonoid OMIE;
    LazySegmentTree(int n, const F f, const G g, const H h, const Monoid& MIE, const OperatorMonoid OMIE) :f(f), g(g), h(h), MIE(MIE), OMIE(OMIE) {
      sz = 1;
      height = 0;
      while (sz < n) sz <<= 1, height += 1;
      data.assign(sz * 2, MIE);
      lazy.assign(sz * 2, OMIE);
    }

    void set(int k, const Monoid& x) {
      data[k + sz] = x;
    }

    void build() {
      for (int k = sz - 1; k > 0; k--) {
        data[k] = f(data[2 * k], data[2 * k + 1]);
      }
    }

    inline void propagate(int k) {
      if (lazy[k] != OMIE) {
        lazy[2 * k] = h(lazy[2 * k], lazy[k]);
        lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
        data[k] = apply(k);
        lazy[k] = OMIE;
      }
    }

    inline Monoid apply(int k) {
      return lazy[k] == OMIE ? data[k] : g(data[k], lazy[k]);
    }

    inline void recalc(int k) {
      while (k >>= 1) data[k] = f(apply(2 * k), apply(2 * k + 1));
    }

    inline void thrust(int k) {
      for (int i = height; i > 0; i--) propagate(k >> i);
    }

    void update(int a, int b, const OperatorMonoid& x) {
      if (a >= b) return;
      thrust(a += sz);
      thrust(b += sz - 1);
      for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) lazy[l] = h(lazy[l], x), l++;
        if (r & 1) --r, lazy[r] = h(lazy[r], x);
      }
      recalc(a);
      recalc(b);
    }

    Monoid query(int a, int b) {
      if (a >= b) return MIE;
      thrust(a += sz);
      thrust(b += sz - 1);
      Monoid L = MIE, R = MIE;
      for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) L = f(L, apply(l++));
        if (r & 1) R = f(apply(--r), R);
      }
      return f(L, R);
    }

    template<typename C>
    int find_subtree(int idx, const C& check, Monoid& M, bool type) {
      while (idx < sz) {
        propagate(idx);
        Monoid nxt = type ? f(apply(2 * idx + 1), M) : f(M, apply(2 * idx));
        if (check(nxt)) idx = 2 * idx + type;
        else M = nxt, idx = 2 * idx + 1 - type;
      }
      return idx - sz;
    }

    template<typename C>
    int min_left(int a, const C& check) {
      Monoid L = MIE;
      if (a <= 0) {
        if (check(f(L, apply(1)))) return find_subtree(1, check, L, false);
        return -1;
      }
      thrust(a + sz);
      int b = sz;
      for (a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
        if (a & 1) {
          Monoid nxt = f(L, apply(a));
          if (check(nxt)) return find_subtree(a, check, L, false);
          L = nxt;
          a += 1;
        }
      }
      return -1;
    }
    template<typename C>
    int max_right(int b, const C& check) {
      Monoid R = MIE;
      if (b >= sz) {
        if (check(f(apply(1), R))) return find_subtree(1, check, R, true);
        return -1;
      }
      thrust(b + sz - 1);
      int a = 0;
      for (a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
        if (b & 1) {
          b -= 1;
          Monoid nxt = f(apply(b), R);
          if (check(nxt)) return find_subtree(b, check, R, true);
          R = nxt;
        }
      }
      return -1;
    }
  };
}