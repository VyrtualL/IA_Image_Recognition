#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "_xor.h"
#include "init.h"
#include "init_ws.h"


//input
int I[2];
//result / output final
int final;
//final error
float err;
//error de l'iteration
float erro;
float alpha = 0.1;
//list weight
float w1[2][2];
float w2[2];
//list variation weight
float v1[2][2];
float v2[2];
//bias
float s[3];
//variation bias
float vs[3];
//output of input/hidden layer
float o1[2];
float o2[1];
//delta backpropa
float d[3];
//sum for sigmoide
float sum = 0;
//result xor
int res;
int ite;
float _S(float x)
{
  return 1.0f /(1.0f + expf(-x));
}

int main(int argc, char *argv[])
{
  if(argc < 3 || argc > 4)
    {
      printf("number of args invalid");
    }
  //initiate weight and bias
  init_weight();
  init_seuil();
  //train
  _xor();
  //take the args
  I[0] = strtol(argv[1], NULL, 10);
  I[1] = strtol(argv[2], NULL, 10);
  //do the final result
  for(int i = 0;i <2;i++)
    {
      sum = 0;
      for(int j = 0;j < 2;j++)
	{
	  sum = sum + (I[j] * w1[i][j]);
	}
      sum = sum - s[i];
      o1[i] = _S(sum);
    }
  //sigmoide final
  o2[0] = _S(o1[0]*w2[0] + o1[1]*w2[1] - s[2]);
  printf("result %.6f\n", o2[0]);
  if(o2[0] >= 0.5)
    res = 1;
  else
    res = 0;
  printf("Number of iteration : %i\n", ite);
  printf("First Value : %i\n", I[0]);
  printf("Second Value : %i\n", I[1]);
  printf("Xor result : %i\n", res);
  return res;
}
