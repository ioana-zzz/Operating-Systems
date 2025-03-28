#include "common.h"

int main()
{char vocale[] = "aeiouAEIOU";

 int a2b = open("./fifo1",O_RDONLY);
 int b2a = open("./fifo2", O_WRONLY);

 if(a2b < 0 || b2a < 0){perror("open fifo"); exit(1);}

 char* str = malloc(100);

 for( int i = 0 ; i < 10 ; i ++)
 {if(read(a2b,str,100) < 0){perror("read");exit(1);}
 printf("B received: %s\n",str);
 char* tmp = malloc(100);
 int k = 0;
 for ( int j = 0; j < strlen(str); j ++)
    if( str[j] != vocale[i] )
      tmp[k++] = str[j];
 tmp[k]='\0';
 if(write(b2a, tmp, 100) < 0 ){perror("write");exit(1);}
 printf("B sent: %s\n",tmp);
 free(tmp);
 }
 free(str);

 if(close(a2b) < 0 || close(b2a) < 0 ){perror("close fifo");exit(1);}


}
