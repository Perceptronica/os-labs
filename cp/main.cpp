#include "graph_checker/graph_checker.h"

int main() {
    ParsedData pd;
    pd = JSON_parser::parse("examples/data.json");
    Graph_checker::check(pd);
    count_parents(pd);
    vector<JSONData> new_jd;
    for (auto& elem : pd.json_data) {
        bool is_here = false;
        for (auto & el : new_jd) {
            if (elem.id == el.id) {
                is_here = true;
            }
        }
        if (!is_here) {
            new_jd.push_back(elem);
        }
    }
    pd.json_data = new_jd;
    vector<int> start_jobs = Graph_checker::get_start_jobs(pd);
    int cnt_start_jobs = (int)start_jobs.size();
    

    
    cout << "End" << endl;
    return 0;
}