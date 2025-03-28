#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("wrong no. of args");
        exit(1);
    }

    int n = atoi(argv[1]);
    int p[2], p1[2], nr;
    float s = 0;
    pid_t pid;

    if (pipe(p) == -1 || pipe(p1) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(p[1]);
        close(p1[0]);

        for (int i = 1; i <= n; i++) {
            int x;
            sleep(1);
            read(p[0], &x, sizeof(int));
            printf("%d - CHILD RECEIVED NO. %d\n", i, x);
            s += x;
        }

        s /= n;
        write(p1[1], &s, sizeof(float));

        close(p[0]);
        close(p1[1]);
        exit(0);
    } else {
        // Parent process
        close(p[0]);
        close(p1[1]);

        for (int i = 1; i <= n; i++) {
            nr = rand() % 100;
            printf("%d - PARENT SENT NO. :%d \n", i, nr);
            sleep(1);
            write(p[1], &nr, sizeof(int));
        }

        wait(NULL);

        float rez;
        read(p1[0], &rez, sizeof(float));
        printf("PARENT: THE RESULT IS %.2f\n", rez);

        close(p[1]);
        close(p1[0]);
    }

    return 0;
}

