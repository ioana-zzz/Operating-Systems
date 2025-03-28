#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main()
{FILE* fd = fopen("./text2","r");
 if(fd == NULL){perror("open file");exit(1);}
 
 int p2c[2];
 if(pipe(p2c) < 0){perror("pipe");exit(1);}

 int pid = fork();
 if ( pid == -1){perror("fork");exit(1);}
 else if(pid == 0){close(p2c[1]);
                   int ok, n, n1, result;
                   char sign;
                   while(1)
                   {if(read(p2c[0],&ok,sizeof(int)) < 0){perror("read");exit(1);}
                    if(!ok) break;
                    if(read(p2c[0],&sign,sizeof(char)) < 0 || read(p2c[0],&n, sizeof(int)) < 0){perror("read");exit(1);}
                    //printf("%c %d\n",sign,n);
                    n1 = n;
                    if(sign == '+')
                      {result = 0;
                       while(n1){result+= n1%10; n1/=10;}
                      }
                   else{result = 1;
                        while(n1){result*=n1%10; n1/=10;
                       }}
                   printf("%c %d %d\n",sign,n,result);	      
                  }  
                 close(p2c[0]);exit(0);}
 else {close(p2c[0]);
       int n,s,ok = 1;
       char sign;
        while(1){
                   s = fscanf(fd,"%c %d\n",&sign,&n);
                   if( s <= 0) ok = 0;
                   if(write(p2c[1],&ok,sizeof(int)) < 0 ){perror("write");exit(1);}
                   if(ok == 0) break;
                   if (write(p2c[1],&sign,sizeof(char)) < 0 || write(p2c[1],&n,sizeof(int)) < 0){ perror("write");exit(1);}
                 }

      close(p2c[1]);fclose(fd);
      wait(0);}
return 0;

}
