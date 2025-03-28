#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{int p2c[2],c2p[2];

 if( pipe(p2c) < 0 || pipe(c2p) < 0)  {perror("pipe");exit(1);}
 struct timeval tv;
 int pid = fork();
 if(pid == -1 ){perror("fork");exit(1);}
 else if( pid == 0 )
   {close(p2c[1]);close(c2p[0]);
    int k,n;
    FILE* fd = fopen("./text","w");
    if(fd == NULL){perror("open output file");exit(1);}
    while(1){ if(read(p2c[0],&k,sizeof(int)) < 0){perror("read");exit(1);}
        if(read(p2c[0],&n,sizeof(int)) < 0){perror("read");exit(1);}
        printf("child received: k = %d, n = %d\n",k,n);
        if(k ==0 ) break;
        if(k % 2 == 0)
    		{int s = 0, n1 = n;
 		 while(n){s+=n%10;
			  n/=10;
			  }
                 fprintf(fd,"%d %d %d\n",k,n1,s);
                 }
        else {int p = 1, n1 = n;
 	      while(n){p*=n%10;
	               n/=10;
			  }
              fprintf(fd,"%d %d %d\n",k,n1,p);
              }

    }
    close(p2c[0]);close(c2p[1]);fclose(fd);
    exit(0);}

 else{close(p2c[0]);close(c2p[1]);
      int k,n;
    while(1){
    if(scanf("%d",&k) < 0){perror("read");exit(1);}
   
    if(k == 0) break;
    
    if(write(p2c[1],&k,sizeof(int)) < 0){perror("write");exit(1);}
    if(write(p2c[1],&n,sizeof(int)) < 0){perror("write");exit(1);}
    printf("parent sent: k = %d, n = %d\n",k,n);
    gettimeofday(&tv, NULL);
    srandom(tv.tv_usec + tv.tv_sec);
    n = rand() % 1000;
    if(write(p2c[1],&n,sizeof(int)) < 0){perror("write");exit(1);} 
    }
     
     close(p2c[1]);close(c2p[0]);
     wait(0);
 }

return 0;}
