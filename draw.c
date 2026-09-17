#include "draw.h"

void init_field(struct field* fld) {
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 10; ++j) fld->plants[i][j] = empty;
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
  init_field(fld);
}

void draw_field(struct field* fld, int* suns) {
  clear();
  cchar_t ch_w;
  for (int xx = 0; xx < 32; ++xx) {
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

  draw_sunflower(0, 7, 1);
  draw_peanut(0, 10, 1);
  draw_cherry(0, 15, 1);
  draw_cactus(0, 19, 1);
  draw_nut(0, 22, 1);
  draw_latuce(0, 25, 1);
  draw_watermelon(0, 29, 1);

  for (int yy = 3; yy < 8; ++yy)
    for (int xx = 2; xx < 32; ++xx) mvaddch(yy, xx, '.');

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 10; ++j)
      if (fld->plants[i][j] != empty)
        draw_plant(i + 3, j * 3, fld->plants[i][j]);
}

int movement(int y, int x, struct field* fld, enum PLANTS* cur) {
  if (y > 8 || y < 3 || x > 32 || x < 3) return 1;
  if (*cur != empty) {
    fld->plants[y - 3][x / 3] = *cur;
  }
  return 0;
}

void draw_plant(int y, int x, enum PLANTS type) {
  mvprintw(17, 0, "draw: y=%d, x=%d", y, x);
  switch (type) {
    case sunflower:
      draw_sunflower(y, x, 0);
      break;
    case peanut:
      draw_peanut(y, x, 0);
      break;
    case cherry:
      draw_cherry(y, x, 0);
      break;
    case cactus:
      draw_cactus(y, x, 0);
      break;
    case nut:
      draw_nut(y, x, 0);
      break;
    case latuce:
      draw_latuce(y, x, 0);
      break;
    case watermelon:
      draw_watermelon(y, x, 0);
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
  mvaddch(y, x + 2, ' ');
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
