#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{printf("Parent pid - %d\n", getpid());
 if (argc != 2) { perror("argc"); exit(1);}

 int n = atoi(argv[1]);
 for (int i = 0; i < n; i ++)
  {int pid = fork();
   if (pid == 0)
           {
 	    printf("Child %d - MY PID: %d, PARENT PID: %d \n", i+1, getpid(), getppid());
            exit(0);
            }
   else {printf("Parent : Child %d PID: %d \n",i+1, pid);
         }
  }

 for(int i = 0 ; i < n; i ++)
  wait(NULL);
 

return 0; 

}
