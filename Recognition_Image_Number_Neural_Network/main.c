#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "ite.h"
#include "init.h"
#include "gen.h"

// Learning Rate
float alpha = 0.1;

// Input of Input Layer (28x28 neural)
// [number of the neural]
float output_input_layer[784];

// Input of the First Hidden Layer (100 neural)
// [number of the neural][number of the output for the second hidden layer]
float output_first_hidden_layer[100];

// Input of the Second Hidden Layer (100 neural)
// [number of the neural][number of the output for the output layer]
float output_second_hidden_layer[100];

// Input of the Output Layer (10 neural)
// [number of the neural][number of the output]
float output_output_layer[10];

// The Weight between Input Layer and First Hidden Layer
float w_i_h[784][100];

// The Weight between First Hidden Layer and Second Hidden Layer
float w_h_h[100][100];

// The Weight between Second Hidden Layer and Output Layer
float w_h_o[100][10];

// Bias of the First Hidden Layer
float b_f_h[100];

// Bias of the Second Hidden Layer
float b_s_h[100];

// Bias of the Output Layer
float b_o_l[10];

// List of the Variation Weight between Input and First Hidden Layer
float v_w_i_h[784][100];

// List of the Variation Weight between First and Second Hidden Layer
float v_w_h_h[100][100];

// List of the Variation Weight between the Second and Output Layer
float v_w_h_o[100][10];

// List of the Variation Bias of the First Hidden Layer
float v_b_f_h[100];

// List of the Variation Bias of the Second Hidden Layer
float v_b_s_h[100];

// List of the Variation Bias of the Output Layer
float v_b_o_l[10];

// List of the Error Gradiant of the Output Layer
float e_g_o_l[10];

// List of the Error Gradiant of the Second Hidden Layer
float e_g_s_h[100];

// List of the Error Gradiant of the First Hidden Layer
float e_g_f_h[100];

// Error of the neural network
float error[10];

//Error we wanted
float error_wanted[10];



int main(int argc, char *argv[])
{
  if(argc < 2 || argc > 3)
    {
      printf("number of args invalid");
    }
    
  // Initiate weight and bias (or take weights and bias from file)
  init_weight_w_i_h();
  printf("ok1\n");
  init_weight_w_h_h();
  init_weight_w_h_o();
  init_b_h();
  init_b_o();
  printf("ok2\n");
  
  // Train
  gen();
  
  printf("ok3\n");
  
  // Take the args and init
  init_input_layer(argv[1]);

  // Do the final result :
  
  // Do the change for out_put of first layer
  for(int i = 0; i < 100; i++)
    {
      float under_softmax = 0;
      // Get the input of first hidden layer
      for(int j = 0; j < 784; j++)
	{
	  under_softmax += (output_input_layer[j] * w_i_h[j][i]);
	}
      under_softmax = under_softmax - b_f_h[i];
      // Do softmax of under_softmax
      // Exp du chiffre diviser par l4exp de la somme des inputs de la layer davant
      float ressss = 1 / (1 + expf(-under_softmax));
      output_first_hidden_layer[i] = ressss;
    }

  
  // Do the change for output of second hidden layer
  for(int k = 0; k < 100; k++)
    {
      float under_softmax_second = 0;
      // Get the input of second hidden layer
      for(int l = 0; l < 100; l++)
	{
	  under_softmax_second += (output_first_hidden_layer[l] * w_h_h[l][k]);
	}
      under_softmax_second = under_softmax_second - b_s_h[k];
      // Do softmax of under_softmax_second
      float resssss = 1 / (1 + expf(-under_softmax_second));
      output_second_hidden_layer[k] = resssss;
    }


  // Do the change for output of output layer
  for(int m = 0; m < 10; m++)
    {
      float under_softmax_third = 0;
      // Get the input of output layer
      for(int n = 0; n < 100; n++)
	{
	  under_softmax_third += (output_second_hidden_layer[n] * w_h_o[n][m]);
	}
      under_softmax_third += under_softmax_third - b_o_l[m];
      // Do softmax of under_softmax_third
      float ressssss = 1 / (1 + expf(-under_softmax_third));
      output_output_layer[m] = ressssss;
    }


  // Print all result for know the proba of all number
  printf("Output : ");
  for(int fin = 0; fin < 10; fin++)
    {
      printf("%.6f ;\n ", output_output_layer[fin]);
    }
  // Know the higher probability for the true result
  float thetrueresult = 0;
  float number = 0;
  float numm = 0;
  for(int ggg = 0; ggg < 10; ggg++)
    {
      if(output_output_layer[ggg] > thetrueresult)
	{
	  thetrueresult = output_output_layer[ggg];
	  if(thetrueresult > number)
	    {
	      number = thetrueresult;
	      numm = ggg;
	    }
	}
    }
  printf("Result : %.6f\n", numm);
}
