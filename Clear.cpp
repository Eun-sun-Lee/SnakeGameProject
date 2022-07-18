#include"Clear.h"

Clear::Clear() {

}

void Clear::Draw() {
  initscr();
  start_color();
  curs_set(false);
  attron(A_BOLD | A_STANDOUT);
  attron(COLOR_PAIR(1));
  mvprintw(LINES/2, COLS/2-COLS/10, "CONGRATURAION! YOU\'VE CLEARED THIS GAME!");
  attroff(A_BOLD);
  refresh();
  getch();
  endwin();
}
