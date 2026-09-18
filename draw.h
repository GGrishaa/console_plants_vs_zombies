#ifndef DRAW_H
#define DRAW_H

#define _XOPEN_SOURCE_EXTENDED 1

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>

#include "icons.h"

enum PLANTS {
  empty = 0,
  sunflower = 1,
  peanut = 2,
  cherry = 3,
  cactus = 4,
  nut = 5,
  latuce = 6,
  watermelon = 7
};

struct field {
  enum PLANTS plants[5][10];
  int cooldown[7];
};

void init_field(struct field* fld);

void init(struct field* fld);
void draw_field(struct field* fld, int* suns, enum PLANTS cur);

int movement(int y, int x, struct field* fld, enum PLANTS* cur);
enum PLANTS select(int y, int x, struct field* fld);

void draw_plant(int y, int x, enum PLANTS type, int color);
void draw_sunflower(int y, int x, int color);
void draw_peanut(int y, int x, int color);
void draw_cherry(int y, int x, int color);
void draw_cactus(int y, int x, int color);
void draw_nut(int y, int x, int color);
void draw_latuce(int y, int x, int color);
void draw_watermelon(int y, int x, int color);

#endif