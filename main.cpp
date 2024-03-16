#include <iostream>
#include <fstream>
#include <pthread.h>
using namespace std;

void printarr(int array1[], int size){
  for (int i = 0; i<size; i++)
    cout << array1[i] << endl;
  cout << endl;
}

struct arraysect{
int *start;
int size;
};

void bubble(int A[], int size){
  int swaps = 1;
  // number of swaps we need to check for
  int iterations = size;
  for (int j=0; j < size - 1; j++){ 
    swaps = 0;
    for (int i = 1; i < iterations; i++){
      if (A[i] < A[i - 1]){
        swap(A[i], A[i - 1]);
        swaps += 1;
      }
    }
    if (swaps == 0)
      break;
    iterations -= 1;
  }
}

void *bubble_bridge(void *ptr){
  arraysect *arg = (arraysect *)ptr;
  bubble(arg->start, arg->size);
  return NULL;
}

void read_and_write_nums(){
  ifstream numberfile;
  numberfile.open("numbers.dat");
  int num;
  int numofnums = 0;
  while (numberfile >> num){
    numofnums += 1;
  }
  numberfile.close();
  
  int sectsize = numofnums / 8;
  
  numberfile.open("numbers.dat");
  int *A = new int[numofnums];
  int endofarray = 0;
  while (numberfile >> num){
    A[endofarray] = num;
    endofarray += 1;
  }
  
  pthread_t thread0, thread1, thread2, thread3, thread4, thread5, thread6, thread7;
  
  arraysect sect0;
  sect0.size = sectsize;
  sect0.start = &A[0];

  arraysect sect1;
  sect1.size = sectsize;
  sect1.start = &A[sectsize];

  arraysect sect2;
  sect2.size = sectsize;
  sect2.start = &A[sectsize * 2];

  arraysect sect3;
  sect3.size = sectsize;
  sect3.start = &A[sectsize * 3];

  arraysect sect4;
  sect4.size = sectsize;
  sect4.start = &A[sectsize * 4];

  arraysect sect5;
  sect5.size = sectsize;
  sect5.start = &A[sectsize * 5];

  arraysect sect6;
  sect6.size = sectsize;
  sect6.start = &A[sectsize * 6];
  
  arraysect sect7;
  sect7.size = sectsize;
  sect7.start = &A[sectsize * 7];

  pthread_create(&thread0, NULL, bubble_bridge, (void*) &sect0);
  pthread_create(&thread1, NULL, bubble_bridge, (void*) &sect1);
  pthread_create(&thread2, NULL, bubble_bridge, (void*) &sect2);
  pthread_create(&thread3, NULL, bubble_bridge, (void*) &sect3);
  pthread_create(&thread4, NULL, bubble_bridge, (void*) &sect4);
  pthread_create(&thread5, NULL, bubble_bridge, (void*) &sect5);
  pthread_create(&thread6, NULL, bubble_bridge, (void*) &sect6);
  pthread_create(&thread7, NULL, bubble_bridge, (void*) &sect7);

  pthread_join(thread0, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);
  pthread_join(thread5, NULL);
  pthread_join(thread6, NULL);
  pthread_join(thread7, NULL);

  printarr(A, numofnums);
  
  ofstream output("mysort.out");
  for (int i = 0; i < numofnums; i++){
    output << A[i] << endl;
  }
}

int main(){
 read_and_write_nums(); 
}