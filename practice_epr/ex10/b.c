#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{


 int fr = open("./fifo1",O_RDONLY);
 
 int fw = open("./fifo2",O_WRONLY); 
 if ( fw < 0 || fr < 0 ){perror("open fifo");exit(1);}
 
int n = 100;

 while (n >= 5)
{if(read(fr,&n,sizeof(int)) < 0){perror("read"); exit(1);}
 printf("B HAS RECEIVED : %d\n",n);
 n/=2;
 printf("B HAS WRITTEN : %d\n",n);
 if( write(fw, &n, sizeof(int)) < 0){perror("write"); exit(1);}
}

close(fw);close(fr);
return 0;

}
