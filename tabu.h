//#pragma once
#ifndef TABU_H_
#define TABU_H_

class tabu {
	int size, Z; //Z-warstwa
public:
	int **tabu_array;// Ma trzy wiersze o długości size(parametr optymalizacyjny), 0-X,1-Y,3-Z, przy sprawdzaniu ruchów na liście tabu będziemy brali uwagę co dwie sąsiednie pozycje
	tabu(int);
	~tabu();
	void display();
	friend class board;
	void updatetabu(int X0, int X1, int Y0, int Y1);
};

#endif
