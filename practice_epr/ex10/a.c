#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{if(mkfifo("./fifo1",0644)<0){perror("mkfifo");exit(1);}
 if(mkfifo("./fifo2",0644)<0){perror("mkfifo");exit(1);}

 int fw = open("./fifo1",O_WRONLY);

 int fr = open("./fifo2",O_RDONLY);
 
 if ( fw < 0 || fr < 0 ){perror("open fifo");exit(1);}

 int n = 50 + rand() % 151 ; 
 while(n >= 5)
  {if(n%2 == 1) n++;
   if(write(fw,&n,sizeof(int)) < 0){perror("write"); exit(1);}
   printf("A HAS WRITTEN: %d\n",n);
   if(read(fr,&n,sizeof(int)) < 0){perror("read"); exit(1);}
   printf("A HAS RECEIVED: %d\n", n);
   
  }

close(fw); close(fr);

if( unlink("./fifo1") < 0 || unlink("./fifo2") < 0){perror("unlink fifo");exit(1);}

return 0;

}
