#include "common.h"

//citim din consola un sir si procesul b elimina pe rand vocalele
 
int main(int argc, char** argv)
{if(mkfifo("./fifo1",0644) < 0 ){perror("mkfifo1");exit(1);}
 if(mkfifo("./fifo2",0644) < 0 ){perror("mkfifo2");exit(1);}

 
 int a2b = open("./fifo1",O_WRONLY);
 int b2a = open("./fifo2",O_RDONLY);
 if( a2b < 0 || b2a <0 ){perror("open fifo");exit(1);}
 

 
 char* str = malloc(100);
 read(0,str,100*sizeof(char));
 printf("from console: %s\n",str);
 

 for(int i = 0; i < 10 ; i++)
{if(write(a2b, str, 100) < 0){perror("write");exit(1);}
 printf("A sent: %s\n",str); 
 if(read(b2a, str, 100) < 0 ){perror("read");exit(1);}
 printf("A received: %s\n",str);
}

printf("final string: %s\n",str);
free(str);

 if( close(a2b) < 0 || close(b2a) < 0){perror("close fifo");exit(1);}
 if(unlink("./fifo1") < 0 || unlink("./fifo2") < 0 ){perror("unlink fifo");exit(1);}

 return 0;

}
