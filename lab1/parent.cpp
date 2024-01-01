#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    int pipe1[2], pipe2[2];
    pid_t child_pid;
    string filename;
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        cerr << "pipe creation failure" << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "enter the output file: ";
    cin >> filename;

    child_pid = fork();
    if (child_pid == -1) {
        cerr << "pid error" << endl;
        exit(EXIT_FAILURE);
    }
    
    if (child_pid == 0) { // child process
        close(pipe1[1]);
        close(pipe2[0]);
        dup2(pipe1[0], STDIN_FILENO); // pipe1[0] - теперь стандартный ввод
        dup2(pipe2[1], STDOUT_FILENO);
        execl("./child", "./child", filename.c_str(), (char*)NULL); // запуск дочернего процесса
        // если execl вернул какое-либо значение, то ошибка
        cerr << "execl failure" << endl;
        exit(EXIT_FAILURE);
    } else { // parent process
        close(pipe1[0]);
        close(pipe2[1]);
        string input;
        while (1) {
            getline(cin, input);
            if (input == "exit") {
                break; // выходим из цикла
            }
            input += '\n'; // добавляем символ новой строки (для передачи в дочерний процесс)
            write(pipe1[1], input.c_str(), input.length()); // отправляем строку в дочерний процесс
        }
        
        close(pipe1[1]); // остановка записи
        int status;
        waitpid(child_pid, &status, 0); // ожидаем завершение дочернего процесса
    }
    
    return 0;
}
