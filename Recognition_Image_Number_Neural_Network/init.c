#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "ite.h"
#include "gen.h"

extern float alpha;
extern float output_input_layer[];
extern float output_first_hidden_layer[];
extern float output_second_hidden_layer[];
extern float output_output_layer[];
extern float w_i_h[][100];
extern float w_h_h[][100];
extern float w_h_o[][10];
extern float b_f_h[];
extern float b_s_h[];
extern float b_o_l[];
extern float v_w_i_h[][100];
extern float v_w_h_h[][100];
extern float v_w_h_o[][10];
extern float v_b_f_h[];
extern float v_b_s_h[];
extern float v_b_o_l[];
extern float e_g_f_h[];
extern float e_g_s_h[];
extern float e_g_o_l[];
extern float error[];
extern float error_wanted[];



// Initiate Weight with random number of w_i_h
void init_weight_w_i_h()
{
  srand(time(NULL));
  for(int i = 0; i < 784; i++)
    {
      for(int j = 0; j < 100; j++)
	{
	  w_i_h[i][j] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f + 1.0f)));
	}
    }
}

// Initiate Weight with random number of w_h_h
void init_weight_w_h_h()
{
  srand(time(NULL));
  for(int i = 0; i < 100; i++)
    {
      for(int j = 0; j < 100; j++)
	{
	  w_i_h[i][j] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f + 1.0f)));
	}
    }
}

// Initiate Weight with random number of w_h_o
void init_weight_w_h_o()
{
  srand(time(NULL));
  for(int i = 0; i < 100; i++)
    {
      for(int j = 0; j < 10; j++)
	{
	  w_i_h[i][j] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f + 1.0f)));
	}
    }
}





// Initiate Bias of the First and Second Layer
void init_b_h()
{
  for(int i = 0; i < 100; i++)
    {
      b_f_h[i] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f + 1.0f)));
      b_s_h[i] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f + 1.0f)));
    }
}

// Initiate Bias of the Output Layer
void init_b_o()
{
  for(int i = 0; i < 10; i++)
    {
      b_o_l[i] = -1.0f + ((float)rand() / ((float)RAND_MAX/(1.0f + 1.0f)));
    }
}

