//#pragma once
#ifndef TABU_H_
#define TABU_H_

class tabu {
	int size;
public:
	int **tabu_array;// Ma trzy wiersze o d³ugoœci size(parametr optymalizacyjny), 0-X,1-Y,3-Z, przy sprawdzaniu ruchów na liœcie tabu bêdziemy brali uwagê co dwie s¹siednie pozycje
	tabu(int);
	~tabu();
	void display();
	friend class board;
};

#endif
