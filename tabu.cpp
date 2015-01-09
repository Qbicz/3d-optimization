#include "stdafx.h"
#include "tabu.h"
#include <iostream>
using namespace std;

void tabu::display(){
	int i, j, k;
	for (i = 0; i<Z; i++){
		cout << endl;
		for (j = 0; j<5; j++){
			cout << endl;
			for(k = 0; k < size; k++)
				cout << tabu_array[i][j];			
		}
	}
}

tabu::tabu(int X, int Z){
	int i, j;
	size = X;
	tabu_array = new int**[Z];
	for (i = 0; i<Z; i++) tabu_array[i] = new int*[5];
		for(j = 0; j < 5; j++) tabu_array[i][j] = new int[X];
	for (i = 0; i<5; i++) // pocz¹tkowo wype³niamy -1
		for (j = 0; j<size; j++)
			tabu_array[i][j] = -1;
}
void tabu::updatetabu(int X0, int X1, int Y0, int Y1, int Z){
	int position;
	for(position = 0; position < size; position++){
		if(tabu_array[0][position] == -1){
			tabu_array[Z][0][position] = X0;
			tabu_array[Z][1][position] = X1;
			tabu_array[Z][2][position] = Y0;
			tabu_array[Z][3][position] = Y1;
		}
	}
}

tabu::~tabu(){
	delete[] tabu_array;
}
