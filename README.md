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
