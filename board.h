// #pragma once
#ifndef BOARD_H_
#define BOARD_H_

class point {
	float delay; //	trzeba jeszcze zrobic ograniczenia zwiazane z czasem...
	int X, Y, Z;
public:
	char state;
	friend class board;
	point(){
		state = '0';
	}
protected:

};

class board {

	int X, Y, Z;
	int counter;
public:
	int curX, curY, curZ;
	point ***array; // Tablica numerowana [Z][Y][X]
	board(int, int, int);
	~board();
	friend class VDec;
	void display();
	void moveX(int, int);
	void moveY(int, int);
	void algoGreedy(int xStart, int yStart, int zStart, VDec &);
	void updateVDec();
	void traceRouteFromVDec(VDec &Dec);
	bool stop();
	void jump(int x, int y);
protected:

};

#endif // BOARD_H_