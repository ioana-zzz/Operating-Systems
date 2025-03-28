#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{int p12[2],p21[2],n1=0,n2=0;

 pipe(p12);pipe(p21);

 int pid1 = fork();
 if (pid1 == 0){close(p21[1]);close(p12[0]);
                while(n1 != 10){n1 =1 + rand() % 10; 
                         write(p12[1],&n1,sizeof(int));
                         printf("CHILD 1 SENT : %d\n",n1);
                         if( n1 == 10)break;
                         read(p21[0],&n1,sizeof(int));
                         printf("CHILD 1 RECEIVED : %d\n",n1);
                         }
                 close(p12[1]);close(p21[0]); exit(0);
               }

 int pid2 = fork();
 if(pid2 == 0){close(p12[1]);close(p21[0]);
                while(n2 != 10){
                         
                         read(p12[0],&n2,sizeof(int));
                         printf("CHILD 2 RECEIVED : %d\n",n2);
                         if ( n2 == 10)break;
                         n2 =1 + rand() % 10;
                         write(p21[1],&n2,sizeof(int));
                         printf("CHILD 2 SENT : %d\n",n2);
                         }
                 close(p12[1]);close(p21[0]); exit(0);
               }

wait(0);wait(0);


return 0;}
