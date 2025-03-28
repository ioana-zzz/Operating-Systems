#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{char vocale[] = "aeiouAEIOU";
 char sir[]="AECdIourOaejiU";
 

 for (int i = 0; i < 10 ; i ++)
   { int p[2];
     if ( pipe(p) == -1){perror("pipe");exit(1);}   
  
     int pid = fork();
     if ( pid == -1){perror("fork");
    		     exit(1);	
                   }
      else if ( pid == 0) {close(p[0]);
                           char* tmp = malloc(strlen(sir));
                           int k = 0;
                           for (int j  = 0;j < strlen(sir); j ++)
                                 if ( vocale[i] != sir[j])
                                     tmp[k++] = sir[j];
                           tmp[k]='\0';
                           printf("%d  - CHILD sent : %s \n", i , tmp);
                           write(p[1],tmp,k+1);
                           //sleep(1);
                           close(p[1]);free(tmp);
                           exit(0);
                          }

     else{close(p[1]);
          //wait(0);
          char* tmp = malloc(strlen(sir));
          //sleep(1);
          read(p[0],tmp,strlen(sir));
          strcpy(sir,tmp);
          printf("%d - PARENT received : %s \n", i , tmp);
          wait(0);free(tmp);
         close(p[0]);}
   }



return 0;
}
