#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "_xor.h"
#include "init_ws.h"

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
float S(float x)
{
  return 1.0f /(1.0f + expf(-x));
}

void init()
{
  //sigmoide
  for(int i = 0;i <2;i++)
    {
      sum = 0;
      for(int j = 0;j < 2;j++)
	{
	  sum = sum + (I[j] * w1[i][j]);
	}
      sum = sum - s[i];
      o1[i] = S(sum);
    }
  //sigmoide final
  o2[0] = S(o1[0]*w2[0] + o1[1]*w2[1] - s[2]);
  //erreur
  err = final - o2[0];
  //backpropagation
  d[2] = o2[0] * (1 - o2[0]) * err;
  v2[0] = alpha * o1[0] * d[2];
  v2[1] = alpha * o1[1] * d[2];
  d[0] = o1[0] * (1 - o1[0]) * d[2] * w2[0];
  d[1] = o1[1] * (1 - o1[1]) * d[2] * w2[1];
  vs[2] = alpha * (-1) * d[0];
  v1[0][0] = alpha * I[0] * d[0];
  v1[0][1] = alpha * I[1] * d[0];
  vs[0] = alpha * (-1) * d[0];
  v1[1][0] = alpha * I[0] * d[1];
  v1[1][1] = alpha * I[1] * d[1];
  vs[1] = alpha * (-1) * d[1];
  //mettre a jour les poids
  w1[0][0] += v1[0][0];
  w1[0][1] += v1[0][1];
  w1[1][0] += v1[1][0];
  w1[1][1] += v1[1][1];
  w2[0] += v2[0];
  w2[1] += v2[1];
  //mettre a jour les seuils
  s[0] += vs[0];
  s[1] += vs[1];
  s[2] += vs[2];
}
