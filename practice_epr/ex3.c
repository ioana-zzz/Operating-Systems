#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int childpid;

void child_handler(int sig)
{printf("CHILD: I have been killed\n");
 exit(0);

}

void parent_handler(int sig)
{printf("PARENT: I have been killed\n");
 kill(childpid, SIGUSR1);
 wait(0);
 exit(0);
 }

void zombie(int sig)
{wait(0);
}


int main()
{int childpid = fork();
 if ( childpid == - 1){perror("fork"); exit(1);} 
   else if (childpid==0){signal(SIGUSR1, child_handler);
                         while(1)
                         {printf("CHILD: %d .........\n",getpid());
                          sleep(3);}
                        }
   else{signal(SIGUSR1, parent_handler);
        signal(SIGCHLD, zombie);
        while(1)
           {printf("PARENT: %d ..........\n",getpid());
            sleep(3);
           }
        }

return 0;


}
