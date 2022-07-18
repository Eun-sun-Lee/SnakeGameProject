#include<ncurses.h>
#include<string>
#include<fstream>
#include<iostream>
#include<ctime>
#include<map>
#include<cstdlib>

using namespace std;

#define WIDTH 110
#define HEIGHT 30

class Element{
  int objLen;
  int objGrowth;
  int objReduce;
  int objGate;
  string mapUrl;

public:
  ifstream map_txt;
  char maps[HEIGHT][WIDTH];
  time_t itemNowTime;
  time_t itemStartTime;

  int gate_X[2];
  int gate_Y[2];
  time_t gateNowTime;
  time_t gateStartTime;

  Element(int level); 
  ~Element();

  void Init(); 
  void Render(WINDOW *map);
  void Update(int x, int y, char value); 
  void makeItem(); 
  void checkItem(); 

  void setGatepos();
  void GateUpdate(); 
  


  int getObjLen() { return objLen; }
  int getObjGrowth() { return objGrowth; }
  int getObjReduce() { return objReduce; }
  int getObjGate() { return objGate; }

};
