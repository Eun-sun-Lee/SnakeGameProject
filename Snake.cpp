#include"Snake.h"

Snake::Snake(Element &map, int bodyNum) {
  stage = &map;
  size = bodyNum + 1;
  maxSize = size;
  direction = 'r';
  dead = false;
  growthNum = 0;
  gateNum = 0;
  inGate = false;
  reduceNum = 0;
  cnt = 0;
}

Snake::~Snake() {
  delete stage;
}

// new Snake
void Snake::init_snake_pos(int x, int y) {
  for(int i = 1; i < snake.size(); i++) {
    if(stage->maps[x][y-i] == 1) {
      return;
    }
  }
  for(int i = 0; i < size; i++) {
    snake.push_back(make_pair(x, y-i));
  }
  headPosX = snake[0].first;
  headPosY = snake[0].second;
  tailPosX = snake[size-1].first;
  tailPosY = snake[size-1].second;

  stage->Update(snake[0].first, snake[0].second, '4');
  for(int i = 1; i < size; i++) {
    stage->Update(snake[i].first, snake[i].second, '3');
  }
}

void Snake::move(int ch) {
  for(int i = size-1; i > 0; i--) {
    snake[i].first = snake[i-1].first;
    snake[i].second = snake[i-1].second;
  }
  switch (ch) {
    case KEY_LEFT:
      if(direction != 'r') {
        direction = 'l';
      }
      else {
        dead = true;
        return;
      }
      break;
    case KEY_RIGHT:
      if(direction != 'l') {
        direction = 'r';
      }
      else {
        dead = true;
        return;
      }
      break;
    case KEY_UP:
      if(direction != 'd') {
        direction = 'u';
      }
      else {
        dead = true;
        return;
      }
      break;
    case KEY_DOWN:
      if(direction != 'u') {
        direction = 'd';
      }
      else {
        dead = true;
        return;
      }
      break;
  }
  if(direction == 'l') {
    headPosY -= 1;
    usleep(100000);
  }
  else if(direction == 'r') {
    headPosY += 1;
    usleep(100000);
  }
  else if(direction == 'u') {
    headPosX -= 1;
    usleep(200000);
  }
  else if(direction == 'd') {
    headPosX += 1;
    usleep(200000);
  }
  Collision(stage->maps[headPosX][headPosY]);
  if(!dead) {
    snake[0].first = headPosX;
    snake[0].second = headPosY;

    stage->Update(tailPosX, tailPosY, '0');
    tailPosX = snake[size-1].first;
    tailPosY = snake[size-1].second;
    stage->Update(headPosX, headPosY, '4');

    for(int i = 1; i < size; i++) {
      stage->Update(snake[i].first, snake[i].second, '3');
    }
  }
  if(inGate) {
    if(cnt > size) {
      inGate = false;
    }
    cnt++;
  }
}

bool Snake::isDead() {
  return dead;
}

void Snake::Collision(char type) {
  if(type == '1' || type == '2' || type == '3') {
    dead = true;
  }
  else if(type == '5') {
    inGate = true;
    gateNum += 1;
    int gx, gy;
    bool isup, isdown, isleft, isright;
    if(headPosY == stage->gate_X[0] && headPosX == stage->gate_Y[0]){
      gx = stage->gate_X[1];
      gy = stage->gate_Y[1];
    }
    else{
      gx = stage->gate_X[0];
      gy = stage->gate_Y[0];
    }

    if(gx == 0){
      changeDirection('r', gx, gy);
    }
    else if(gx == WIDTH-1){
      changeDirection('l', gx, gy);
    }
    else if(gy == 0){
      changeDirection('d', gx, gy);
    }
    else if(gy == HEIGHT-1){
      changeDirection('u', gx, gy);
    }
    else{
      if(direction == 'r') {
        if(stage->maps[gy][gx+1] != '1' && stage->maps[gy][gx+1] != '2') changeDirection('r', gx, gy);
        else if(stage->maps[gy+1][gx] != '1' && stage->maps[gy+1][gx] != '2') changeDirection('d', gx, gy);
        else if(stage->maps[gy-1][gx] != '1' && stage->maps[gy-1][gx] != '2') changeDirection('u', gx, gy);
        else if(stage->maps[gy][gx-1] != '1' && stage->maps[gy][gx-1] != '2') changeDirection('l', gx, gy);
      }
      else if(direction == 'd') {
        if(stage->maps[gy+1][gx] != '1' && stage->maps[gy+1][gx] != '2') changeDirection('d', gx, gy);
        else if(stage->maps[gy][gx-1] != '1' && stage->maps[gy][gx-1] != '2') changeDirection('l', gx, gy);
        else if(stage->maps[gy][gx+1] != '1' && stage->maps[gy][gx+1] != '2') changeDirection('r', gx, gy);
        else if(stage->maps[gy-1][gx] != '1' && stage->maps[gy-1][gx] != '2') changeDirection('u', gx, gy);
      }
      else if(direction == 'l') {
        if(stage->maps[gy][gx-1] != '1' && stage->maps[gy][gx-1] != '2') changeDirection('l', gx, gy);
        else if(stage->maps[gy-1][gx] != '1' && stage->maps[gy-1][gx] != '2') changeDirection('u', gx, gy);
        else if(stage->maps[gy+1][gx] != '1' && stage->maps[gy+1][gx] != '2') changeDirection('d', gx, gy);
        else if(stage->maps[gy][gx+1] != '1' && stage->maps[gy][gx+1] != '2') changeDirection('r', gx, gy);
      }
      else if(direction == 'u') {
        if(stage->maps[gy-1][gx] != '1' && stage->maps[gy-1][gx] != '2') changeDirection('u', gx, gy);
        else if(stage->maps[gy][gx+1] != '1' && stage->maps[gy][gx+1] != '2') changeDirection('r', gx, gy);
        else if(stage->maps[gy][gx-1] != '1' && stage->maps[gy][gx-1] != '2') changeDirection('l', gx, gy);
        else if(stage->maps[gy+1][gx] != '1' && stage->maps[gy+1][gx] != '2') changeDirection('d', gx, gy);
      }
    }
  }
  else if(type == '6') {
    Growth();
  }
  else if(type == '7') {
    Reduce();
  }
}

void Snake::Growth() {
  snake.push_back(make_pair(tailPosX, tailPosY));
  size+=1;
  if(size > maxSize)
    maxSize += 1;
  growthNum += 1;
}

void Snake::Reduce() {
  snake.pop_back();
  stage->Update(tailPosX, tailPosY, '0');
  tailPosX = snake[size-1].first;
  tailPosY = snake[size-1].second;
  size-=1;
  if(size < 3) {
    dead = true;
  }
  reduceNum += 1;
}

void Snake::changeDirection(char directions, int gx1, int gy1){
  if(directions == 'u'){
    headPosY = gx1;
    headPosX = gy1 - 1;
    direction = 'u';
  }
  else if(directions == 'd'){
    headPosY = gx1;
    headPosX = gy1 + 1;
    direction = 'd';
  }
  else if(directions == 'l'){
    headPosY = gx1 - 1;
    headPosX = gy1;
    direction = 'l';
  }
  else if(directions == 'r'){
    headPosY = gx1 + 1;
    headPosX = gy1;
    direction = 'r';
  }
}
