//Lab 1 - Array sorter
//Vincent Chan
//RedID 815909699

#include <stdio.h>
#include <stdlib.h>

#define SEED 123

//Array declarations and function prototype
int x[10];
void initArray(int a[], int size, int min, int max, int seed);
void printArray(int a[], int size, char name[]);
void sortArray(int a[], int size);
int sorted(int a[], int size);

/***Main******************************/
/**                                 **/
int main() {
  initArray(x, 10, 10, 100, SEED);
  printArray(x, 10, "array x");
  sortArray(x, 10);
  printArray(x, 10, "array x Sorted");
  return 0;
} //End main
/**                                 **/
/*************************************/

/***Functions*************************/
/**                                 **/
//This will print the array.
//accepts an array, size, and a string to print before printing array.
void printArray(int a[], int size, char name[]) {
  int i;
  printf("%s:\n", name);
  for(i=0; i<size; i++)
    printf("%d\n", a[i]);
} //End printArray()

//This will initialize the array, populating it with random integers
//user can specify size, minimum int, max int, and the seed to use.
void initArray(int a[], int size, int min, int max, int seed) {
  int i;
  srand(seed);
  for(i=0; i<size; i++) a[i] = (rand()%(max-min+1)) + min;
} //End initArray()

//This will sort the given array.
//Size and array must be specified.
void sortArray(int a[], int size) {
  int i, temp, r;
  while(!sorted(a, size)) {
    for(i=0; i<size; i++) {
      r = rand()%size;
      temp = a[i];
      a[i] = a[r];
      a[r] = temp;
    }
  }
} //End sortArray()

//This will check the array to see if it sorted.
//returns 1 if sorted, 0 if not.
int sorted(int a[], int size) {
  int i;
  for(i=0; i<size-1; i++)
    if(a[i]>a[i+1]) return 0;
  return 1;
} //End sorted()
/**                                 **/
/*************************************/
