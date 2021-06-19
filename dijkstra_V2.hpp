template<typename T>
std::vector<T> dijkstra_V2(int start, std::vector<std::vector<T>>& dist, T INF) {
    int n = dist.size();
    std::vector<T> res(n, INF);
    std::queue<int> q;
    q.emplace(start);
    std::vector<bool> used(n, false);
    res[start] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        used[cur] = true;
        for (int i = 0; i < n; i++) chmin(res[i], res[cur] + dist[cur][i]);
        int next = -1;
        T d = INF;
        for (int i = 0; i < n; i++) if (!used[i]) if (chmin(d, res[i])) next = i;
        if (next != -1) q.emplace(next);
    }
    return res;
}