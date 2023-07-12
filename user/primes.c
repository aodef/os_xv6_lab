#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAXSIZE 34
void filter(int p[2])
{
    int prime_chosen;
    int stop;
    int i;
    close(p[1]);
    read(p[0],&prime_chosen,4);
    	printf("prime %d\n", prime_chosen);
    stop = read(p[0], &i, 4);
    if(stop){
        int np[2];
        pipe(np);
        int pid=fork();
        if(pid>0){
            close(np[0]);
            if(i%prime_chosen)
                write(np[1], &i, 4);
            while(read(p[0], &i, 4)){
				if(i%prime_chosen)
                    write(np[1], &i, 4);
			}
            close(p[0]);
            close(np[1]);
            wait((int*)0);
        }
        else{
            filter(np);
        }
    }
    exit(0);
}
int main()
{
    int p[2];
    pipe(p); 
    int pid=fork();
    if(pid>0){  //主进程
        close(p[0]);
        for(int i=2;i<=35;i++){
            write(p[1],&i,4);
        }
        close(p[1]);
        wait((int*)0);
        exit(0);
    }
    else{  //子进程
       filter(p);
    }
    return 0;
}