#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <err.h>
#include "ite.h"
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


void init_sdl()
{
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    errx(1,"Could not initialize SDL: %s.\n",SDL_GetError());
}

SDL_Surface* load_image(char* path)
{
  SDL_Surface *img;
  img = IMG_Load(path);
  if(!img)
    {
      errx(3,"Can't load %s: %s",path, IMG_GetError());
    }
  return img;
}

Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void SDL_FreeSurface(SDL_Surface *surface);

// Init the input layer
void init_input_layer(char* picture)
{
  SDL_Surface* image_surface = load_image(picture);
  Uint8 r, g, b;
  int width = image_surface->w;
  int height = image_surface->h;
  int index = 0;
  for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
	{
	  Uint32 pixel = get_pixel(image_surface, j, i);
	  SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
	  float f1;
	  if(r < 125)
	  {
	    f1 = 0;
	  }
	  else
	  {
	    f1 = 1;
	  }
	  output_input_layer[index] = f1;
	  index++;
	}
    }
  SDL_FreeSurface(image_surface);
}



















// Do the iteration for the neural system
void gen()
{
  // Train the neural network with all possibility
  for(int i = 0; i < 75; i++)
    {
      int index_error = -1;
      int index_error2 = -1;
      printf("gen%i\n", i);
      for(int b = 0; b < 400; b++)
	{
	  for(int et = 0; et < 10; et++)
	    {
	      error[et] = 0;
	      error_wanted[et] = 0;
	      //printf("error wanted %i : %.6f\n",et, error_wanted[et]);
	      //printf("%i\n",b);
	    }
	  //printf("%i\n",b);
	  if(b < 10 && b >= 0)
	    {
	      error_wanted[b] = 1;
	      //printf("error wanted %i : [%i] %.6f\n",b,b, error_wanted[b]);
	      char fic[6] = "X.bmp";
	      fic[0] = (char)(b+48);
	      init_input_layer(fic);
	      ite();
	      error_wanted[b] = 0;
	    }
	  if(b >= 10 && b < 100)
	    {
	      index_error++;
	      if(index_error == 10)
	        {
	          index_error = 0;
	        }
	      char fich[7] = "XX.bmp";
	      int tenth = b / 10;
	      error_wanted[index_error] = 1;
	      //printf("error wanted %i : [%i] : %.6f\n",b,index_error, error_wanted[(b % 10)]);
	      fich[0] = (char)(tenth+48);
	      fich[1] = (char)((b % 10) + 48); 
	      init_input_layer(fich);
	      ite();
	      
	    }
	  if(b >= 100 && b < 400)
	    {
	      index_error2++;
	      if(index_error2 == 10)
	        {
	          index_error2 = 0;
	        }
	      char fichi[] = "XXX.bmp";
	      int hundred = b / 100;
	      int indd = b % 100;
	      int tenth2 = indd / 10;
	      error_wanted[index_error2] = 1;
	      //printf("error wanted %i : [%i] : %.6f\n",b,index_error2, error_wanted[index_error2]);
	      fichi[0] = (char)(hundred + 48);
	      fichi[1] = (char)(tenth2 + 48);
	      fichi[2] = (char)((indd % 10) + 48);
	      init_input_layer(fichi);
	      ite();
	    }
	  //for(int oo = 0; oo < 10; oo++)
	  //{
	     //if(error_wanted[oo] == 1)
	     //{
	        //printf("error wanted %i : %6.f\n",oo, error_wanted[oo]);
	     //}
	  //}
	}
    }
}
