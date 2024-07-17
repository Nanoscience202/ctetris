#include <ncurses.h>
#include <stdbool.h>

void init();
void quit();

int main(void) {
  init();

  int cols = 10;
  int rows = 20;

  quit();
  return 0;
}

void init() {
  initscr();
  cbreak();
  keypad(stdscr, true);
  clear();
  refresh();
}

void quit() {
  clear();
  printw("Press any key to exit");
  refresh();
  getch();
  endwin();
}
