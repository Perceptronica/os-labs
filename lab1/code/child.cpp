#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("incorrect arguments");
        exit(EXIT_FAILURE);
    }

    string filename(argv[1]);
    ofstream outfile(filename, ofstream::app);
    string input;
    
    if (!outfile.is_open()) {
        perror("failed to open file");
        exit(EXIT_FAILURE);
    }
    cout << "enter the strings of numbers:" << endl;
    while (getline(cin, input)) {
        istringstream iss(input);
        vector<float> nums;
        float num;

        while (iss >> num) {
            nums.push_back(num);
        }

        if (nums.empty()) continue;

        float result = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                perror("exit: division by zero"); // Сообщаем родителю о необходимости выхода
                exit(EXIT_FAILURE); // Выходим из программы
            }
            result /= nums[i];
        }
        outfile << result << endl; // Записываем результат в файл
    }
    outfile.close();
    return 0;
}
