#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>
#include <stdbool.h>
#include <stddef.h>


int main(int argc, char *argv[])
{
 int fd = open("OS09_05.txt",O_RDONLY);
 if(fd == 1){
  perror("Error opening file");
  return 1;
 }
 char buffer[128];
 ssize_t bytesRead;
 // чтение первых 10 байт
 lseek(fd,0,SEEK_SET); //  ставим пзицию в начало
 bytesRead = read(fd,buffer,10);
 buffer[bytesRead] = '\0';
 printf("[10 bytes]: %s\n",buffer);
 
 // Чтение следующих 10 байт
 lseek(fd,10,SEEK_CUR); // смещение на 10 от текущей позиции;
 bytesRead = read(fd,buffer,10);
 buffer[bytesRead] = '\0';
 printf("[Next 10 bytes]: %s\n",buffer);
 
 // чтение последних 30 байт от конца файла
 lseek(fd,-22,SEEK_END);
 bytesRead = read(fd,buffer,30);
 buffer[bytesRead] = '\0';
 printf("[End 30 bytes]: %s\n",buffer);

 close(fd);
 return 0;
}
