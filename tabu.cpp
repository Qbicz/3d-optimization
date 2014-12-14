#include "stdafx.h"
#include "tabu.h"
#include <iostream>
using namespace std;

void tabu::display(){
	int i, j;
	for (i = 0; i<3; i++){
		cout << endl;
		for (j = 0; j<size; j++)
			cout << tabu_array[i][j];
	}
}

tabu::tabu(int X){
	int i, j;
	size = X;
	tabu_array = new int*[3];
	for (i = 0; i<3; i++) tabu_array[i] = new int[X];
	for (i = 0; i<3; i++) // pocz¹tkowo wype³niamy zerami
		for (j = 0; j<size; j++)
			tabu_array[i][j] = 0;
}

tabu::~tabu(){
	delete[] tabu_array;
}
