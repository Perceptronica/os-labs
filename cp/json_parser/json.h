#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

using namespace std;
using json = nlohmann::json;
using graph = vector<vector<int>>;

class JSONData {
public:
    int id;
    int prev_id;
    string cmd;
    string output;
    int num_parents = 0;
    int num_completed_parents = 0;
};

class ParsedData {
public:
    graph g;
    graph g_undirected;
    std::vector<JSONData> json_data;
    unordered_map<string, int> sem_name_to_degree;
};

class JSON_parser {
public:
    static ParsedData parse(const std::string &file_path);
};