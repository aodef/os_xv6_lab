#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAXSIZE 16

int main(int argc,char* argv[]){
	char buf[MAXSIZE];
    char* nargv[MAXARG];
    
    int i;
    for (i=1;i<argc;i++){
        nargv[i-1] = argv[i];
    }

	char c,*p = buf;
	while(read(0,&c,1) != 0){
		if(c == '\n'){
			//如果是换行符则开一个子进程执行命令
			*p = '\0';
			nargv[i-1] = buf;//作为参数传入
			if(fork() == 0){
				exec(nargv[0],nargv);
				exit(0);
			}
			p = buf;
            wait(0);
		}
		else{
			*p = c;
            p++;
        }
	}	
	exit(0);
    

}