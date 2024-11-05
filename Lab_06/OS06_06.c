#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mx;

void* A(void* arg){
 for(int i=0;i<90;i++){
  if(i==30){
   pthread_mutex_lock(&mx);
  }
  sleep(1);
  printf("%d A: %d\n",i,getpid());
  if(i==60){
   pthread_mutex_unlock(&mx);
  }
 }
 printf("---> A Finished <---");
 pthread_exit("A");
}


void* B(void* arg){
 for(int i=0;i<90;i++){
  if(i==30){
   pthread_mutex_lock(&mx);
  }
  sleep(1);
  printf("%d B: %d\n",i,getpid());
  if(i==60){
   pthread_mutex_unlock(&mx);
  }
 }
 printf("---> B Finished <----");
 pthread_exit("B");
}

int main(){
 pthread_mutex_init(&mx,NULL);
 pthread_t a_th1, a_th2;
 void *r_th1, *r_th2;
 pid_t pid = getpid();
 printf("Main: PID= %d\n",pid);
 int res1 = pthread_create(&a_th1,NULL,A,NULL);
 int res2 = pthread_create(&a_th2,NULL,B,NULL);
 for(int i=0;i<90;i++){
  if(i==30){
   pthread_mutex_lock(&mx);
  }
  sleep(1);
  printf("%d Main: %d\n",i,pid);
  if(i==60){
   pthread_mutex_unlock(&mx);
  }
 }
 printf("---> Main Finished <---");
 int status1 = pthread_join(a_th1,(void**)&r_th1);
 int status2 = pthread_join(a_th2,(void**)&r_th2);
 pthread_mutex_destroy(&mx);
}
