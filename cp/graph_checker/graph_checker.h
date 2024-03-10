#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include "../json_parser/json.h"

using namespace std;
using graph = vector<vector<int>>;

enum {
    WHITE = 0, GREY = 1, BLACK = 2
};

class Graph_checker {
private:
    static void dfs_connectivity_component(int u, const graph& g, vector<int>& vis);
    static bool check_cycle(ParsedData& parsed_data);
    static int connectivity_component(ParsedData& parsed_data);
    static bool check_cycle_dfs(const graph& g, int u, vector<int>& vis, unordered_set<int>& st);
public:
    static vector<int> get_start_jobs(ParsedData& parsed_data);
    static void check(ParsedData& parsed_data);
};

size_t cnt_nodes(ParsedData& pd);
vector<int> get_all_edges(ParsedData& parsed_data);
void count_parents(ParsedData& parsed_data);
size_t count_children(int u, ParsedData& pd);
vector<int> get_children(int u, ParsedData& parsed_data);
