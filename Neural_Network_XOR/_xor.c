#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "init.h"
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

void _xor()
{
  for(int i = 0; i < 20000; i++)
    {
      //train the neural network with all possibility
      I[0] = 0;
      I[1] = 0;
      final = 0;
      init();
      erro += err;
      I[0] = 1;
      I[1] = 0;
      final = 1;
      init();
      erro += err;
      I[0] = 0;
      I[1] = 1;
      final = 1;
      init();
      erro += err;
      I[0] = 1;
      I[1] = 1;
      final = 0;
      init();
      erro += err;
      ite += 1;
    }
}
