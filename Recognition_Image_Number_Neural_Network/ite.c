#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "gen.h"
#include "init.h"

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

// Do all the learning of the neural network
void ite()
{

   
   
  
  // Do the change for out_put of first layer
  for(int i = 0; i < 100; i++)
    {
      float under_softmax = 0;
      // Get the input of first hidden layer
      for(int j = 0; j < 784; j++)
	{
	  under_softmax += (output_input_layer[j] * w_i_h[j][i]);
	  //printf("random value weight : %.6f\n", w_i_h[j][i]);
	}
      under_softmax = under_softmax - b_f_h[i];
      // Do softmax of under_softmax
      // Exp du chiffre diviser par l4exp de la somme des inputs de la layer davant
      float ressss = 1.0f / (1.0f + expf(-under_softmax));
      output_first_hidden_layer[i] = ressss;
      //printf("output first hidden : %.6f\n",output_first_hidden_layer[i]);
    }
    
    //printf("random value first hidden : %.6f\n", output_first_hidden_layer[67]);
    //printf("random value weight : %.6f\n", w_i_h[157][67]);

  // Do the change for output of second hidden layer
  for(int k = 0; k < 100; k++)
    {
      float under_softmax_second = 0;
      // Get the input of second hidden layer
      for(int l = 0; l < 100; l++)
	{
	  under_softmax_second += (output_first_hidden_layer[l] * w_h_h[l][k]);
	  //printf("random value weight : %.6f\n", w_i_h[l][k]);
	}
      under_softmax_second = under_softmax_second - b_s_h[k];
      // Do softmax of under_softmax_second
      float resssss = 1.0f / (1.0f + expf(-under_softmax_second));
      output_second_hidden_layer[k] = resssss; 
      //printf("output second hidden : %.6f\n",output_second_hidden_layer[k]);
    }


  // Do the change for output of output layer
  for(int m = 0; m < 10; m++)
    {
      float under_softmax_third = 0;
      // Get the input of output layer
      for(int n = 0; n < 100; n++)
	{
	  under_softmax_third += (output_second_hidden_layer[n] * w_h_o[n][m]);
	  //printf("random value weight : %.6f\n", w_i_h[n][m]);
	}
      under_softmax_third = under_softmax_third - b_o_l[m];
      // Do softmax of under_softmax_third
      float ressssss = 1.0f / (1.0f + expf(-under_softmax_third));
      output_output_layer[m] = ressssss;
      //printf("output output layer : %.6f\n", output_output_layer[m]);
    }
    
  

  // Calculate error of all output
  for(int aa = 0; aa < 10; aa++)
    {
      error[aa] = error_wanted[aa] - output_output_layer[aa];
    }
  

  // Calculate the error gradiant of the output layer
  for(int c = 0; c < 10; c++)
    {
      e_g_o_l[c] = output_output_layer[c] * (1 - output_output_layer[c]) * error[c];
    }

  // Calculate the error gradiant of the second hidden layer
  for(int b = 0; b < 100; b++)
    {
      float tmp_e_g = 0;
      for(int a = 0; a < 10; a++)
	{
	  tmp_e_g += output_second_hidden_layer[b] * (1 - output_second_hidden_layer[b]) * e_g_o_l[a] * w_h_o[b][a];
	}
      e_g_s_h[b] = tmp_e_g;
    }

  // Calculate the error gradiant of the first hidden layer
  for(int d = 0; d < 100; d++)
    {
      float tmp2_e_g = 0;
      for(int e = 0; e < 100; e++)
	{
	  tmp2_e_g += output_first_hidden_layer[d] * (1 - output_first_hidden_layer[d]) * e_g_s_h[e] * w_h_h[d][e];
	}
      e_g_f_h[d] = tmp2_e_g;
    }



  // Calculate variations of the weights between second and output layer
  for(int f = 0; f < 100; f++)
    {
      for(int g = 0; g < 10; g++)
	{
	  v_w_h_o[f][g] = alpha * output_second_hidden_layer[f] * e_g_o_l[g];
	}
    }

  // Calculate variations of the bias of the output layer
  for(int ad = 0; ad < 10; ad++)
    {
      v_b_o_l[ad] = alpha * (-1) * e_g_o_l[ad];
    }

  // Calculate variation of the weights between first and second hidden layer
  for(int h = 0; h < 100; h++)
    {
      for(int o = 0; o < 100; o++)
	{
	  v_w_h_h[h][o] = alpha * output_first_hidden_layer[h] * e_g_s_h[o];
	}
    }

  // Calculate variations of the bias of the second hidden layer
  for(int s = 0; s < 100; s++)
    {
      v_b_s_h[s] = alpha * (-1) * e_g_s_h[s];
    }

  // Calculate variation of the weights between input and first hidden layer
  for(int p = 0; p < 784; p++)
    {
      for(int q = 0; q < 100; q++)
	{
	  v_w_i_h[p][q] = alpha * output_input_layer[p] * e_g_f_h[q];
	}
    }

  // Calculate variation of the bias of the first hidden layer
  for(int r = 0; r < 100; r++)
    {
      v_b_f_h[r] = alpha * (-1) * e_g_f_h[r];
    }



  // Update of the weights between input and first hidden layer
  for(int t = 0; t < 784; t++)
    {
      for(int u = 0; u < 100; u++)
	{
	  w_i_h[t][u] = w_i_h[t][u] + v_w_i_h[t][u];
	}
    }

  // Update of the weights between first and second hidden layer
  for(int v = 0; v < 100; v++)
    {
      for(int w = 0; w < 100; w++)
	{
	  w_h_h[v][w] = w_h_h[v][w] + v_w_h_h[v][w];
	}
    }

  // Update of the weights between second and input layer
  for(int x = 0; x < 100; x++)
    {
      for(int y = 0; y < 10; y++)
	{
	  w_h_o[x][y] = w_h_o[x][y] + v_w_h_o[x][y];
	}
    }

  // Update of the bias of the first hidden layer
  for(int z = 0; z < 100; z++)
    {
      b_f_h[z] = b_f_h[z] + v_b_f_h[z];
    }

  // Update of the bias of the second hidden layer
  for(int ab = 0; ab < 100; ab++)
    {
      b_s_h[ab] = b_s_h[ab] + v_b_s_h[ab];
    }

  // Update of the bias of the output hidden layer
  for(int ac = 0; ac < 10; ac++)
    {
      b_o_l[ac] = b_o_l[ac] + v_b_o_l[ac];
    }
}  
