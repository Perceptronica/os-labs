#include <iostream>
#include <cmath>

extern "C" float Derivative(float A, float deltaX);
extern "C" int GCD(int A, int B);

float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A - deltaX))/(2 * deltaX);
}

int GCD(int A, int B) {
    for (int d = std::min(A, B); d > 0; --d) {
        if (A % d == 0 && B % d == 0) {
            return d;
        }
    }
    return 1;
}