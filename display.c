#include "display.h"

int displayRansom() {
  initscr();
  cbreak();
  noecho();

  mvaddch(0, 0, '+');
  mvaddch(LINES - 1, 0, '-');
  mvaddstr(10, 30, "your files have been encrypted");
  refresh();

  getch();

  endwin();

  return 0;
}
