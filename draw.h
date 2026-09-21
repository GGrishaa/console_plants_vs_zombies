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
  peas = 2,
  cherry = 3,
  cactus = 4,
  nut = 5,
  lettuce = 6,
  watermelon = 7
};

struct field {
  enum PLANTS plants[5][10];
  int cycles[5][10];
  int cooldown[7];
  int sun_cycles;
};

void init_field(struct field* fld);

void init(struct field* fld);
void draw_field(struct field* fld, int* suns, enum PLANTS cur);

int movement(int y, int x, struct field* fld, enum PLANTS* cur, int* sun);
enum PLANTS select(int y, int x, struct field* fld, int sun);

void draw_plant(int y, int x, enum PLANTS type, int color);
void draw_sunflower(int y, int x, int color);
void draw_peas(int y, int x, int color);
void draw_cherry(int y, int x, int color);
void draw_cactus(int y, int x, int color);
void draw_nut(int y, int x, int color);
void draw_lettuce(int y, int x, int color);
void draw_watermelon(int y, int x, int color);
void draw_empty(int y, int x, int color);

int cost(enum PLANTS type);
int cooldown(enum PLANTS type);

void sun_cycle(struct field* fld, int* suns);
void cooldown_cycle(struct field* fld);

#endif