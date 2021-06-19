struct StronglyConnectedComponents {
	int n, group_num, now_ord;
	std::vector<std::vector<int>> g;
	std::vector<int> low, ord, idx;
	StronglyConnectedComponents() = default;
	StronglyConnectedComponents(int _n) :n(_n), group_num(0), now_ord(0) , g(n), low(n), ord(n, -1), idx(n){}
	void add_edge(int from, int to) {
		g[from].emplace_back(to);
	}
	void dfs(int cur, std::vector<int>& visited) {
		ord[cur] = low[cur] = now_ord++;
		visited.emplace_back(cur);
		for (auto nxt : g[cur]) {
			if (ord[nxt] == -1) {
				dfs(nxt, visited);
				chmin(low[cur], low[nxt]);
			}
			else {
				chmin(low[cur], ord[nxt]);
			}
		}
		if (ord[cur] == low[cur]) {
			while (true) {
				int v = visited.back();
				visited.pop_back();
				ord[v] = n; //別のdfs木からこないように
				idx[v] = group_num;
				if (cur == v) break;
			}
			group_num++;
		}
	}



	//sccのidxに入ってる頂点番号 idxはトポロジカル順
	void build() {
		std::vector<int> visited;
		for (int i = 0; i < n; i++) if (ord[i] == -1) dfs(i, visited);
		for (int i = 0; i < n; i++) idx[i] = group_num - 1 - idx[i];
	}
	//build()の後にやる
	std::vector<std::vector<int>> groups() {
		std::vector<std::vector<int>> ret(group_num);
		for (int i = 0; i < n; i++) {
			ret[idx[i]].emplace_back(i);
		}
		return ret;
	}
	int operator[](int i) { return idx[i]; }
};