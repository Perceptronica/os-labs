#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "the wrong argument" << endl;
        exit(EXIT_FAILURE);
    }
    
    const char *filename = argv[1];
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "file opening failure" << endl;
        exit(EXIT_FAILURE);
    }
    
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<float> numbers;
        float num;
        bool zero_flag = false;
        while (iss >> num) {
            numbers.push_back(num);
        }
        
        if (numbers.size() < 2) {
            cerr << "not enough numbers" << endl;
            continue;
        }
        
        float result = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            if (numbers[i] == 0) {
                cerr << "error: division by zero" << endl;
                zero_flag = true;
                break;
            }
            result /= numbers[i];
        }
        if (!zero_flag) {
            file << result << endl;
        } else {
            zero_flag = false;
        }
    }
    
    file.close();
    return 0;
}
