#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char** argv)
{if (argc!=3){perror("wrong no. of args");
              exit(1);
             }

 int n = atoi(argv[1]);
 for ( int i = 2 ; i <= n/2 ; i ++)
  { int pid = fork();
    if(pid == -1){ perror("fork");
                   exit(1);
                  }
    else if ( pid == 0 ) {int numere[n+1],x;
                          for(int j=1;j<=n;j++)numere[j]=0;
                          FILE* fd = fopen(argv[2],"r");
                          while(fscanf(fd,"%d",&x) == 1)
                                numere[x]=x;

                          numere[1]=0;
                          fclose(fd);
 
                          for ( int j = 2 ; j <= n/i ; j ++)
                                numere[j*i]=0;
                          fd = fopen(argv[2],"w");
                          for( int j = 1; j <= n ;j ++)
                               if (numere[j]) 
                                  fprintf(fd,"%d ",j);
                          fclose(fd);
                          exit(0);
                         }
   wait(NULL);}
   return 0;
  }
 
