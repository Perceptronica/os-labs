#include <iostream>
#include <cmath>

extern "C" float Derivative(float A, float deltaX);
extern "C" int GCD(int A, int B);

float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A))/deltaX;
}

int GCD(int A, int B) {
    if (A == 0)
        return B;
    return GCD(B % A, A);
}