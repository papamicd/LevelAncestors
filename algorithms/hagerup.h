#ifndef HAGERUP_H
#define HAGERUP_H

#include "../la_common.h"

/************************************************************************/
/* Hagerup Algo Data Structures					*/
/************************************************************************/
/************************************************************************/
struct valley_struct
{
  int x;
  int low;
  int high;
};
typedef struct valley_struct valley_tuple;

int* height_arr;    // One-difference array that holds the y value of the current place in the Euler tour representation
int* euler_arr;     // ith vertex in the Euler tour 
int* rep_arr;     // rep_arr(v) returns the index i of the last occurence of v in the height_arr

int* valley;    // valley[x] is the valley for point x where a valley is the deepest right most point reachable without going above y of x
int** ladder;
int* jump;

int K, K_prime, K_max;
int max_depth, y_min, y_max;
/************************************************************************/


/************************************************************************/
/* Function Prototypes						*/
/************************************************************************/
void hagerup_preprocessing();

int hagerup_query(int query_node, int query_level);
/************************************************************************/
#endif