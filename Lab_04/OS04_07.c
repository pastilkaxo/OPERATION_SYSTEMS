#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void* OS04_07_T1(void* arg){
 pid_t pid = getpid();
 for(int i = 1; i < 75; i++){
  sleep(1);
  printf("OS04_07_T1: %d-%d\n",pid,i);
 }
 pthread_exit("OS04_07_T1 Thread");
}

int main(){
 pthread_t t1;
 void* thread_result;
 pid_t pid = getpid();
 printf("main: PID = %d \n",pid);
 int res = pthread_create(&t1,NULL,OS04_07_T1,NULL);

 for(int i = 1;i < 100; i++){
  sleep(2);
  printf("Main: %d-%d\n",pid,i);
 }
 int status = pthread_join(t1,(void**)&thread_result);
 exit(0);

}
