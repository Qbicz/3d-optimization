//#pragma once
#ifndef TABU_H_
#define TABU_H_

class tabu {
	int size, Z; //Z-warstwa
public:
	int ***tabu_array;
	tabu(int);
	~tabu();
	void display();
	friend class board;
	void updatetabu(int X0, int X1, int Y0, int Y1, int Z0);
};

#endif
