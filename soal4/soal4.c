#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void* wat_proc(void *this);
void* zipit(void *tozip);
void* unzipit(void *unzipwat);

int main()
{
  pthread_t thread1, thread2;
  pthread_t thread3, thread4;
  pthread_t thread5, thread6;

  char *list_it1 = "ps aux | head -11 | tail -10 > /home/Penunggu/Documents/FolderProses1/SimpanProses1.txt";
  char *list_it2 = "ps aux | head -21 | tail -10 > /home/Penunggu/Documents/FolderProses2/SimpanProses2.txt";
  char *letszip1 = "zip -r -j /home/Penunggu/Documents/FolderProses1/KompresProses1 /home/Penunggu/Documents/FolderProses1/SimpanProses1.txt";
  char *letszip2 = "zip -r -j /home/Penunggu/Documents/FolderProses2/KompresProses2 /home/Penunggu/Documents/FolderProses2/SimpanProses2.txt";
  char *unzip1 = "unzip /home/Penunggu/Documents/FolderProses1/KompresProses1.zip -d /home/Penunggu/Documents/FolderProses1";
  char *unzip2 = "unzip /home/Penunggu/Documents/FolderProses2/KompresProses2.zip -d /home/Penunggu/Documents/FolderProses2";

  pthread_create(&thread1, NULL, wat_proc, (void *)list_it1);
  pthread_create(&thread2, NULL, wat_proc, (void *)list_it2);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  pthread_create(&thread3, NULL, zipit, (void *)letszip1);
  pthread_create(&thread4, NULL, zipit, (void *)letszip2);

  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);

  printf("Menunggu 15 detik untuk mengekstrak kembali\n");
  sleep(15);
  pthread_create(&thread5, NULL, unzipit, (void *)unzip1);
  pthread_create(&thread6, NULL, unzipit, (void *)unzip2);

  pthread_join(thread5, NULL);
  pthread_join(thread6, NULL);

  return 0;
}

void* wat_proc(void *this)
{
  char *y = (char *)this;
  system(y);
}

void* zipit(void *tozip)
{
  char *x = (char *)tozip;
  char *this = &x[strlen(x)-17];
  if(strcmp(this, "SimpanProses1.txt")){
    system(x);
    system("rm /home/Penunggu/Documents/FolderProses1/SimpanProses1.txt");
  }
  if(strcmp(this, "SimpanProses2.txt")){
    system(x);
    system("rm /home/Penunggu/Documents/FolderProses2/SimpanProses2.txt");
  }
}

void* unzipit(void *unzipwat)
{
  char *z = (char *)unzipwat;
  char *this = &z[strlen(z)-1];
  if(strcmp(this, "1")){
    system(z);
  }
  if(strcmp(this, "2")){
    system(z);
  }
}
