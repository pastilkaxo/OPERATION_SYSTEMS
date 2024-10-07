#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void cycle(int c, char* msg){
for(int i=0;i<c;i++){
sleep(1);
printf("%d. %s PID:%d\n",i,msg,getpid());
}
}

int main()
{
pid_t pid;

switch(pid=fork()){
case -1:
	perror("fork error");
	exit(1);
case 0: 
	cycle(50,"OS03_05_1");
	exit(0);
default:
	cycle(100,"OS03_05");
	wait(NULL);
}

exit(0);
}
