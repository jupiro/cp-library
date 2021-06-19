namespace KKT89
{
	template<typename Monoid, typename F>
	struct SegmentTree {
		int sz;
		std::vector<Monoid> seg;
		const F f;
		const Monoid IE;
	 
		SegmentTree(int n, const F f, const Monoid& IE) :f(f), IE(IE) {
			sz = 1;
			while (sz < n) sz *= 2;
			seg.assign(2 * sz, IE);
		}
	 
		void set(int k, const Monoid& x) {
			seg[k + sz] = x;
		}
	 
		void build() {
			for (int k = sz - 1; k > 0; k--) {
				seg[k] = f(seg[k * 2], seg[k * 2 + 1]);
			}
		}
	 
		void update(int k, const Monoid& x) {
			k += sz;
			seg[k] = x;
			while (k /= 2) {
				seg[k] = f(seg[k * 2], seg[k * 2 + 1]);
			}
		}
	 
		Monoid query(int a, int b) {
			if (a >= b) return IE;
			Monoid L = IE, R = IE;
			for (a += sz, b += sz; a < b; a /= 2, b /= 2) {
				if (a & 1) L = f(L, seg[a++]);
				if (b & 1) R = f(seg[--b], R);
			}
			return f(L, R);
		}
	 
		template<typename C>
		int find_subtree(int idx, const C& check, Monoid& M, bool type) {
			while (idx < sz) {
				Monoid nxt = type ? f(seg[2 * idx + 1], M) : f(M, seg[2 * idx]);
				if (check(nxt)) idx = idx * 2 + type;
				else M = nxt, idx = idx * 2 + 1 - type;
			}
			return idx - sz;
		}
	 
		template<typename C>
		int min_left(int a, const C& check) {
			Monoid L = IE;
			if (a <= 0) {
				if (check(f(L, seg[1]))) return find_subtree(1, check, L, false);
				return -1;
			}
			int b = sz;
			for (a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
				if (a & 1) {
					Monoid nxt = f(L, seg[a]);
					if (check(nxt)) return find_subtree(a, check, L, false);
					L = nxt;
					a += 1;
				}
			}
			return -1;
		}
	 
		template<typename C>
		int max_right(int b, const C& check) {
			Monoid R = IE;
			if (b >= sz) {
				if (check(f(seg[1], R))) return find_subtree(1, check, R, true);
				return -1;
			}
			int a = 0;
			for (a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
				if (b & 1) {
					b -= 1;
					Monoid nxt = f(seg[b], R);
					if (check(nxt)) return find_subtree(b, check, R, true);
					R = nxt;
				}
			}
			return -1;
		}
	};
}