#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

// READ - 0
// WRITE - 1

#define MAX_LEN 100

int main() {
    string filename;
    cout << "enter the output file: ";
    getline(cin, filename);
    if (filename.empty()) {
        perror("getline error");
        exit(EXIT_FAILURE);
    }

    int fd1[2], fd2[2];
    if ((pipe(fd1) == -1) || (pipe(fd2) == -1)) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    
    if (pid < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(fd1[1]);
        close(fd2[0]);
        if (dup2(fd1[0], fileno(stdin)) != 0) {
            perror("dup2 error: child, stdin");
            exit(EXIT_FAILURE);
        }
        if (execl("./child", "child", filename.c_str(), NULL) == -1) {
            perror("execl failure");
            exit(EXIT_FAILURE);
        }
    } else {
        close(fd1[0]);
        close(fd2[1]);
        if (write(fd1[1], &fd2[1], sizeof(float)) != sizeof(float)) {
            perror("write failure");
            exit(EXIT_FAILURE);
        }
        while (true) {
            string command;
            float num;
            float input_arr[MAX_LEN];
            int i = 0;
            getline(cin, command);
            stringstream ss(command, ios_base::in);
            while (command != "exit" && (ss >> num)) {
                if (i >= MAX_LEN) {
                    cerr << "error: max " << MAX_LEN << " numbers" << endl;
                    exit(EXIT_FAILURE);
                }
                input_arr[i] = num;
                ++i;
            }

            if (command == "exit") {
                int code = -1;
                if (write(fd1[1], &code, sizeof(float)) != sizeof(float)) {
                    perror("writing to pipe failure");
                } 
                break;
            }

            if (write(fd1[1], &i, sizeof(float)) != sizeof(float) ||
                write(fd1[1], input_arr, sizeof(float) * i) != sizeof(float) * i) {
                perror("writing to pipe failure");
                exit(EXIT_FAILURE);
            }
        }
        close(fd1[1]);
        close(fd2[0]);
    }
    return 0;
}
