# SoalShift_modul3_A14

Soal Shift Modul 3
1. [Soal 1](#1-soal-1)
2. [Soal 2](#2-soal-2)
3. [Soal 3](#3-soal-3)
4. [Soal 4](#4-soal-4)
5. [Soal 5](#5-soal-5)

### 1. Soal 1
##### Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
##### Contoh:<br> ./faktorial 5 3 4<br>3! = 6<br>4! = 24<br>5! = 120

```sh
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX 500

void order_it(int hmany, char *wat[]);
void* factor_this(void *arg);
int multiply(int x, int this[], int resc);

int thisint[100];
int flag = 0;

int main(int argc, char *argv[])
{
  order_it(argc, argv);
  int x;
  // for(x=0; x<argc-1; x++)
  // {
  //   printf("%d\n", thisint[x]);
  // }

  pthread_t tid[argc-1];
  int thr;
  int i, j;
  for(i=0;i<argc-1;i++){
    flag = 0;
    thr=pthread_create(&(tid[i]), NULL, factor_this, (void*)&i);
    while (flag!=1){ }
  }
  for(j=0;j<argc-1;j++)
  {
    pthread_join(tid[j],NULL);
  }
  return 0;

}

void* factor_this(void *arg)
{
  int this[MAX];
  flag = 0;
  int *x=arg;
  this[0] = 1;
  int res_size  = 1;
  printf("%d! = ", thisint[*x]);
  for(int i=2;i<=thisint[*x];i++)
  {
    res_size = multiply(i, this, res_size);
  }
  int a;
  for (a=res_size-1; a>=0; a--)
  {
    printf("%d", this[a]);
  }
  printf("\n");

  flag = 1;
}

int multiply(int x, int this[], int resc)
{
  int carry = 0;
  int k;
  for(k = 0; k < resc; k++)
  {
    int prod = this[k] * x + carry;
    this[k] = prod % 10;
    carry = prod/10;
  }
  while(carry)
  {
    this[resc] = carry % 10;
    carry = carry / 10;
    resc++;
  }
  return resc;
}


void order_it(int hmany, char *wat[])
{
  int x, z;

  int tmp;
  int chtoint;

  for(x=1; x<hmany; x++)
  {
      // printf("char : %s\n", wat[x]);
      chtoint = atoi(wat[x]);
      thisint[x-1] = chtoint;
      // printf("int %d\n", thisint[x-1]);
  }

  for(x=0; x<hmany-1; x++)
  {

    for(z=x+1; z<hmany-1; z++)
    {
      if(thisint[x] > thisint[z])
      {
        tmp = thisint[x];
        thisint[x] = thisint[z];
        thisint[z] = tmp;
      }
    }
  }
}

```



3.

```sh
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

```
