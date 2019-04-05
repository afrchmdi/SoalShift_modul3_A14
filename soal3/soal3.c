#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
#include<sys/wait.h>

int this;
int WakeUp_Status = 0;
int Spirit_Status = 100;

void to_do();
void *WakeUp();
int check();
void *Sleep_pls();
void *delay();

int flag;
int flag2;
int flag3;
int countwake;
int countgn;
pthread_t thread1, thread2, thread3;

int main()
{

  int wake_agmal;
  int gn_iraj;
  countwake = 0;
  countgn = 0;

  flag = 0;
  flag2 = 0;
  flag3 = 0;
  this = 0;
  printf("Stat Agmal: %d\n", WakeUp_Status);
  printf("Stat Iraj : %d\n", Spirit_Status);
  printf("--------------------\n");
  while (1){

        this = 0;
        while (flag == 1) {}
        to_do();
        scanf("%d", &this);

        if(this == 1)
        {
          printf("\nStat Agmal: %d\n", WakeUp_Status);
          printf("Stat Iraj : %d\n", Spirit_Status);
          printf("--------------------\n");
        }
        if(this == 2 && flag2 == 0)
        {
          flag = 1;
          countwake++;
          // printf("countwake = %d\n", countwake);
          wake_agmal = pthread_create(&thread2, NULL, WakeUp, NULL);

        }
        else if(this == 3 && flag3 == 0){
          flag = 1;
          countgn++;
          // printf("countgn = %d\n", countgn);
          gn_iraj = pthread_create(&thread3, NULL, Sleep_pls, NULL);
        }
        if(flag3 == 1 && this == 3 || flag2 == 1 && this == 2){
          printf("current fitur is disabled, please choose another option\n");
        }


  }

}

void *delay()
{
    int number_of_seconds = 1000;
    int i;
    for (i = 0; i < 10; i++) {
      int milli_seconds = 1000 * number_of_seconds;
      clock_t start_time = clock();

      while (clock() < start_time + milli_seconds){
        if(countgn != 0){
          flag2 = 1;
        }
        if(countwake != 0){
            flag3 = 1;
        }
      }
    }
    flag3 = 0;
    flag2 = 0;
    countwake = 0;
    countgn = 0;
}

void *WakeUp()
{
    this = 0;
    while (flag == 0){}
    if(countwake == 3){
      printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
      int i;
      pthread_create(&thread1, NULL, (void *) delay, NULL);
    }
      // printf("plus wake\n");
      WakeUp_Status += 15;
      printf("WakeUp_Status = %d\n", WakeUp_Status);
      check();
      flag = 0;
}

void *Sleep_pls()
{
  this = 0;
  while (flag == 0) {}
  if(countgn == 3){
    printf("Agmal Ayo Bangun disabled 10 s\n");
    int i;
    pthread_create(&thread1, NULL, (void *) delay, NULL);
  }
    // printf("min wake\n");
    Spirit_Status -= 20;
    printf("Spirit_Status = %d\n", Spirit_Status);
    check();
    flag = 0;
}

int check(){

  if(WakeUp_Status >= 100)
  {
    printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
    exit(0);
  }
  if(Spirit_Status <= 0)
  {
    printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
    exit(0);
  }
}


void to_do()
{

  printf("\nFitur yang tersedia:\n");
  printf("(1) 'All Status', untuk menampilkan status karakter\n");
  printf("(2) 'Agmal Ayo Bangun!', untuk menambah WakeUp Status karakter Agmal\n");
  printf("(3) 'Iraj Ayo Tidur!', untuk mengurangi Spirit Status karakter Iraj\n");
  printf("-----------------------------------------------------------------------\n");
  printf("Fitur yang ingin dimainkan: ");

}
