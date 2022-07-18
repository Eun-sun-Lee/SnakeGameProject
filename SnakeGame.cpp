#include"SnakeGame.h"

SnakeGame::SnakeGame(int objLevel) {
  intro = new Intro();
  clearScene = new Pass();
  overScene = new GameOver();
  endScene = new Clear();
  this->objLevel = objLevel;
}
void SnakeGame::startGame() {
  intro->Draw();
  while(true) {
    inGame = new UI(curLevel);
    inGame->Run();
    if(inGame->isClear) {
      clearScene->Draw();
      curLevel += 1;
      if(curLevel > objLevel) break;
    }
    else {
      overScene->Draw();
    }
  }
  endScene->Draw();
}
