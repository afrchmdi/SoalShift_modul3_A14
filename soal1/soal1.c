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
