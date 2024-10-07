#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void cycle(int c){
for(int i=0;i<c;i++){
sleep(1);
printf("%d. OS03_06 PID: %d\n",i,getpid());
}
}

int main(){
printf("Start child process \n");
system("./OS03_05_1.out");
printf("Finish child Process \n");
printf("Parent process:\n");
cycle(10);
printf("Finished parent process\n");
exit(0);
}
