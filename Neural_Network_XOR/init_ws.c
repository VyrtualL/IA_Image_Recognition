#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "_xor.h"
#include "init.h"

extern int I[];
extern int final;
extern float err;
extern float erro;
extern float alpha;
extern float w1[][2];
extern float w2[];
extern float v1[][2];
extern float v2[];
extern float s[];
extern float vs[];
extern float o1[];
extern float o2[];
extern float d[];
extern float sum;
extern int ite;

//initiate weight
void init_weight()
{
  srand(time(NULL));
  for(int i = 0;i<2;i++)
  {
    for(int j=0;j<2;j++)
      {
	w1[i][j] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f + 1.0f))) ;
      }
    w2[i] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f+1.0f)));
  }
}

//initiate bias
void init_seuil()
{
  for(int i = 0;i<3;i++)
  {
    s[i] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f+1.0f)));
  }
  
}
