#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: child <filename>" << endl;
        return 1;
    }

    ofstream outfile(argv[1], ios::binary);
    if (!outfile.is_open()) {
        cerr << "file opening error!" << endl;
        return 1;
    }
    
    string line;
    float num, divisor, result;

    while(getline(cin, line)) {
        istringstream iss(line);
        vector<float> numbers;
        
        while (iss >> num) { numbers.push_back(num); }

        if (numbers.size() < 2) {
            if (line.find("exit") != string::npos) { break; }
            cerr << "not enough numbers provided!" << endl;
            continue;
        }

        result = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            divisor = numbers[i];
            if (divisor == 0) {
                cerr << "division by 0 -> terminating" << endl;
                outfile.close();
                return 1;
            }
            result /= divisor;
        }
        outfile << result << '\n';
    }

    outfile.close();
    return 0;
}