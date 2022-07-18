#include"Intro.h"

Intro::Intro() {
}

void Intro::Draw() {
  initscr();
  start_color();
  curs_set(false);
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  attron(A_BOLD);
  attron(COLOR_PAIR(1));
  mvprintw(LINES/2, COLS/2-COLS/20, "SNAKE GAME");
  attroff(A_BOLD);
  attron(A_BLINK);
  mvprintw(LINES/2+LINES/10, COLS/2-COLS/11, "Press any key to start");
  attroff(A_BLINK);
  refresh();
  getch();
  endwin();
}
