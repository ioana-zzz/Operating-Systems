#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int globalpid;

int main(int argc, char** argv)
{if (argc!=2){perror("argv"); exit(1);}
 printf("PARENT: %d\n",getpid());
 globalpid = getpid();
 int n = atoi(argv[1]);
 for ( int i = 0 ; i < n ; i ++)
 {
 int pid = fork();
 if ( pid == - 1){perror("fork");exit(1);}
   else if ( pid == 0)
       {printf("I am child %d, my pid - %d, my parent's pid - %d\n",i,getpid(),getppid());
       fork(); 
       exit(0);}
   else{wait(0);
     if(getpid()!=globalpid)   exit(0);}
}
          


return 0;
}
