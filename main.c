#include <ncurses.h>

#include "draw.h"

int main() {
  int suns = 50;
  struct field fld;
  enum PLANTS cur = sunflower;
  init(&fld);
  MEVENT event;
  draw_field(&fld, &suns);
  int ch, y, x;
  while ((ch = getch()) != 'q') {
    if (ch == KEY_MOUSE && getmouse(&event) == OK &&
        event.bstate & BUTTON1_CLICKED) {
      y = event.y;
      x = event.x;
      mvprintw(15, 0, "click: y=%d, x=%d", y, x);
      movement(y, x, &fld, &cur);
      draw_field(&fld, &suns);
    }
  }
  endwin();
  return 0;
}
