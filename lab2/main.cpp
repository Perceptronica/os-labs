#include <cassert>
#include <random>
#include <chrono>
#include "gaussian.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " <max_threads>" << endl;
        exit(EXIT_FAILURE);
    }

    int max_threads = stoi(argv[1]);
    assert(max_threads > 0);
    int N[] = {1000};
    for (int& k : N) {
        int n = k;
        int m = k;
        Matrix A(n, Row(m));
        Row B(m);
        random_device rd;
        mt19937 gen(rd()); // генератор Мерсенна Твистера, 
                        // инициализируется неким уникальным числом из random_device rd
        uniform_real_distribution<float> dist(-1000.0f, 1000.0f);
                        // генерация float с плавающей запятой в [-1000; 1000].
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                A[i][j] = dist(gen);
            }
        }
        for (int i = 0; i < n; ++i) {
            B[i] = dist(gen);
        }
        for (int i = 1; i <= max_threads; ++i) {
            chrono::time_point<chrono::steady_clock> start;
            chrono::time_point<chrono::steady_clock> end;
            start = chrono::steady_clock::now();
            GaussianElimination(A, B, i);
            end = chrono::steady_clock::now();
            auto time = chrono::duration_cast<chrono::milliseconds>(end - start);
            int t = 0;
            if (i == 1) {
                t = (int) time.count();
            }
            double s_p = (int) time / t;
            cout << i << "," << n << "," << m << "," << to_string(time.count()) << endl;
        }
    }

}