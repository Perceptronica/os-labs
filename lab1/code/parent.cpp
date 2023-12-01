#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

const int PATH_MAX = 4096;
const int BUFFER_SIZE = 256;

using namespace std;

enum pipe {READ = 0, WRITE = 1};

int main(void) {
    // читаем, куда писать ответ:
    string filename = "\0";
    cout << "enter output file: ";
    getline(cin, filename);
    if (filename == "" || filename.size() > PATH_MAX) {
        filename = "output.txt";
    }

    int fd1[2], fd2[2];
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        cerr << "pipe error!" << endl;
    }

    int pid = fork(); // создание дочернего процесса
    if (pid < 0) {
        cerr << "fork creating error!" << endl;
    } else if (pid == 0) { // child process
        close(fd1[WRITE]);
        close(fd2[READ]);
        
        if (dup2(fd1[READ], fileno(stdin)) == -1) {
            cerr << "dup2 failure! (1)" << endl;
        }

        close(fd1[READ]);

        if(dup2(fd2[WRITE], fileno(stdout)) == -1) {
            cerr << "dup2 failure! (2)" << endl;
        }

        //close(fd2[WRITE]);

        if (execl("child", "child", filename.c_str(), NULL) != 0) {
            cerr << "execl error!" << endl;
        }
    } else { // parent process
        close(fd1[READ]);
        close(fd2[WRITE]);

        if (dup2(fd1[WRITE], fileno(stdout)) == -1) {
            cerr << "dup2 failure! (3)" << endl;
        }

        bool should_exit = false;
        string input_line;
        
        while(!should_exit) {
            getline(cin, input_line);
            if (input_line.find("exit") != string::npos) { should_exit = true; }
            write(fd1[WRITE], input_line.c_str(), input_line.size() + 1);
            if (should_exit) { break; }
        }

        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            cout << "child exited with status" << WIFEXITED(status) << endl;
        }

        close(fd1[WRITE]);
        close(fd2[READ]);
    }
    return 0;
}