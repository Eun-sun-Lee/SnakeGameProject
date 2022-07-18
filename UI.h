#include<ncurses.h>
#include<iostream>
#include<unistd.h>
#include"Snake.h"
using namespace std;


class UI {
  WINDOW *gameboard;
  WINDOW *scoreboard;
  WINDOW *missionboard;
  Element *stage;
  Snake *player;
public:
  bool isClear;

  UI(int level);
  ~UI();
  void InitWindow();
  void InitGameboard();
  void InitScoreboard();
  void InitMissionboard();

  void Run(); 
  void GameOver();

  void UpdateGameBoard();
  void UpdateScoreBoard();
  void UpdateMissionBoard();

  char *to_char(string s);

  string isAchieve(int cur, int goal);

  bool checkClear();
};
