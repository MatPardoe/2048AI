IDIR = include/
CFLAGS= -I $(IDIR)

all: Tidy.o SmoothGreedy.o Positional.o Greedy.o MinMax.o ExpectiMax.o RandomDirection.o ControlerFactory.o Board.o main.cpp
	g++ $(CFLAGS) main.cpp *.o -o 2048AI

Board.o: src/Board.cpp include/Board.h
	g++ -c $(CFLAGS) src/Board.cpp

ControlerFactory.o: src/ControlerFactory.cpp include/ControlerFactory.h include/Greedy.h include/Positional.h include/Tidy.h include/SmoothGreedy.h include/Controler.h include/RandomDirection.h include/MinMax.h include/ExpectiMax.h include/Evaluation.h
	g++ -c $(CFLAGS) src/ControlerFactory.cpp

ExpectiMax.o: src/ExpectiMax.cpp include/ExpectiMax.h include/Controler.h include/Board.h include/Evaluation.h
	g++ -c $(CFLAGS) src/ExpectiMax.cpp

MinMax.o: src/MinMax.cpp include/MinMax.h include/Controler.h include/Board.h include/Evaluation.h
	g++ -c $(CFLAGS) src/MinMax.cpp

RandomDirection.o: src/RandomDirection.cpp include/RandomDirection.h include/Controler.h include/Board.h
	g++ -c $(CFLAGS) src/RandomDirection.cpp

Greedy.o: src/Greedy.cpp include/Greedy.h include/Board.h include/Evaluation.h
	g++ -c $(CFLAGS) src/Greedy.cpp

Positional.o: src/Positional.cpp include/Positional.h include/Board.h include/Evaluation.h
	g++ -c $(CFLAGS) src/Positional.cpp

SmoothGreedy.o: src/SmoothGreedy.cpp include/SmoothGreedy.h include/Board.h include/Evaluation.h
	g++ -c $(CFLAGS) src/SmoothGreedy.cpp

Tidy.o: src/Tidy.cpp include/Tidy.h include/Board.h include/Evaluation.h
	g++ -c $(CFLAGS) src/Tidy.cpp

clean:
	rm -rf 2048AI Tidy.o SmoothGreedy.o Positional.o Greedy.o MinMax.o ExpectiMax.o RandomDirection.o ControlerFactory.o Board.o
