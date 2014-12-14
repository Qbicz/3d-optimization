//#pragma once
#ifndef TABU_H_
#define TABU_H_

class tabu {
	int size;
public:
	int **tabu_array;// Ma trzy wiersze o d�ugo�ci size(parametr optymalizacyjny), 0-X,1-Y,3-Z, przy sprawdzaniu ruch�w na li�cie tabu b�dziemy brali uwag� co dwie s�siednie pozycje
	tabu(int);
	~tabu();
	void display();
	friend class board;
};

#endif
