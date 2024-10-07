#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = getpid();
    for (int i = 1; i < 50; i++) {
        sleep(1);
        printf("%d. PID: %d\n", i, pid);
    }
    exit(0);
}

