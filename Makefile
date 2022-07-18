CC = g++


main : main.o Intro.o SnakeGame.o Snake.o Element.o UI.o GameOver.o Pass.o Clear.o
	g++ -o main main.o Intro.o SnakeGame.o Snake.o Element.o UI.o GameOver.o Pass.o Clear.o -lncurses -std=c++11

main.o : main.cpp
	g++ -c main.cpp -lncurses -std=c++11

Intro.o : Intro.cpp
	g++ -c Intro.cpp -lncurses -std=c++11

SnakeGame.o : SnakeGame.cpp
	g++ -c SnakeGame.cpp -lncurses -std=c++11

Snake.o : Snake.cpp
	g++ -c Snake.cpp -lncurses -std=c++11

Element.o : Element.cpp
	g++ -c Element.cpp -std=c++11 -lncurses -std=c++11

UI.o : UI.cpp
	g++ -c UI.cpp -lncurses -std=c++11

GameOver.o : GameOver.cpp
	g++ -c GameOver.cpp -lncurses -std=c++11

Pass.o : Pass.cpp
	g++ -c Pass.cpp -lncurses -std=c++11

Clear.o : Clear.cpp
	g++ -c Clear.cpp -lncurses -std=c++11

clean : 
	rm -rf *.o *.exe
