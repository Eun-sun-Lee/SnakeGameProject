#include<ncurses.h>
#include<iostream>
#include<string>
#include<vector>
#include"Intro.h"
#include"UI.h"
#include"GameOver.h"
#include"Pass.h"
#include"Clear.h"
using namespace std;


class SnakeGame {
  bool isOver;
  Intro *intro;
  UI *inGame;
  GameOver *overScene;
  Pass *clearScene;
  Clear *endScene;
  int curLevel = 1;
  int objLevel;
public:
  SnakeGame(int objLevel);
  void startGame();
};
