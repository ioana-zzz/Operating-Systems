#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main()
{FILE* fd = fopen("./text", "r");
 if( fd == NULL){perror("open file");exit(1);}

 int p2c[2];
 if( pipe(p2c) < 0){perror("pipe");exit(1);}

 int pid = fork();
 if(pid == -1){perror("fork");exit(1);}
 else if( pid == 0){close(p2c[1]);
       int a,b,res, ok = 1;
       char sign;
       while(1){
       if(read(p2c[0],&ok,sizeof(int)) < 0 || read(p2c[0],&sign,sizeof(char)) < 0 ||read(p2c[0],&a,sizeof(int)) < 0 || read(p2c[0],&b,sizeof(int)) < 0){perror("write");exit(1);}
       if(!ok) break;
        if(sign == '+')
               res = a+b;
        else res = a - b;
        printf("%d %c %d = %d\n",a,sign,b,res);}
        close(p2c[0]);
        exit(0);    
 }
 else{int ok = 1, a, b;
      close(p2c[0]);
      char sign;
      while(1)
       {int nr = fscanf(fd,"%c %d %d\n",&sign,&a,&b);
        if( nr <= 0)
            ok = 0;
        if(write(p2c[1],&ok,sizeof(int)) < 0 || write(p2c[1],&sign,sizeof(char)) < 0 || write(p2c[1],&a,sizeof(int)) < 0 || write(p2c[1],&b,sizeof(int)) < 0)
              {perror("write");exit(1);}
       
       }
      close(p2c[1]);fclose(fd);
      wait(0);
      }
return 0;
}
