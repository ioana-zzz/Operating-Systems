#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{if(mkfifo("./fifo1",0644)<0){perror("mkfifo");exit(1);}
 if(mkfifo("./fifo2",0644)<0){perror("mkfifo");exit(1);}

 int fr = open("./fifo2",O_RDONLY);
 int fw = open("./fifo1",O_WRONLY);

 if(fr < 0 || fw < 0){perror("open fifo"); exit(1);}

 write(fw, &argc, sizeof(int));
 char* sr = malloc(15);
 char* sf = malloc(15);


 for ( int i = 1 ; i < argc ; i++)
  {write(fw,argv[i],strlen(argv[i])+1);
   read(fr, sr, 15);
   printf("A RECEIVED : %s\n",sr);
   strcat(sf,sr);}
  close(fw);
  close(fr);

 

printf("PROCESS A : %s\n" , sf);

free(sr); free(sf);
unlink("./fifo1");
unlink("./fifo2");



return 0;}
