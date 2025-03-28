#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{if ( argc == 1){perror("not enough arguments"); exit(1);}
 int pid = fork();
 if ( pid == 0 ){execvp(argv[1],argv+1);
                 
                }
  else {wait(0);
        }

return 0;}

