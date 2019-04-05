#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void *battle();
void *standby();
void *shop();
void *bath();
void *hunger();
void *hygiene();
void *blood();

char mname[100];
int hunger_stat = 200;
int hygiene_stat = 100;
int health_stat = 300;
int food_stat = 0;

int counter_bath = 20;
int flagbath = 0;
int wat;

int main()
{
  system("clear");
  printf("Welcome To Monster Dungeon\n");
  printf("==========================\n");
  printf("\nplease enter your monster name : ");
  scanf("%s", mname);

  printf("\n------------------------------------\n");
  printf("     Welcome, %s!\n", mname);
  printf("-- Have fun, Byte back! :) --\n\n");

  pthread_t stnby, shp, bttl, threadbath, eat;
  pthread_t hungert, healtht, hygienet;

  pthread_create(&hungert, NULL, hunger, NULL);
  pthread_create(&hygienet, NULL, hygiene, NULL);
  pthread_create(&healtht, NULL, blood, NULL);

  while(1){
    pthread_create(&stnby, NULL, standby, NULL);
    pthread_join(stnby, NULL);
    scanf("%d", &wat);
    if(wat == 1){
      system("clear");
      hunger_stat += 15;
      // printf("feed me\n");
    }
    else if(wat == 2){
      system("clear");
      if (flagbath == 0){
        flagbath = 1;
        hygiene_stat += 30;
        pthread_create(&threadbath, NULL, (void *) bath, NULL);
      }
      else{
        printf("dude, you just take a bath earlier..\n");
      }

    }
    else if(wat == 3){
      system("clear");
    }
    else if(wat == 4){
      system("clear");
    }
    else if(wat == 5){
      printf("               -- Game Over --\n");
      exit(1);
    }


    if (hunger_stat <= 0){
      printf("too hungry, you die :(\n");
      return 0;
    }
    if (hygiene_stat <= 0){
      printf("too dirty, you die :(\n");
      return 0;
    }

  }
  pthread_join(hygienet, NULL);
  pthread_join(hungert, NULL);
  pthread_join(eat, NULL);
  pthread_join(threadbath, NULL);

  return 0;
}

void *blood()
{
  while(health_stat > 0){
    int number_of_seconds = 1000;
    int i;
      for (i = 0; i < 10; i++) {
        int milli_seconds = 3000 * number_of_seconds;
        clock_t start_time = clock();
        while (clock() < start_time + milli_seconds){
        }
      }
      health_stat += 5;
      // printf("health stat: %d\n", health_stat);
    }

}

void *hunger()
{
  while(hunger_stat > 0){
    int number_of_seconds = 1000;
    int i;
      for (i = 0; i < 10; i++) {
        int milli_seconds2 = 3000 * number_of_seconds;
        clock_t start_time2 = clock();
        while (clock() < start_time2 + milli_seconds2){
        }
      }
      hunger_stat -= 5;
      // printf("hunger stat: %d\n", hunger_stat);
    }

}

void *hygiene()
{
  while(hygiene_stat > 0){
    int number_of_seconds = 1000;
    int i;
      for (i = 0; i < 30; i++) {
        int milli_seconds3 = 2000 * number_of_seconds;
        clock_t start_time3 = clock();
        while (clock() < start_time3 + milli_seconds3){
        }
      }
      hygiene_stat -= 10;
      // printf("hygiene stat : %d\n", hygiene_stat);
    }

}

void *bath()
{
    int number_of_seconds = 2000;
    int i;
    counter_bath = 20;
      for (i = 0; i < 20; i++) {
        int milli_seconds4 = 1500 * number_of_seconds;
        clock_t start_time4 = clock();
        while (clock() < start_time4 + milli_seconds4){
        }
        counter_bath--;
      }
      flagbath = 0;
}


void *standby()
{
  printf("\n\nStandby Mode\n");
  printf("-----------------\n");
  printf("Health : %d\n", health_stat);
  printf("Hunger : %d\n", hunger_stat);
  printf("Hygiene : %d\n", hygiene_stat);
  printf("Food left : %d\n", food_stat);
  
  if(flagbath == 0){
    printf("Bath is ready!\n");
  }
  else{
    printf("Bath will be ready in %d s\n", counter_bath);
  }
  printf("Choices : \n");
  printf("1. Eat\n");
  printf("2. Bath\n");
  printf("3. Battle\n");
  printf("4. Shop\n");
  printf("5. Exit\n");
  printf("your choice: ");

}

void *battle();

void *shop();
