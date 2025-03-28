#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if (mkfifo("./fifo1", 0644) < 0) {
        perror("mkfifo");
        exit(1);
    }
    if (mkfifo("./fifo2", 0644) < 0) {
        perror("mkfifo");
        exit(1);
    }
    int fw = open("./fifo1", O_WRONLY);
    int fr = open("./fifo2", O_RDONLY);
   
    if (fr < 0 || fw < 0) {
        perror("open fifo");
        exit(1);
    }

    write(fw, &argc, sizeof(int));
    char sr[15] = {0}; // Inițializăm cu 0 pentru a preveni comportamentul nedefinit
    char sf[15 * (argc - 1) + 1] ; // Inițializăm cu 0 pentru a preveni comportamentul nedefinit

    for (int i = 1; i < argc; i++) {
        write(fw, argv[i], strlen(argv[i]) + 1);
        if (read(fr, sr, 15) < 0) {
            perror("read");
            exit(1);
        }
        printf("A RECEIVED: %s\n", sr);
        strcat(sf, sr);
    }
    
    close(fw);
    close(fr);

    printf("PROCESS A : %s\n", sf);

    unlink("./fifo1");
    unlink("./fifo2");

    return 0;
}
 
