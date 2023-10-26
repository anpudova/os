#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctime>
#include <random>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sleep_time>\n";
        return 1;
    }

    int sleep_time = std::atoi(argv[1]);
    srand(time(nullptr));

    pid_t pid = getpid();
    pid_t parent_pid = getppid();

    std::cout << "Child[" << pid << "]: I am started. My PID " << pid << ". Parent PID " << parent_pid << ".\n";
    sleep(sleep_time);
    std::cout << "Child[" << pid << "]: I am ended. PID " << pid << " Parent PID " << parent_pid << ".\n";
    
    int exit_code = (rand() + pid) % 2;
    _exit(exit_code);

    return 0;
}