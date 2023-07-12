#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAXSIZE 16
int main()
{
    int ftc[2],ctf[2];
    char buf[MAXSIZE];
    pipe(ftc);
    pipe(ctf);
    int pid=fork();
    if(pid>0){
        write(ftc[1],"m",MAXSIZE);
        wait((int*)0);
        read(ctf[0],buf,MAXSIZE);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
    else{
        read(ftc[0],buf,MAXSIZE);
        printf("%d: received ping\n", getpid());
        write(ctf[1],buf,MAXSIZE);
        exit(0);
    }

}