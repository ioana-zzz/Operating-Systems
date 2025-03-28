#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv)
{if(argc == 1){printf("Wrong no. of args");exit(1);}

 for (int i = 1 ; i < argc ; i ++){
 int p1[2],p2[2];
 if( pipe(p1) < 0 || pipe(p2) < 0) {perror("pipe");exit(1);}
 
 int pid = fork();
 if( pid == -1) {perror("fork");exit(1);}
 else if(pid == 0)
    { char* str = malloc(10);
      int ltr = 0, dgt = 0, sp = 0; 
      if( read(p1[0],str,10 ) < 0){perror("read");exit(1);}
      for( int j = 0 ; j < strlen(str) ; j++)
         { if ( (str[j] <= 'z' && str[j] >= 'a') || (str[j] <= 'Z' && str[j] >= 'A') )
                    ltr++;
          else if( str[j] >= '0' && str[j] <= '9')
                    dgt++;
          else sp++;}      
      if( write(p2[1],&ltr,sizeof(int) ) < 0){perror("write");exit(1);}
      if( write(p2[1],&dgt,sizeof(int) ) < 0){perror("write");exit(1);}
      if( write(p2[1],&sp,sizeof(int) ) < 0){perror("write");exit(1);}
      free(str);
      close(p1[0]);close(p2[1]);
      exit(0); }

 else{close(p1[0]);close(p2[1]);
      int letters = 0, digits = 0, special = 0;
      if( write(p1[1],argv[i],10 ) < 0){perror("write");exit(1);}
      if( read(p2[0],&letters,sizeof(int) ) < 0){perror("read");exit(1);}
      if( read(p2[0],&digits,sizeof(int) ) < 0){perror("read");exit(1);}
      if( read(p2[0],&special,sizeof(int) ) < 0){perror("read");exit(1);}
      printf("argv[%d] - LETTERS: %2d  DIGITS: %2d  SPECIAL CHARACTERS: %2d\n",i,letters,digits,special);
      wait(0);
      close(p2[1]);close(p2[0]);
} }




return 0;}
