#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>

void *battle();
void *standby();
void *shop();
void *bath();
void *hunger();
void *hygiene();
void *blood();
int check();
void game();
void *menu();

char mname[100];
int hunger_stat = 200;
int hygiene_stat = 100;
int health_stat = 10;
int my_fishnships;
int enemy = 100;

int *fish_n_ships;

int counter_bath = 20;
int flagbath = 0;
int flags;
int flagg;
int wat;
int this;

int life;
int winit;
int tilldie;

pthread_t stnby, shp, bttl, threadbath, eat;
pthread_t hungert, healtht, hygienet, menushp;

int main()
{
  flags = 0;
  my_fishnships = 0;
  flagg = 0;

  system("clear");
  printf("Welcome To Monster Dungeon\n");
  printf("==========================\n");
  printf("\nplease enter your monster name : ");
  scanf("%s", mname);
  system("clear");
  printf("\n------------------------------------\n");
  printf("          Welcome, %s!\n", mname);
  printf("     -- Have fun, Byte back! :) --\n\n");

  pthread_create(&hungert, NULL, hunger, NULL);
  pthread_create(&hygienet, NULL, hygiene, NULL);
  pthread_create(&healtht, NULL, blood, NULL);


  while(1){
    while(flags == 1){ }

    pthread_create(&stnby, NULL, standby, NULL);
    pthread_join(stnby, NULL);
    // scanf("%d", &wat);

    if(wat == 1 ){
      system("clear");
      if(my_fishnships == 0){
        printf("not enough food :(\n\n");
      }
      else{
          hunger_stat += 15;
          my_fishnships -= 1;
      }
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
      flags = 1;
      system("clear");
      // printf("battle here\n");
      pthread_create(&bttl, NULL, (void *) battle, NULL);
      pthread_join(bttl, NULL);
      // printf("hmm\n");
      flags = 0;
    }
    else if(wat ==4){
      flags = 1;
      system("clear");
      pthread_create(&shp, NULL, (void *) shop, NULL);
      pthread_join(shp, NULL);
    }
    else if(wat == 5){
      printf("               -- Game Over --\n");
      exit(1);
    }

  }

  return 0;
}

void *blood()
{
  while(health_stat > 0 && flags == 0){
    // printf("blood\n");
    int number_of_seconds = 1000;
    int i;
      for (i = 0; i < 10; i++) {
        int milli_seconds = 3000 * number_of_seconds;
        clock_t start_time = clock();
        while (clock() < start_time + milli_seconds){
          while(flags == 1){ i = 0; }
        }
      }
        health_stat += 5;
      if(flagg = 0){
        system("clear");
        pthread_create(&stnby, NULL, standby, NULL);
        pthread_join(stnby, NULL);
        flagg = 1;
      }


    }

}

void *hunger()
{
  while(hunger_stat > 0 && hunger_stat <= 200 && flags == 0){
    int number_of_seconds = 1000;
    int w;
      for (w = 0; w < 10; w++) {
        int milli_seconds2 = 3000 * number_of_seconds;
        clock_t start_time2 = clock();
        while (clock() < start_time2 + milli_seconds2){
          while(flags == 1){ w = 0; }
        }
      }
        hunger_stat -= 5;
        check();
      if(flagg == 0){
        system("clear");
        pthread_create(&stnby, NULL, standby, NULL);
        pthread_join(stnby, NULL);
        flagg =1;
      }

    }

}

void *hygiene()
{
  while(hygiene_stat > 0 && flags == 0){
    // printf("hygiene --\n");
    int number_of_seconds = 1000;
    int r;
      for (r = 0; r < 30; r++) {
        int milli_seconds3 = 3000 * number_of_seconds;
        clock_t start_time3 = clock();
        while (clock() < start_time3 + milli_seconds3){
          while(flags == 1){r = 0;}
        }
      }
        hygiene_stat -= 10;
        check();
      if(flagg == 0){
        system("clear");
        pthread_create(&stnby, NULL, standby, NULL);
        pthread_join(stnby, NULL);
        flagg = 1;
      }

    }

}

void *bath()
{
    int number_of_seconds = 1000;
    int y;
    counter_bath = 20;
      for (y = 0; y < 20; y++) {
        flagg = 1;
        int milli_seconds4 = 4000 * number_of_seconds;
        clock_t start_time4 = clock();
        while (clock() < start_time4 + milli_seconds4){
          while(flags == 1){ y = 0;}
        }
        counter_bath--;
        if(counter_bath < 0){ break; }
        system("clear");
        pthread_create(&stnby, NULL, standby, NULL);
        // pthread_join(stnby, NULL);
        // printf("in %d\n", counter_bath);
      }
      // printf("bath is ready\n");
      flagbath = 0;
      // system("clear");
      // pthread_create(&stnby, NULL, standby, NULL);
      // pthread_join(stnby, NULL);
      flagg = 0;
}


void *standby()
{
  printf("\n\nStandby Mode\n");
  printf("-----------------\n");
  printf("Health : %d\n", health_stat);
  printf("Hunger : %d\n", hunger_stat);
  printf("Hygiene : %d\n", hygiene_stat);
  printf("Food left : %d\n", my_fishnships);

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
  printf("5. Exit\n\n");
  scanf("%d", &wat);

}

int check()
{
  if (hunger_stat <= 0){
    printf("too hungry, you die :(\n");
    exit(0);
  }
  if (hygiene_stat <= 0){
    printf("too dirty, you die :(\n");
    exit(0);
  }
}

void *battle()
{
  tilldie = 1;
  life = health_stat;

  while(tilldie == 1 && enemy > 0 && life > 0){
    int e = rand() % 2;

    // printf("health stat : %d\n", health_stat);

    printf("\n\nBattle Mode\n");
    printf("-----------------\n");
    printf("Monster's Health : %d\n", life);
    printf("Enemy's Health : %d\n", enemy);
    printf("Choices\n");
    printf("1. Attack\n");
    printf("2. Run\n");
    printf("3. Leave\n");
    scanf("%d", &winit);

    if(winit == 1){
      printf("--  Attack the enemy!  --\n");

      if(e+1 == 1){
        printf("  --  Enemy Attacking!  --\n");
        life -= 20;
        enemy -= 20;
        game();
      }
      else if(e+1 == 2){
        printf("-- Enemy run, attack failed  --\n");
      }
    }
    else if(winit == 2){
      printf("-- Run from enemy  --\n");

      if(e+1 == 1){
        printf("  --  Enemy Attacking, you survived!  --\n");
      }
      else if(e+1 == 2){
        printf("--  You both run  --\n");
      }
    }
    else if(winit == 3){
      tilldie = 0;
      enemy = -1;
      life = -1;
    }

  }

}

void game()
{
  if(life <= 0){
    printf("Boo, you lose\n");
    system("clear");
    tilldie = 0;
  }
  else if(enemy <= 0){
    printf("Victory!\n");
    system("clear");
    tilldie = 0;
  }
}

void *shop()
{
  int number_of_seconds = 1000;
  key_t key = 1234;
  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  fish_n_ships = shmat(shmid, NULL, 0);
  flags = 1;
  int k;

  while(flags == 1){
    // while(1){
      // system("clear");
      // printf("\n\nShop Mode\n");
      // printf("-----------------\n");
      // printf("Shop food stock : %d\n", *fish_n_ships);
      // printf("Your food stock : %d\n", my_fishnships);
      // printf("Choices\n");
      // printf("1. Buy\n");
      // printf("2. Back\n");
    // }
      pthread_create(&menushp, NULL, menu, NULL);
      scanf("%d", &this);
      if(fish_n_ships < 0 || my_fishnships < 0){
        flags = 0;
      }
      if(this == 1){
        *fish_n_ships -= 1;
        my_fishnships += 1;
        // system("clear");
        // menu();
      }
      else if(this == 2){
        flags = 0;
        break;
      }
    }
  // }
  system("clear");
}

void *menu()
{
  // while(1){
    system("clear");
    printf("\n\nShop Mode\n");
    printf("-----------------\n");
    printf("Shop food stock : %d\n", *fish_n_ships);
    printf("Your food stock : %d\n", my_fishnships);
    printf("Choices\n");
    printf("1. Buy\n");
    printf("2. Back\n");
    sleep(1);
  // }
}
