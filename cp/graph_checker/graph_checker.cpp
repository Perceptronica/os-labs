#include "graph_checker.h"

using namespace std;
using graph = vector<vector<int>>;

void Graph_checker::dfs_connectivity_component(int u, const graph& g, vector<int>& vis) {
    vis[u] = 1;
    for (auto& v : g[u]) {
        if (!vis[v]) {
            dfs_connectivity_component(v, g, vis);
        }
    }
}

int Graph_checker::connectivity_component(ParsedData& parsed_data) {
    vector<int> vis(parsed_data.g.size());
    int res = 0;
    for (int i = 0; i < vis.size(); ++i) {
        if (!vis[i]) {
            dfs_connectivity_component(i, parsed_data.g_undirected, vis);
            res++;
        }
    }
    return res;
}

vector<int> get_all_edges(ParsedData& parsed_data) {
    vector<int> edges(parsed_data.json_data.size());
    int index = 0;
    for (auto& elem : parsed_data.json_data) {
        edges[index++] = elem.id;
    }
    return edges;
}

size_t cnt_nodes(ParsedData& pd) {
    unordered_set<int> nodes;
    for (auto& elem : pd.json_data) {
        nodes.insert(elem.id);
    }
    return nodes.size();
}

bool Graph_checker::check_cycle_dfs(const graph& g, int u, vector<int>& color, unordered_set<int>& st) {
    color[u] = GREY;
    st.insert(u);

    for (int v : g[u]) {
        if (color[v] == WHITE) {
            if (check_cycle_dfs(g, v, color, st)) {
                return true;
            }
        } else if (st.count(v) > 0) {
            // Найден цикл
            return true;
        }
    }

    color[u] = BLACK;
    st.erase(u);
    return false;
}

vector<int> Graph_checker::get_start_jobs(ParsedData& parsed_data) {
    vector<int> result;
    for (auto& job : parsed_data.json_data) {
        if (job.prev_id == -1) {
            result.push_back(job.id);
        }
    }
    return result;
}

bool Graph_checker::check_cycle(ParsedData& parsed_data) {
    vector<int> color(parsed_data.g.size());
    unordered_set<int> st;
    vector<int> start_edges = get_start_jobs(parsed_data);

    for (int i = 0; i < color.size(); ++i) {
        if (!color[i]) {
            if (check_cycle_dfs(parsed_data.g, i, color, st)) {
                return true;
            }
        }
    }
    return false;
}

void Graph_checker::check(ParsedData& parsed_data) {
    if (connectivity_component(parsed_data) > 1) {
        throw std::runtime_error("Graph has more than one connectivity component");
    }
    if (check_cycle(parsed_data)) {
        throw std::runtime_error("Graph has a cycle");
    }
}

void count_parents(ParsedData& parsed_data) {
    for (auto& job : parsed_data.json_data) {
        int temp_id = job.id - 1;
        int cnt = 0;
        for (auto& children : parsed_data.g) {
            for (auto& child : children) {
                if (temp_id == child) {
                    cnt++;
                }
            }
        }
        job.num_parents = cnt;
    }
}

size_t count_children(int u, ParsedData& pd) {
    return pd.g[u - 1].size();
}

vector<int> get_children(int u, ParsedData& parsed_data) {
    return parsed_data.g[u - 1];
}
