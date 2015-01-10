// Wektor decyzyjny
// Model matematyczny ruchu drukarki 3D

#include <iostream>
#include "stdafx.h" // tylko dla Visual Studio
#include "VDec.h"

VDec::VDec(int X0, int Y0, int Z0)
{
	X = X0;
	Y = Y0;
	Z = Z0;
	int*** Dec;
	N = 0;					// numer ruchu zawsze na poczatku 0
	Dec = new int **[Z]; 	// X,Y,E
	for(int i=0; i<Z; i++) 	// najpierw warstwa
	{
		Dec[i] = new int *[H]; // "szerokosc"
		for(int j=0; j<H; j++)
		{
			Dec[i][j] = new int [10*(X+Y)]; // "dlugosc"
		}
	}
	// w przyszlosci lap std::bad_alloc

	int max = X;
	if (Y > max)
		max = Y;
	
	for(int i=0; i<Z; i++)
		for(int j=0; j<H; j++)
			for(int k=0; k<max; k++)
				Dec[i][j][k] = -1; // inicjalizacja
}

//VDec::VDec(VDec &original) // konstruktor kopiujacy
//{
// // dodatkowe max(X,Y) kolumn
//}

VDec::~VDec()
{
	delete[] Dec;
}

int VDec::ObliczKoszt()			// obecnie tylko koszt ruchow 'lejacych'
{
	T = 0;
	for (int z = 0; z < Z; z++)
		for (int i = 0; i < 10*(X+Y); i++)
			T += Dec[z][H-1][i]; // T = suma E
	return T;
}

void VDec::Wyswietl()
{
	for (int i = 0; i < Z; i++)
	{
	std::cout << "Poziom " << Z << std::endl;
	for (int j = 0; j < H; j++)
	{
		std::cout << std::endl;
		for (int k = 0; k < N; k++)
			std::cout << Dec[i][j][k]; // prezentacja
	}
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

void VDec::swap(int A, int B, int Z0, tabu &lista){ //A,B-numery kolumn, Z-numer warstwy, w której zmieniamy
	int i, a, b; //pomocnicze
	bool flag = true;
	for(i = 0; lista[Z0][0][i+1] = -1; i++)
		if(lista[Z0][0][i] == Dec[Z0][0][A] 
		&& lista[Z0][1][i] == Dec[Z0][0][B] 
		&& lista[Z0][2][i] == Dec[Z0][1][A] 
		&& lista[Z0][3][i] == Dec[Z0][1][B])
			flag = false;
	if(flag){
		a = Dec[Z][0][A];
		b = Dec[Z][1][A];
		Dec[Z][0][A] = Dec[Z][0][B];
		Dec[Z][1][A] = Dec[Z][1][B];
		Dec[Z][0][B] = a;
		Dec[Z][1][B] = b;
	}
}

int VDec::FunctionValue(board Pattern){ // Wartoœæ funkcji celu :)
	int i;
	Pattern.counter = 0;
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






