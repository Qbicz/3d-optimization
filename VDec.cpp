// Wektor decyzyjny
// Model matematyczny ruchu drukarki 3D

#include <iostream>
//#include "stdafx.h" // tylko dla Visual Studio
#include "StanRozw.cpp"
#define H 3

class VDec				// wektor decyzyjny
{
	private:
		int*** Dec; 	// 3 na X*Y na Z
		int kierunek; 	// flaga - pion/poziom
		int X,Y,Z,N; 	// N - numer ruchu i kolumny VDec
		int T;			// koszt - sumaryczny czas (ilosc iteracji)
	public:
		VDec();
		VDec(int X, int Y, int Z);
		VDec(VDec &original);		// kiedy wektor sie powieksza, trzeba alokowac wiecej pamieci
		~VDec();
		friend class board;
		void Wyswietl();
		int ObliczKoszt();
		void CzytajPlik();
		void updateVDec(board &Rozw1);
		void simplifyVDec();		// zamienia ruchy zlozone na sume ruchow prostych
};

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
	for(int i=0; i<Z; i++)
		for(int j=0; j<H; j++)
			for(int k=0; k<X*Y; k++)
				Dec[i][j][k] = 0; // inicjalizacja
}

VDec::VDec(VDec &original) // konstruktor kopiujacy
{
	// dodatkowe 100 kolumn
}

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
}

void VDec::Wyswietl()
{
	for(int i=0; i<Z; i++)
		for(int j=0; j<H; j++)
			for(int k=0; k<X*Y; k++)
				std::cout << Dec[i][j][k]; // prezentacja
}

void VDec::updateVDec(board &Rozw1)
{	// poziom 0 - X, poziom 1 - Y, poziom 2 - E
	Dec[Rozw1.curZ][0][N] = Rozw1.curX;		// DONE::zamienic na przeslanie przez referencje
	Dec[Rozw1.curZ][1][N] = Rozw1.curY;
	N++;
}

void VDec::simplifyVDec()
{
	for (int i = 1; i < N; i++)		// this.N
	{
		if (Dec[curZ][0][i - 1] != Dec[curZ][0][i] && Dec[curZ][1][i - 1] != Dec[curZ][1][i])
		{	// wykryto ruch ukosny (zlozony)
			for (int j = N; j >= i; j--)
			{	// rozsuniecie wektora, lacznie z i-tym elementem
				Dec[curZ][0][j + 1] = Dec[curZ][0][j];
				Dec[curZ][1][j + 1] = Dec[curZ][1][j];
			}
			Dec[curZ][0][i] = Dec[curZ][0][i + 1]; // punkt posredni
			Dec[curZ][1][i] = Dec[curZ][1][i - 1];
		}
}

//int main(void)
//{
//	// <czyta dane z pliku>
//	VDec Dec1;
//	Dec1.Wyswietl();
//}


