namespace KKT89
{
  std::vector<ll> dijkstra(int start, std::vector<std::vector<std::pair<int, ll>>>& graph)
  {
    std::vector<ll> dist(graph.size(), INF); dist[start] = 0;
    std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<std::pair<ll, int>>> pq;
    pq.emplace(0, start);
    while (!pq.empty()) {
      ll cost; int idx;
      std::tie(cost, idx) = pq.top();
      pq.pop();
      if (dist[idx] < cost) continue;
      for (auto next : graph[idx]) 
        if (chmin(dist[next.first], cost + next.second))
          pq.emplace(dist[next.first], next.first);
    }
    return dist;
  }
}
