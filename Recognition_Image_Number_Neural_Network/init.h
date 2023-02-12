#ifndef INIT_H
#define INIT_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "ite.h"
#include "gen.h"

void init_weight_w_i_h();
void init_weight_w_h_h();
void init_weight_w_h_o();
void init_b_h();
void init_b_o();

#endif
