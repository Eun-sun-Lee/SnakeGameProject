#include"Element.h"

Element::Element(int level) {
  this->mapUrl = "stage/stage" + to_string(level) + ".txt";
  map_txt.open(this->mapUrl);
  for(int i = 0; i < 2; i++){
    gate_X[i] = 0;
    gate_Y[i] = 0;
  }
}
//
Element::~Element(){
}

void Element::Init(){
  int mapHeight = 0;
  while (!map_txt.eof())
  {
    char temp[200];
    map_txt.getline(temp, 200);
    if(mapHeight == 0) {
      string tmp;
      for(int i = 0; i < 3; i++) {
        tmp += temp[i];
      }
      objLen = stoi(tmp);
    }
    else if(mapHeight == 1) {
      string tmp;
      for(int i = 0; i < 3; i++) {
        tmp += temp[i];
      }
      objGrowth = stoi(tmp);
    }
    else if(mapHeight == 2) {
      string tmp;
      for(int i = 0; i < 3; i++) {
        tmp += temp[i];
      }
      objReduce = stoi(tmp);
    }
    else if(mapHeight == 3) {
      string tmp;
      for(int i = 0; i < 3; i++) {
        tmp += temp[i];
      }
      objGate = stoi(tmp);
    }
    else {
      for (int i = 0; i < WIDTH; i++)
      {
        maps[mapHeight-4][i] = temp[i];
      }
    }
    mapHeight++;
  }
}

void Element::Render(WINDOW *board){
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(3, COLOR_RED, COLOR_RED);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(8, COLOR_CYAN, COLOR_CYAN);
  init_pair(9, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(7, COLOR_GREEN, COLOR_GREEN);
  init_pair(10, COLOR_BLACK, COLOR_BLACK);
  for(int i = 0; i < HEIGHT; i++){
    for(int j = 0; j < WIDTH; j++){
      switch (maps[i][j])
      {
        case '0':
          mvwaddch(board, i+1, j+1, '-' | COLOR_PAIR(5)); // can move
          break;
        case '1':
          mvwaddch(board, i+1, j+1, '#' | COLOR_PAIR(2)); // block
          break;
        case '2':
          mvwaddch(board, i+1, j+1, '@' | COLOR_PAIR(10)); // wall
          break;
        case '4':
          mvwaddch(board, i+1, j+1, 'O' | COLOR_PAIR(3)); // head
          break;
        case '3':
          mvwaddch(board, i+1, j+1, 'X' | COLOR_PAIR(4)); // body
          break;
        case '5':
          mvwaddch(board, i+1, j+1, '^' | COLOR_PAIR(7)); // gate
          break;
        case '6':
          mvwaddch(board, i+1, j+1, 'G' | COLOR_PAIR(8)); // Growth
          break;
        case '7':
          mvwaddch(board, i+1, j+1, 'L' | COLOR_PAIR(9)); // Loss
          break;
      }
    }
  }
  wrefresh(board);
}

void Element::Update(int x, int y, char value) {
  maps[x][y] = value;
}

void Element::makeItem(){
  itemStartTime = time(NULL);

  srand(time(NULL));
  int num = 0;  // current item_count
  int growthItem = rand() % 2 + 2;  // Growth Item count
  int growthItemCount = 0;  // current Growth Item count
  int tmpx, tmpy;    // location

  while(num<5){ // max_item_count == 5
    tmpx = rand()%WIDTH;  
    tmpy = rand()%HEIGHT;

    if(maps[tmpy][tmpx] != '0')
      continue;

    if (growthItemCount < growthItem) {   // generate Growth Item 
      maps[tmpy][tmpx] = '6';
      num++;
      growthItemCount++;
      continue;
    }

    // generate Poison Item
    maps[tmpy][tmpx] = '7';
    num++;
  }
}
//
void Element::checkItem() {
  itemNowTime = time(NULL);

	if(itemNowTime - itemStartTime > 7){  // after 7sec passed
    for (int i=0; i<30; i++) {   // erase items
      for (int j=0; j<110; j++) {
        if (maps[i][j]=='6' || maps[i][j]=='7') maps[i][j]='0';
      }
    }
		makeItem();
	}
}

void Element::setGatepos(){
  gateStartTime = time(NULL);

  srand(time(NULL));
  int x = 0;
  int y = 0;
  int gateCount = 0;
  while(gateCount < 2){
    x = rand() % WIDTH;
    y = rand() % HEIGHT;
    if(maps[y][x] == '1'){
      maps[y][x] = '5';
      gate_X[gateCount] = x;
      gate_Y[gateCount] = y;
      gateCount++;
    }
  }
}

void Element::GateUpdate(){
  gateNowTime = time(NULL);
  if(gateNowTime - gateStartTime > 10) {
    maps[gate_Y[0]][gate_X[0]] = '1';
    maps[gate_Y[1]][gate_X[1]] = '1';
    setGatepos();
	}
}