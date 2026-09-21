#include <ncurses.h>

#include "draw.h"

int main() {
  int suns = 50;
  struct field fld;
  enum PLANTS cur = empty;
  init(&fld);
  MEVENT event;
  draw_field(&fld, &suns, cur);
  int ch, y, x;
  while (true) {
    ch = getch();
    if (ch == KEY_MOUSE && getmouse(&event) == OK &&
        event.bstate & BUTTON1_CLICKED) {
      y = event.y;
      x = event.x;
      movement(y, x, &fld, &cur, &suns);
      draw_field(&fld, &suns, cur);
    } else if (ch == 'q')
      break;
    sun_cycle(&fld, &suns);
    cooldown_cycle(&fld);
    // attack_cycle();
    draw_field(&fld, &suns, cur);
  }
  endwin();
  return 0;
}
