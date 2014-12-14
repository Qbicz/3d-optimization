// Wektor decyzyjny
// Model matematyczny ruchu drukarki 3D

#include <iostream>
#include "stdafx.h" // tylko dla Visual Studio
#include "VDec.h"

VDec::VDec(int X, int Y, int Z)
{
	int*** Dec;
	N = 0;					// numer ruchu zawsze na poczatku 0
	Dec = new int **[Z]; 	// X,Y,E
	for(int i=0; i<Z; i++) 	// najpierw warstwa
	{
		Dec[i] = new int *[H]; // "szerokosc"
		for(int j=0; j<H; j++)
		{
			Dec[i][j] = new int [X*Y]; // "dlugosc"
		}
	}
	// w przyszlosci lap std::bad_alloc

	int max = X;
	if (Y > max)
		max = Y;
	
	for(int i=0; i<Z; i++)
		for(int j=0; j<H; j++)
			for(int k=0; k<max; k++)
				Dec[i][j][k] = 0; // inicjalizacja
}

//VDec::VDec(VDec &original) // konstruktor kopiujacy
//{
//	// dodatkowe max(X,Y) kolumn
//}

VDec::~VDec()
{
	delete[] Dec;
}

int VDec::ObliczKoszt()			// obecnie tylko koszt ruchow 'lejacych'
{
	T = 0;
	for (int z = 0; z < Z; z++)
		for (int i = 0; i < X*Y; i++)
			T += Dec[z][H-1][i]; // T = suma E
	return T;
}

void VDec::Wyswietl()
{
	for(int i=0; i<Z; i++)
		for(int j=0; j<H; j++)
			for(int k=0; k<N; k++)
				std::cout << Dec[i][j][k]; // prezentacja
}

void VDec::updateVDec(board &Rozw1)
{	// poziom 0 - X, poziom 1 - Y, poziom 2 - E
	Dec[Rozw1.curZ][0][N] = Rozw1.curX;		// DONE::zamienic na przeslanie przez referencje
	Dec[Rozw1.curZ][1][N] = Rozw1.curY;
	N++;
}

void VDec::simplifyVDec(board &Rozw1)
{
	for (int i = 1; i < N; i++)		// this.N
	{
		if (Dec[Rozw1.curZ][0][i - 1] != Dec[Rozw1.curZ][0][i] && Dec[Rozw1.curZ][1][i - 1] != Dec[Rozw1.curZ][1][i])
		{	// wykryto ruch ukosny (zlozony)
			for (int j = N; j >= i; j--)
			{	// rozsuniecie wektora, lacznie z i-tym elementem
				Dec[Rozw1.curZ][0][j + 1] = Dec[Rozw1.curZ][0][j];
				Dec[Rozw1.curZ][1][j + 1] = Dec[Rozw1.curZ][1][j];
			}
			Dec[Rozw1.curZ][0][i] = Dec[Rozw1.curZ][0][i + 1]; // punkt posredni
			Dec[Rozw1.curZ][1][i] = Dec[Rozw1.curZ][1][i - 1];
		}
	}
}

void VDec::swap(int A, int B, int Z){ //A,B-numery kolumn, Z-numer warstwy, w której zmieniamy
	int a, b; //pomocnicze
	a = Dec[Z][0][A];
	b = Dec[Z][1][A];
	Dec[Z][0][A] = Dec[Z][0][B];
	Dec[Z][1][A] = Dec[Z][1][B];
	Dec[Z][0][B] = a;
	Dec[Z][1][B] = b;
}

int VDec::FunctionValue(board Pattern){ // Wartoœæ funkcji celu :)
	int i;
	bool prev, flag = true; // true-poziomo, false-pionowo
	if (Dec[Z][0][0] == Dec[Z][0][1]) prev = false;
	else prev = true;
	for (i = 0; i<N - 1; i++){
		if (Dec[Z][0][i] == Dec[Z][0][i + 1]){
			Pattern.moveY(Dec[Z][1][i], Dec[Z][1][i + 1]);
			flag = false;
		}
		else{
			Pattern.moveX(Dec[Z][0][i], Dec[Z][0][i + 1]);
			flag = true;
		}
		if (prev != flag) Pattern.counter++; // dodaje counter jako skladnik klasy board, czy w funkcji board::stop chodzi o ta sama zmienna?
		prev = flag;
	}
	return Pattern.counter;
}


//int main(void)
//{
//	// <czyta dane z pliku>
//	VDec Dec1;
//	Dec1.Wyswietl();
//}


