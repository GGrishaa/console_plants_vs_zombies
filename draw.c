#include "draw.h"

void init_field(struct field* fld) {
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 10; ++j) fld->plants[i][j] = empty;
  for (int i = 0; i < 7; ++i) fld->cooldown[i] = 0;
}

void init(struct field* fld) {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  mousemask(BUTTON1_PRESSED | BUTTON1_RELEASED | BUTTON1_CLICKED, NULL);
  curs_set(0);
  start_color();
  init_pair(1, 0, COLOR_GREEN);
  init_pair(2, 0, COLOR_RED);
  init_pair(3, 0, COLOR_WHITE);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_field(fld);
}

void draw_field(struct field* fld, int* suns, enum PLANTS cur) {
  clear();
  cchar_t ch_w;
  for (int xx = 0; xx < 34; ++xx) {
    mvaddch(2, xx, '#');
    mvaddch(8, xx, '#');
  }
  setcchar(&ch_w, BRAIN, A_NORMAL, 0, NULL);
  for (int yy = 3; yy < 8; ++yy) mvadd_wch(yy, 0, &ch_w);

  setcchar(&ch_w, SUN, A_NORMAL, 0, NULL);
  mvadd_wch(0, 1, &ch_w);
  mvprintw(0, 2, "%d", *suns);

  mvprintw(1, 8, "%d", 50);
  mvprintw(1, 11, "%d", 100);
  mvprintw(1, 15, "%d", 100);
  mvprintw(1, 19, "%d", 75);
  mvprintw(1, 22, "%d", 50);
  mvprintw(1, 25, "%d", 125);
  mvprintw(1, 29, "%d", 300);

  draw_sunflower(0, 7, 1 + (fld->cooldown[0] > 0));
  draw_peanut(0, 10, 1 + (fld->cooldown[1] > 0));
  draw_cherry(0, 14, 1 + (fld->cooldown[2] > 0));
  draw_cactus(0, 18, 1 + (fld->cooldown[3] > 0));
  draw_nut(0, 21, 1 + (fld->cooldown[4] > 0));
  draw_latuce(0, 24, 1 + (fld->cooldown[5] > 0));
  draw_watermelon(0, 28, 1 + (fld->cooldown[6] > 0));

  for (int yy = 3; yy < 8; ++yy)
    for (int xx = 2; xx < 34; ++xx) mvaddch(yy, xx, '.');

  attron(COLOR_PAIR(4));
  for (int yy = 3; yy < 8; ++yy)
    for (int xx = 2; xx < 34; xx += 3) mvaddch(yy, xx, '.');
  attroff(COLOR_PAIR(4));

  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 10; ++j)
      if (fld->plants[i][j] != empty)
        draw_plant(i + 3, j * 3 + 3, fld->plants[i][j], 0);

  mvprintw(0, 40, "selected:");
  draw_plant(0, 50, cur, 3);
}

int movement(int y, int x, struct field* fld, enum PLANTS* cur) {
  if (y == 0) {
    enum PLANTS picked = select(y, x, fld);
    if (picked != empty) *cur = picked;
    return 1;
  }
  if (y < 3 || y > 7) return 1;
  if (x < 3 || x > 31) return 1;
  if ((x - 3) % 3 == 2) return 1;
  if (*cur == empty) return 1;
  fld->plants[y - 3][(x - 3) / 3] = *cur;
  *cur = empty;
  return 0;
}

enum PLANTS select(int y, int x, struct field* fld) {
  if (y > 0) return empty;
  if (x >= 8 && x <= 9 && fld->cooldown[0] <= 0) return sunflower;
  if (x >= 11 && x <= 12 && fld->cooldown[1] <= 0) return peanut;
  if (x >= 15 && x <= 16 && fld->cooldown[2] <= 0) return cherry;
  if (x >= 19 && x <= 20 && fld->cooldown[3] <= 0) return cactus;
  if (x >= 22 && x <= 23 && fld->cooldown[4] <= 0) return nut;
  if (x >= 25 && x <= 26 && fld->cooldown[5] <= 0) return latuce;
  if (x >= 29 && x <= 30 && fld->cooldown[6] <= 0) return watermelon;
  return empty;
}

void draw_plant(int y, int x, enum PLANTS type, int color) {
  switch (type) {
    case sunflower:
      draw_sunflower(y, x, color);
      break;
    case peanut:
      draw_peanut(y, x, color);
      break;
    case cherry:
      draw_cherry(y, x, color);
      break;
    case cactus:
      draw_cactus(y, x, color);
      break;
    case nut:
      draw_nut(y, x, color);
      break;
    case latuce:
      draw_latuce(y, x, color);
      break;
    case watermelon:
      draw_watermelon(y, x, color);
      break;
    default:
      break;
  }
}

void draw_sunflower(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, SUNFLOWER, A_NORMAL, 0, NULL);
  mvadd_wch(y, x, &ch_w);
  if (color) attroff(COLOR_PAIR(color));
}

void draw_peanut(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, PEANUT, A_NORMAL, 0, NULL);
  mvadd_wch(y, x, &ch_w);
  if (color) attroff(COLOR_PAIR(color));
}

void draw_cherry(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, CHERRY, A_NORMAL, 0, NULL);
  mvadd_wch(y, x, &ch_w);
  if (color) attroff(COLOR_PAIR(color));
}

void draw_cactus(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, CACTUS, A_NORMAL, 0, NULL);
  mvadd_wch(y, x, &ch_w);
  if (color) attroff(COLOR_PAIR(color));
}

void draw_nut(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, NUT, A_NORMAL, 0, NULL);
  mvadd_wch(y, x, &ch_w);
  if (color) attroff(COLOR_PAIR(color));
}

void draw_latuce(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, LATUCE, A_NORMAL, 0, NULL);
  mvadd_wch(y, x, &ch_w);
  if (color) attroff(COLOR_PAIR(color));
}

void draw_watermelon(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, WATERMELON, A_NORMAL, 0, NULL);
  mvadd_wch(y, x, &ch_w);
  if (color) attroff(COLOR_PAIR(color));
}
