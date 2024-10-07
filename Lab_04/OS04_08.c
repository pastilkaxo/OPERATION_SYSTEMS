#define GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/syscall.h>

void* OS04_08_T1(void* arg){
 pid_t pid = getpid();
 pid_t tid = pthread_self();
 int xtid = syscall(SYS_gettid);
 for(int i = 0; i<75;i++){
  sleep(1);
  printf("%d. OS04_08_T1: PID = %d TID = %d\n",i,pid,xtid);
 }
 pthread_exit("OS04_08_T1 Thread");
}


int main(){
 pid_t pid = getpid();
 pthread_t t1;
 void* thread_result;
 int res = pthread_create(&t1,NULL,OS04_08_T1,NULL);
 for(int i = 1; i< 100; i++){
  if(i == 10){
   printf("Main: Sleeping\n");
   sleep(15);
   printf("Main: Unsleeping\n");
  }
  sleep(2);
  printf("Main: %d-%d\n",pid,i);
 }
 int status = pthread_join(t1,(void**)&thread_result);
 exit(0);
}
