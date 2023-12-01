#ifndef GAUSSIAN
#define GAUSSIAN

#include <iostream>
#include <cstdlib>
#include <vector>
#include <pthread.h>

using namespace std;

typedef vector<double> Row;
typedef vector<Row> Matrix;

struct ThreadParam
{
    Matrix* A;
    Row* b;
    int startRow;
    int endRow;
    int currentColumn;
};


void* ThreadFunc(void* param);
void GaussianElimination(Matrix& A, Row& b, int maxThreads);

#endif