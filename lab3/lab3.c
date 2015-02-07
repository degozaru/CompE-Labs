/* Lab 3 Spring 2015
 * Vincent Chan 815909699
 */

#include <stdio.h>
#include <math.h>

typedef struct {
  float x;
  float y;
  float z;
} vector;

vector getVector(void);
void printVector(vector v);
vector addVectors(vector* v1, vector* v2);
float magnitude(vector* v);

/**Main function************************************/
/**                                               **/
int main() {
  vector v1, v2, v3;
  
  //Vector 1
  printf("Enter vector v1:\n");
  v1 = getVector();
  printf("[Vector 1]\n");
  printVector(v1);
  printf("[Vector 1] = %0.2f\n", magnitude(&v1));

  //Vector 2
  printf("Enter vector v2: ");
  v2 = getVector();
  printf("[Vector 2]\n");
  printVector(v2);
  printf("[Vector 2] = %0.2f\n", magnitude(&v1));

  //Vector addition
  printf("v1 + v2 =\n");
  v3 = addVectors(&v1, &v2);
  printVector(v3);

  return 0;
} //End main()
/**                                               **/
/***************************************************/

/**Functions****************************************/
/**                                               **/
//This will construct a vector
//returns the constructed vector.
vector getVector() {
  vector temp;
  printf("Enter x: ");
  scanf("%f", &temp.x);
  printf("Enter y: ");
  scanf("%f", &temp.y);
  printf("Enter z: ");
  scanf("%f", &temp.z);
  printf("\n");
  return temp;
} //End getVector()

//This will add the vectors
//returns the sum of the two vectors
vector addVectors(vector* v1, vector* v2) {
  vector temp;
  temp.x = (*v1).x + (*v2).x;
  temp.y = (*v1).y + (*v2).y;
  temp.z = (*v1).z + (*v2).z;
  return temp;
} //End addVectors();

//This prints the vector.
void printVector(vector v) {
  printf("[X] %0.2f [Y] %0.2f [Z] %0.2f", v.x, v.y, v.z);
  printf("\n");
} //End printVector()

//This will calculate the magnitude
//of the vector. 
float magnitude(vector* v) {
  return (float) sqrt(((*v).x*(*v).x)+
                      ((*v).y*(*v).y)+
                      ((*v).z*(*v).z));
} //End magnitude()
/**                                               **/
/***************************************************/

/*************
 * Fall seven times
 *    Get up eight.
 ************/
