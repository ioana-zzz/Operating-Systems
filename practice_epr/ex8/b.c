#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
   
    int fw = open("./fifo2", O_WRONLY);
    int fr = open("./fifo1", O_RDONLY);
    if (fr < 0 || fw < 0) {
        perror("open fifo");
        exit(1);
    }

    int n;
    if (read(fr, &n, sizeof(int)) < 0) {
        perror("read");
        exit(1);
    }

    char s[15] = {0}; // Inițializăm cu 0 pentru a preveni comportamentul nedefinit

    for (int i = 1; i < n; i++) {
        if (read(fr, s, 15) < 0) {
            perror("read");
            exit(1);
        }
        printf("PROCESS B RECEIVED: %s\n", s);
        for (int j = 0; j < strlen(s); j++)
            if (s[j] >= 'A' && s[j] <= 'Z')
                s[j] = s[j] + 'a' - 'A';
        if (write(fw, s, 15) < 0) {
            perror("write");
            exit(1);
        }
    }

    close(fr);
    close(fw);
    return 0;
}
 
