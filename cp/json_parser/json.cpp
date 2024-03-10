#include "json.h"

ParsedData JSON_parser::parse(const std::string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("file opening error");
    }
    json json_input_data;
    file >> json_input_data;
    file.close();
    ParsedData parsed_data;
    json array_of_jobs = json_input_data["jobs"];
    parsed_data.json_data.resize(array_of_jobs.size());
    int i = 0;

    // считываем данные из json в массив
    for (const auto& job : array_of_jobs) {
        parsed_data.json_data[i].id = job["id"];
        parsed_data.json_data[i].prev_id = job["prev_id"];
        parsed_data.json_data[i].cmd = job["cmd"];
        parsed_data.json_data[i].output = job["output"];
        i++;
    }
    // количество уникальных элементов
    unordered_set<int> st;
    for (const auto& job : parsed_data.json_data) {
        st.insert(job.id);
        if (job.prev_id != -1) {
            st.insert(job.prev_id);
        }
    }
    int n = 0;
    for (auto& job : parsed_data.json_data) {
        if (n < job.id) {
            n = job.id;
        }
        if (n < job.prev_id) {
            n = job.prev_id;
        }
    }
    
    graph g(st.size());
    graph g_undirected(st.size());
    for (const auto& job : parsed_data.json_data) {
        int cur_id = job.id;
        int prev_id = job.prev_id;
        if (prev_id == -1) {
            continue;
        }
        --cur_id; 
        --prev_id;
        g[prev_id].push_back(cur_id);
        g_undirected[prev_id].push_back(cur_id);
        g_undirected[cur_id].push_back(prev_id);
    }

    std::vector<JSONData> new_jd;

    parsed_data.g = g;
    parsed_data.g_undirected = g_undirected;

    return parsed_data;
}