#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>
#include <list>

int forkProcess() {
    pid_t child_pid = fork();
    if (child_pid > 0) {
        std::cout << "Parent[" << getpid() << "]: I ran children process with PID " << child_pid << ".\n";
    } else {
        int rand_num = (rand() + child_pid) % 6 + 5; 
        execlp("./child", "child", std::to_string(rand_num).c_str(), nullptr);
    }
    return child_pid;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <fork_count>\n";
        return 1;
    }

    int fork_count = std::atoi(argv[1]);
    srand(time(nullptr)); 

    std::list<pid_t> processes;
    for (int i = 0; i < fork_count; i++) {
        processes.push_back(forkProcess());
    }
    while (!processes.empty()) {
        int status;
        pid_t child_pid = wait(&status);
        if (child_pid > 0) {
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                std::cout << "Parent[" << getpid() << "]: Child with PID " << child_pid << " terminated. Exit Status " << exit_code << ".\n";
                if (exit_code != 0) {
                    processes.push_back(forkProcess());
                }
                processes.remove(child_pid);
            }
        }
    }

    return 0;
}