#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{if (argc != 2) {perror("wrong no. of args"); exit(1);}
 
 int n = atoi(argv[1]);
 int p[2],p1[2], nr;
 float  s=0;
 int res = pipe(p);
 if ( res == -1){perror("pipe");exit(1);}
 pipe(p1);


int pid = fork();
for ( int i = 1 ; i <= n; i ++)
  {if ( pid == 0 ){close(p[1]);close(p1[0]);
                   int x;
                   sleep(1);
                   read(p[0], &x, sizeof(int));
                   printf("%d - CHILD RECEIVED NO. %d\n",i,x);
                   s+=x;
                   if (i == n) {s/=n;
                                write(p1[1],&s,sizeof(float));
                                }
                  close(p[0]);close(p1[1]);
                   if(i == n)exit(0);
                  
                  }

      else{close(p[0]);close(p1[1]);
           nr = rand() % 100;
           printf("%d - PARENT SENT NO. :%d \n",i,nr);
           sleep(1);
           write(p[1],&nr,sizeof(int));
           if(i == n){wait(0);
                      float rez;
                      read(p1[0],&rez,sizeof(float));
                      printf("PARENT: THE RESULT IS %.0f",rez);
                       
                     }
          close(p[1]);close(p1[0]);}
}
return 0;  
               
} 
