#include "gaussian.hpp"

void* ThreadFunc(void* param) {
    // обнуление элементов в столбце
    ThreadParam* p = static_cast<ThreadParam*>(param);
    // static_cast <type-id> ( expression )
    // преобразует выражение в тип идентификатора типа, основываясь только на типах, присутствующих в выражении.
    // без проверки в рантайме.
    // dynamic_cast используется для безопасного приведения типов в иерархии классов при наличии полиморфизма.
    Matrix& A = *(p->A);
    Row& b = *(p->b);
    int sR = p->startRow;
    int eR = p->endRow;
    int cC = p->currentColumn;
    for (int i = sR; i < eR; ++i) {
        double coef = A[i][cC] / A[cC][cC];
        for (int j = cC; j < A[i].size(); ++j) {
            A[i][j] -= coef * A[cC][j];
        }
        b[i] -= coef * b[cC];
    }
    return nullptr;
}

void GaussianElimination(Matrix& A, Row& b, int maxThreads) {
    size_t n = A.size();
    vector<pthread_t> threads(maxThreads);
    vector<ThreadParam> params(maxThreads);

    for (int i = 0; i < n; ++i) {
        // Нормализация текущей строки
        for (int k = i + 1; k < n; ++k) {
            A[i][k] /= A[i][i];
        }
        b[i] /= A[i][i];
        A[i][i] = 1.0;

        // создание и запуск потоков для текущего шага нулирования:
        int rowsPerThread = (n - i - 1) / maxThreads; 
        if (maxThreads >= n) {
            rowsPerThread = 1;
        }
        for (int k = 0; k < maxThreads; ++k) {
            int startRow = i + 1 + k * rowsPerThread;
            int endRow = (i == maxThreads - 1) ? n : startRow + rowsPerThread;
            // условие ? если_верно : если_неверно

            params[k] = {&A, &b, startRow, endRow, i};
            if (startRow < n) {
                if(pthread_create(&threads[k], NULL, ThreadFunc, &params[k])) {
                    cerr << "thread creating error!" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        // синхронизация потоков:
        for (int k = 0; k < maxThreads; ++k) {
            if (params[k].startRow < n) {
                pthread_join(threads[k], NULL);
            }
        }
    }

    // обратный ход (может быть выполнен в один поток, чаще всего быстрый процесс)
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= A[i][j] * x[j];
        }
    }
    /*
    // вывод результатов:
    for (double xi : x) {
        cout << xi << " ";
    }
    cout << endl;
    */
}