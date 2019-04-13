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

### 2.
##### Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
##### Terdapat 2 server: server penjual dan server pembeli
##### 1 server hanya bisa terkoneksi dengan 1 client
##### Server penjual dan server pembeli memiliki stok barang yang selalu sama
##### Client yang terkoneksi ke server penjual hanya bisa menambah stok
##### Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
##### Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
##### Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
##### Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
##### Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
##### Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
##### Server penjual akan mencetak stok saat ini setiap 5 detik sekali
##### Menggunakan thread, socket, shared memory



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

multi-thread digunakan untuk menambah WakeUp_Status, dan mengurangi Spirit_Status. dan delay ketika fitur menambah dan mengurangi status digunakan 3 kali.
Apabila user memilih '2' maka fitur yang dijalankan adalah "Agmal Ayo Bangun" dimana akan dibuat thread dengan tid thread2 dan starting function WakeUp().
Sedangkan apabila user menginputkan pilihan '3' maka fitur yang akan dijalankan adalah "Iraj Ayo Tidur" dimana akan dibuat thread dengan tid thread3 dan dengan starting function Sleep_pls().

Ketika memilih fitur "Agmal Ayo Bangun" atau "Iraj Ayo Tidur", akan dilakukan counting berapa kali fitur telah digunakan. Masing-masing fitur memiliki counter yang akan diincrement 1 tiap kali user memilih fitur untuk dijalankan. Pada fitur "Agmal Ayo Bangun" counternya disimpan pada variabel global countwake, dan pada fitur "Iraj Ayo Tidur" counternya disimpan pada variabel global countgn.

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

fungsi WakeUp() untuk menambah status WakeUp sebanyak 15 yang merupakan starting function dari thread dengan tid thread2.
Apabila countwake == 3 maka akan ditampilkan pesan "Fitur Iraj Ayo Tidur disabled 10 s" dan dibuat thread dengan tid thread1 dengan starting function delay().
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
fungsi Sleep_pls() untuk mengurangi Spirit_Status sebanyak 20 dan fungsi ini merupakan starting function dari thread dengan tid thread3. Apabila countgn == 3 maka akan ditampilkan pesan "Agmal Ayo Bangun disabled 10 s" dan dibuat thread dengan tid  thread1 dengan starting function delay().
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
fungsi check() untuk mengecek apakah status Agmal dan Iraj memenuhi syarat exit program, yaitu apabila WakeUp_Status >= 100 atau ketika Spirit_Status <= 0.
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
fungsi ini akan dipanggil sebagai start function thread yang dibuat ketika countgn atau countwake = 3 yang berarti fitur telah dijalankan sebanyak 3 kali.
Dalam fungsi ini dilakukan looping selama 10 s dimana selama loopingan tersebut berjalan, counter yang bernilai 3 akan diberi flag. Jika countgn yang memiliki nilai 3, maka flag2 = 1. Jika countwake yang memiliki nilai 3, maka flag3 =1.
Pemberian flag2 dan flag3 ini yang akan berefek pada fungsi main() dimana pilihan tidak akan berjalan ketika flag ini bernilai 1.

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

### 5. 
##### Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
##### Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
##### Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
##### Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
##### Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
##### Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
##### Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
##### Pembeli (terintegrasi dengan game)
##### Dapat mengecek stok makanan yang ada di toko.
##### Jika stok ada, pembeli dapat membeli makanan.
##### Penjual (terpisah)
##### Bisa mengecek stok makanan yang ada di toko
##### Penjual dapat menambah stok makanan.
##### 	Spesifikasi program:
##### Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
##### Program terdiri dari 3 scene yaitu standby, battle, dan shop.
##### Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

##### Standby Mode
##### Health : [health status]
##### Hunger : [hunger status]
##### Hygiene : [hygiene status]
##### Food left : [your food stock]
##### Bath will be ready in [cooldown]s
##### Choices
##### Eat
##### Bath
##### Battle
##### Shop
##### Exit

##### Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

##### Battle Mode
##### Monster’s Health : [health status]
##### Enemy’s Health : [enemy health status]
##### Choices
##### Attack
##### Run

##### Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

##### 		Shop Mode
##### 		Shop food stock : [shop food stock]
##### 		Your food stock : [your food stock]
##### 		Choices
##### Buy
##### Back

##### Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

##### Shop
##### Food stock : [shop food stock]
##### Choices
##### Restock
##### Exit

##### Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

```sh
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

```

##### -- Revisi Soal 5 --

Program dimana game berjalan :
```sh
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

```

Program dimana fitur shop berjalan :
```sh
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>


void *this();

pthread_t shop;
int *fish_n_ships;
int do_;

void main()
{


  key_t key = 1234;

  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  fish_n_ships = shmat(shmid, NULL, 0);
  *fish_n_ships = 10;

  while(1){
    pthread_create(&shop, NULL, this, NULL);
    pthread_join(shop, NULL);
    scanf("%d", &do_);

    if(do_ == 1){
      *fish_n_ships += 1;
      pthread_create(&shop, NULL, this, NULL);
      pthread_join(shop, NULL);

    }
    else if(do_ == 2 || *fish_n_ships < 0){
      printf("Shop Closed\n");
      exit(1);
    }

      pthread_create(&shop, NULL, this, NULL);
      pthread_join(shop, NULL);

  }

  return;

}


void *this()
{
  // while(1){
    system("clear");
    printf("Shop\n");
    printf("-----------------\n");
    printf("Food Stock : %d\n", *fish_n_ships);
    printf("Choices\n");
    printf("1. Restock\n");
    printf("2. Exit\n\n");

    // scanf("%d", &do_);
    // sleep(1);
  // }

}

```

Pada revisi program game, ada penambahan real time update pada mode standby yang menampilkan status dari monster (health status, hungry status, hygiene status, food status, dan cooldown bath).

Pada main program :
```sh
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
```
Pada awal program user diminta menginputkan nama monster dan kemudian akan dioutputkan.
Lalu dibuat 3 thread dengan keterangan sebagai berikut:

- thread dengan tid healtht akan menggunakan blood() sebagai starting functionnya dimana thread ini akan menambah helath_stat monster tiap 10 detik sebanyak 5.
```sh
  pthread_create(&healtht, NULL, blood, NULL);
  
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

```

- thread dengan tid hygienet dengan starting function hygiene() akan mengurangi hygiene_stat sebanyak 10 tiap 30 s.
```sh
  pthread_create(&hygienet, NULL, hygiene, NULL);
  
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
```

- thread dengan tid hungert dengan starting function hunger() yang akan mengurangi hunger_stat monster sebanyak 5 tiap 10 s.
```sh
  pthread_create(&hungert, NULL, hunger, NULL);
  
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
```
Lalu setelah itu dilakuan looping dalam while(1) yang akan menampilkan menu dari program game.

Untuk menampilkan menu standby mode, dibuat thread dengan tid stnby dengan starting function standby().
```sh
    pthread_create(&stnby, NULL, standby, NULL);
    pthread_join(stnby, NULL);
```
Apabila user menginputkan '1', maka fitur yang dipilih adalah "Eat".
Sebelumnya dicek terlebih dahulu food_stat dari monster yang disimpan dalam variabel my_fishnships.

my_fishnships ini merupakan variabel shared memory dengan program __shop.c__  dimana kedua program dapat menggunakan variabel ini secara bersamaan. Pada program game, user dapat mengurangi jumlah dari my_fishnships dengan menggunakan fitur "Eat", dan pada program __shop.c__ user dapat menambah stok my_fishnships ini.

Apabila jumlah my_fishnships tidak mencukupi / = 0, maka akan ditampilkan pesan "not enough food :("
Namun apabila my_fishnships mencukupi / user telah membeli stok makanan dari shop dan food stock nya belum habis diberikan pada monster, maka hunger_stat ditambah 15 dan stok my_fishnships dikurangi 1.
```sh
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
```

Kemudian apabila user menginputkan '2', maka fitur "Bath" akan dijalankan.
Pada fitur bath ini, terdapat flagbath yang digunakan untuk mengecek apakah cooldown dari fitur ini sedang berjalan atau tidak.
Apabila flagbath == 0 atau berarti fitur ini belum digunakan sama sekali / paling tidak selama 20 detik yang lalu, maka fitur dapat dijalankan.
Flagbath diubah menjadi 1 dan hygiene_stat ditambah 30.
kemudian dibuat thread dengan tid threadbath dengan starting function bath().
```sh
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
```
Pada fungsi bath() tersebut, dilakukan counting selama 20 second dengan counter_bath yang diset 20 pada awal fungsi dan kemudian diincrement tiap 1 s. Tiap 1 s dibuat thread menampilkan mode standby agar cooldown bath dapat ditampilkan secara real time.
Setelah 20 s selesai, flagbath dikembalikan menjadi 0 dan dapat digunakan kembali.

Ketika user menginputkan '3', maka game akan masuk ke mode Battle.
Akan dibuat thread dengan tid bttl dengan starting function battle()

Pada fungsi ini terdapat 3 pilihan yaitu attack, run, atau leave. Apabila monster dan enemy sama-sama menyerang, maka healthstat monster akan berkurang 20 dan darah enemy juga akan berkurang 20. Selain itu, tidak terjadi perubahan apa-apa.
Mode battle akan selesai ketika salah satu monster atau enemy mati.
```sh
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

```

JIka user memilih '4', maka akan masuk ke mode Shop. dibuat thread dengan tid shp dan starting function shop()
Pada mode ini ditampilkan menu yang memungkinkan user untuk mengakses shared memory my_fishnships dan menambah stok makanan untuk monster.
```sh
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
```
Source code __shop.c__ :
```sh
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>


void *this();

pthread_t shop;
int *fish_n_ships;
int do_;

void main()
{


  key_t key = 1234;

  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  fish_n_ships = shmat(shmid, NULL, 0);
  *fish_n_ships = 10;

  while(1){
    pthread_create(&shop, NULL, this, NULL);
    pthread_join(shop, NULL);
    scanf("%d", &do_);

    if(do_ == 1){
      *fish_n_ships += 1;
      pthread_create(&shop, NULL, this, NULL);
      pthread_join(shop, NULL);

    }
    else if(do_ == 2 || *fish_n_ships < 0){
      printf("Shop Closed\n");
      exit(1);
    }

      pthread_create(&shop, NULL, this, NULL);
      pthread_join(shop, NULL);

  }

  return;

}


void *this()
{
  // while(1){
    system("clear");
    printf("Shop\n");
    printf("-----------------\n");
    printf("Food Stock : %d\n", *fish_n_ships);
    printf("Choices\n");
    printf("1. Restock\n");
    printf("2. Exit\n\n");

    // scanf("%d", &do_);
    // sleep(1);
  // }

}

```
