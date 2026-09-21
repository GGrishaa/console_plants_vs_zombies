#include "draw.h"

void init_field(struct field* fld) {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 10; ++j) {
      fld->plants[i][j] = empty;
      fld->cycles[i][j] = 0;
    }
  }
  for (int i = 0; i < 7; ++i) fld->cooldown[i] = 0;
  fld->sun_cycles = AUTO_SUN_CYCLE;
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
  timeout(30);
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

  mvprintw(1, 8, "%d", SUNFLOWER_COST);
  mvprintw(1, 11, "%d", PEAS_COST);
  mvprintw(1, 15, "%d", CHERRY_COST);
  mvprintw(1, 19, "%d", CACTUS_COST);
  mvprintw(1, 22, "%d", NUT_COST);
  mvprintw(1, 25, "%d", LETTUCE_COST);
  mvprintw(1, 29, "%d", WATERMELON_COST);

  draw_sunflower(0, 7, 1 + (fld->cooldown[0] > 0));
  draw_peas(0, 10, 1 + (fld->cooldown[1] > 0));
  draw_cherry(0, 14, 1 + (fld->cooldown[2] > 0));
  draw_cactus(0, 18, 1 + (fld->cooldown[3] > 0));
  draw_nut(0, 21, 1 + (fld->cooldown[4] > 0));
  draw_lettuce(0, 24, 1 + (fld->cooldown[5] > 0));
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

int movement(int y, int x, struct field* fld, enum PLANTS* cur, int* sun) {
  if (y == 0) {
    enum PLANTS picked = select(y, x, fld, *sun);
    if (picked != empty) *cur = picked;
    return 1;
  }
  if (y < 3 || y > 7) return 1;
  if (x < 3 || x > 31) return 1;
  if ((x - 3) % 3 == 2) return 1;
  if (*cur == empty) return 1;
  if (fld->plants[y - 3][(x - 3) / 3]) return 1;
  fld->plants[y - 3][(x - 3) / 3] = *cur;
  if (*cur == sunflower)
    fld->cycles[y - 3][(x - 3) / 3] = SUN_PROD_CYCLE_1;
  else
    fld->cycles[y - 3][(x - 3) / 3] = 0;
  *sun -= cost(*cur);
  fld->cooldown[(int)*cur - 1] = cooldown(*cur);
  *cur = empty;
  return 0;
}

enum PLANTS select(int y, int x, struct field* fld, int sun) {
  if (y > 0) return empty;
  if (x >= 8 && x <= 9 && fld->cooldown[0] <= 0 && sun >= SUNFLOWER_COST)
    return sunflower;
  if (x >= 11 && x <= 12 && fld->cooldown[1] <= 0 && sun >= PEAS_COST)
    return peas;
  if (x >= 15 && x <= 16 && fld->cooldown[2] <= 0 && sun >= CHERRY_COST)
    return cherry;
  if (x >= 19 && x <= 20 && fld->cooldown[3] <= 0 && sun >= CACTUS_COST)
    return cactus;
  if (x >= 22 && x <= 23 && fld->cooldown[4] <= 0 && sun >= NUT_COST)
    return nut;
  if (x >= 25 && x <= 26 && fld->cooldown[5] <= 0 && sun >= LETTUCE_COST)
    return lettuce;
  if (x >= 29 && x <= 30 && fld->cooldown[6] <= 0 && sun >= WATERMELON_COST)
    return watermelon;
  return empty;
}

void draw_plant(int y, int x, enum PLANTS type, int color) {
  switch (type) {
    case sunflower:
      draw_sunflower(y, x, color);
      break;
    case peas:
      draw_peas(y, x, color);
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
    case lettuce:
      draw_lettuce(y, x, color);
      break;
    case watermelon:
      draw_watermelon(y, x, color);
      break;
    case empty:
      draw_empty(y, x, color);
  }
}

void draw_sunflower(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, SUNFLOWER, A_NORMAL, 0, NULL);
  mvadd_wch(y, x, &ch_w);
  if (color) attroff(COLOR_PAIR(color));
}

void draw_peas(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, PEAS, A_NORMAL, 0, NULL);
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

void draw_lettuce(int y, int x, int color) {
  cchar_t ch_w;
  if (color) attron(COLOR_PAIR(color));
  setcchar(&ch_w, LETTUCE, A_NORMAL, 0, NULL);
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

void draw_empty(int y, int x, int color) {
  if (color) attron(COLOR_PAIR(color));
  mvprintw(y, x, "  ");
  if (color) attroff(COLOR_PAIR(color));
}

int cost(enum PLANTS type) {
  switch (type) {
    case empty:
      return 0;
    case sunflower:
      return SUNFLOWER_COST;
    case peas:
      return PEAS_COST;
    case cherry:
      return CHERRY_COST;
    case cactus:
      return CACTUS_COST;
    case nut:
      return NUT_COST;
    case lettuce:
      return LETTUCE_COST;
    case watermelon:
      return WATERMELON_COST;
    default:
      return 0;
  }
}

int cooldown(enum PLANTS type) {
  switch (type) {
    case empty:
      return 0;
    case sunflower:
      return FAST_CD;
    case peas:
      return FAST_CD;
    case cherry:
      return SLOW_CD;
    case cactus:
      return FAST_CD;
    case nut:
      return MIDDLE_CD;
    case lettuce:
      return FAST_CD;
    case watermelon:
      return FAST_CD;
    default:
      return 0;
  }
}

void sun_cycle(struct field* fld, int* suns) {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (fld->plants[i][j] == sunflower) {
        if (fld->cycles[i][j] <= 0) {
          *suns += 25;
          fld->cycles[i][j] = SUN_PROD_CYCLE_2;
        } else
          fld->cycles[i][j] -= 1;
      }
    }
  }
  if (fld->sun_cycles <= 0) {
    *suns += 25;
    fld->sun_cycles = AUTO_SUN_CYCLE;
  } else {
    fld->sun_cycles -= 1;
  }
}

void cooldown_cycle(struct field* fld) {
  for (int i = 0; i < 7; ++i)
    if (fld->cooldown[i] > 0) fld->cooldown[i]--;
}