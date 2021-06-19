std::vector<int> topological_sort(const std::vector<std::vector<int>>& g) {
	std::vector<int> topo;
	const int n = g.size();
	std::vector<int> deg(n);
	for (int i = 0; i < n; i++) for (auto next : g[i]) deg[next]++;
	std::queue<int> q;
	for (int i = 0; i < n; i++) if (deg[i] == 0) q.push(i), topo.push_back(i);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (auto next : g[cur]) {
			deg[next]--;
			if (deg[next] == 0) {
				q.emplace(next);
				topo.push_back(next);
			}
		}
	}
	return topo;
}