#include"GameOver.h"

GameOver::GameOver() {

}

void GameOver::Draw() {
  initscr();
  start_color();
  curs_set(false);
  attron(A_BOLD | A_STANDOUT);
  attron(COLOR_PAIR(1));
  mvprintw(LINES/2, COLS/2-COLS/20, "GAMEOVER");
  attroff(A_BOLD);
  refresh();
  getch();
  endwin();
}
