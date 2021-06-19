template<typename T>
struct Dinic {
    struct edge {
        int to;
        T cap;
        int rev;
        bool isrev;
        int idx;
        edge(int _to, T _cap, int _rev, bool _isrev, int _idx) :to(_to), cap(_cap), rev(_rev), isrev(_isrev), idx(_idx) {}
    };
    std::vector<std::vector<edge>> g;
    std::vector<int> min_cost, iter;
    T INF;
    Dinic(int n, T INF) :g(n), INF(INF) {}

    void add_edge(int from, int to, T cap, int idx = -1) {
        g[from].emplace_back(to, cap, (int)g[to].size(), false, idx);
        g[to].emplace_back(from, 0, (int)g[from].size() - 1, true, idx);
    }

    bool bfs(int s, int t) {
        min_cost.assign(g.size(), -1);
        std::queue<int> q;
        q.emplace(s);
        min_cost[s] = 0;
        while (!q.empty() && min_cost[t] == -1) {
            int cur = q.front();
            q.pop();
            for (auto& e : g[cur]) {
                if (e.cap > 0 && min_cost[e.to] == -1) {
                    min_cost[e.to] = min_cost[cur] + 1;
                    q.push(e.to);
                }
            }
        }
        return min_cost[t] != -1;
    }

    T dfs(int idx, const int t, T flow) {
        if (idx == t) return flow;
        for (int& i = iter[idx]; i < (int)g[idx].size(); i++) {
            edge& e = g[idx][i];
            if (e.cap > 0 && min_cost[idx] < min_cost[e.to]) {
                T d = dfs(e.to, t, std::min(flow, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    T max_flow(int s, int t) {
        T flow = 0;
        while (bfs(s, t)) {
            iter.assign(g.size(), 0);
            T f = 0;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }

    void output() {
        for(int i = 0; i < (int)g.size(); i++) {
          for(auto &e : g[i]) {
            if(e.isrev) continue;
            auto &rev_e = g[e.to][e.rev];
            cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
          }
        }
    }
};