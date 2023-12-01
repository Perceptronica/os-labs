#include <iostream>
#include <sstream>
#include <cstdlib>
#include <dlfcn.h>

using namespace std;

void* handle = NULL; // указатель (для будущего получения доступа
                     // к библиотеке/на библиотеку)
int current_lib = 0;
float (*Derivative)(float A, float deltaX); // указатель на функции
int (*GCD)(int A, int B);
void setLibrary();
void work();
const char* lib_array[] = {"./libd1.so", "./libd2.so"}; // shared library files

int main() {
    setLibrary();
    Derivative = (float(*)(float, float))dlsym(handle, "Derivative");
    GCD = (int(*)(int, int))dlsym(handle, "GCD");
    work();
}

void setLibrary() {
    int lib;
    cout << "Enter library: " << endl;
    cout << "1 - first library" << endl;
    cout << "2 - second library" << endl;
    cin >> lib;
    bool flag = true;
    while (flag) {
        if (lib == 1) {
            current_lib = 0;
            flag = false;
        }
        else if (lib == 2) {
            current_lib = 1;
            flag = false;
        }
        else {
            cout << "enter arg=[1,2]!" << endl;
            cin >> lib;
        }
    }
    handle = dlopen(lib_array[current_lib], RTLD_LAZY); //rtld lazy
    //выполняется поиск только тех символов, на которые есть ссылки из кода
    if (!handle) {
        cerr << "library opening error!" << endl;
        exit(EXIT_FAILURE);
    }
}

void work() {
    string command = "\0";
    while ((getline(cin, command))) {
        stringstream stream(command);
        int funcNumber;
        stream >> funcNumber;
        if (funcNumber == 0) {
            dlclose(handle);
            current_lib = 1 - current_lib;
            handle = dlopen(lib_array[current_lib], RTLD_LAZY);
            if (!handle) {
                cerr << "library opening error!" << endl;
                exit(EXIT_FAILURE);
            } else {
                cout << "library was changed successfully!" << endl;
            }
            Derivative = (float(*)(float, float))dlsym(handle, "Derivative");
            GCD = (int(*)(int, int))dlsym(handle, "GCD");

        } else if (funcNumber == 1) {
            float a, delta;
            stream >> a >> delta;
            cout << "cos'(" << a << ") = " << Derivative(a, delta) << "\n";
        } else if (funcNumber == 2) {
            int A, B;
            stream >> A >> B;
            cout << "GCD(" << A << ", " << B << ") = " << GCD(A, B) << "\n";
        } else if (funcNumber == 3) {
            dlclose(handle);
            exit(0);
        } else {
            cout << "enter [0-3] [args]!\n";
        }
    }
}