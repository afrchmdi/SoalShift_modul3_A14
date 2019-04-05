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
Pada soal 1, digunakan multithreading untuk menghitung faktorial dari input yang dipassingkan melalui terminal.

`int main(int argc, char *argv[])` Untuk mendapatkan input dari terminal, pada fungsi main diberikan parameter int argc dan char \*argv[]. Dimana argc akan berisi jumlah kata dari inputan dan char \*argv[] berisi pointer array of charyang menampung kata yang diinputkan. Misal, input berupa :
  ./soal1.c 2 7 9 18, maka argc akan bernilai 5, dan char \*argv[] akan berisi {"./soal1", "2", "7", "9", "18"}.
  
`order_it(argc, argv);` Input yang didapat kemudian diurutkan terlebih dahulu dari angka paling kecil ke paling besar.

```sh
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
input awalnya berupa bertipe pointer array of char(string) diubah menjadi integer degan fungsi atoi dan disimpan dalam array of int thisint\[]. kemudian diurutkan dengan algoritma bubble sort.

```sh
for(i=0;i<argc-1;i++){
    flag = 0;
    thr=pthread_create(&(tid[i]), NULL, factor_this, (void*)&i);
    while (flag!=1){ }
  }
  for(j=0;j<argc-1;j++)
  {
    pthread_join(tid[j],NULL);
  }
```
dilakukan pembuatan thread secara looping dengan start function nya adalah fungsi factor_this dan argumen yang dipassingkan adalah index i.

```sh
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
```

fungsi yang menghitung faktorial dan mengoutputkannya.


### 3.
##### Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
##### Terdapat 2 karakter Agmal dan Iraj
##### Kedua karakter memiliki status yang unik
##### Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
##### Iraj memiliki Spirit_Status, di awal program memiliki status 100
##### Terdapat 3 Fitur utama
##### All Status, yaitu menampilkan status kedua sahabat
##### Ex: Agmal WakeUp_Status = 75 
#####      Iraj Spirit_Status = 30
##### “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
##### “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
##### Terdapat Kasus yang unik dimana:
##### Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
##### Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
##### Program akan berhenti jika Salah Satu :
##### WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
##### Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

##### Syarat Menggunakan Lebih dari 1 Thread

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

thread digunakan untuk menambah WakeUp_Status, dan mengurangi Spirit_Status. dan delay ketika fitur menambah dan mengurangi status digunakan 3 kali.

```sh
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
```

fungsi WakeUp() untuk menambah status WakeUp
```sh
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
```
fungsi Sleep_pls() untuk mengurangi Spirit_Status
```sh
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
```
fungsi check() untuk mengecek apakah status Agmal dan Iraj memenuhi syarat exit program
```sh
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
```
fungsi delay() untuk men-disable komplemen fitur yang digunakan 3 kali.
```sh
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
```


### 4.
##### Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
##### Dengan Syarat : 
##### Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
##### Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
##### Ketika Mengekstrak file .zip juga harus secara bersama-sama
##### Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
##### Wajib Menggunakan Multithreading
##### Boleh menggunakan system

```sh
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

```

dibuat 6 thread pada program.
```sh
char *list_it1 = "ps aux | head -11 | tail -10 > /home/Penunggu/Documents/FolderProses1/SimpanProses1.txt";
  char *list_it2 = "ps aux | head -21 | tail -10 > /home/Penunggu/Documents/FolderProses2/SimpanProses2.txt";
  char *letszip1 = "zip -r -j /home/Penunggu/Documents/FolderProses1/KompresProses1 /home/Penunggu/Documents/FolderProses1/SimpanProses1.txt";
  char *letszip2 = "zip -r -j /home/Penunggu/Documents/FolderProses2/KompresProses2 /home/Penunggu/Documents/FolderProses2/SimpanProses2.txt";
  char *unzip1 = "unzip /home/Penunggu/Documents/FolderProses1/KompresProses1.zip -d /home/Penunggu/Documents/FolderProses1";
  char *unzip2 = "unzip /home/Penunggu/Documents/FolderProses2/KompresProses2.zip -d /home/Penunggu/Documents/FolderProses2";
```
merupakan list command system yang digunakan pada program. digunakan untuk mengambil 10 list hasil dari `ps aux`, men zip text, serta menggunzipnya kembali.

```sh
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

```
thread 1 dan 2 untuk mengambil 10 data hasil dari command ps aux yang disimpan pada 2 file berbeda dan folder berbeda. fungsi start yang digunakan pada kedua thread ini adalah fungsi wat_proc().
```sh
void* wat_proc(void *this)
{
  char *y = (char *)this;
  system(y);
}
```
sedangkan thread 3 dan 4 untuk men zip kedua file txt secara bersamaan dan menghapus file txt tersebut. fungsi startnya adalah zipit().
```sh
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
```
thread 5 dan 6 digunakan untuk mengunzip kedua file yang telah dikompres sebelumnya. fungsi startnya adalah unzipit().
```sh
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
```
