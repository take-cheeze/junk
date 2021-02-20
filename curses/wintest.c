#include <ncurses.h>

int main(void) {
  initscr();

  move(5, 10);
  waddstr(stdscr, "Hello, world!");
  wrefresh(stdscr);
  wgetch(stdscr);

  endwin();
  return 0;
}
