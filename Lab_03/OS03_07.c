#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void cycle(int c){
for(int i =0; i<c;i++){
sleep(1);
printf("%d. OS03_07 PID: %d\n",i,getpid());
}
}

int main(){
char * const argv[] = {"ps","-ef",0};
printf("Parent process started:\n");
cycle(10);
printf("Parent process ended\n");
printf("Child process started:\n");
execv("./OS03_05_1.out",argv);
exit(0);
}
