#include <iostream>
#include <sstream>
#include "lib1.cpp"

using namespace std;

int main() {
    string command;
    cout << "1 for cos derivative" << endl;
    cout << "2 for GCD(a, b)"<< endl;
    cout << "3 for exit" << endl;
    while (getline(cin, command)) {
        stringstream stream(command);
        int funcNumber;
        stream >> funcNumber;
        if (funcNumber == 1) {
            float a, delta;
            stream >> a >> delta;
            cout << "cos'(" << a << ") = " << Derivative(a, delta) << "\n";
        } else if (funcNumber == 2) {
            int A, B;
            stream >> A >> B;
            cout << "GCD(" << A << ", " << B << ") = " << GCD(A, B) << "\n";
        } else if (funcNumber == 3) {
            return 0;
        } else {
            cout << "enter [0-2] [args]!\n";
        }
    }
    return 0;
}
