// Wektor decyzyjny
// Model matematyczny ruchu drukarki 3D
#include <iostream>
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
		~VDec();
		friend class board;
		void Wyswietl();
		int ObliczKoszt();
		void CzytajPlik();
		void updateVDec();
};

VDec(int X, int Y, int Z)
{
	int*** Dec;
	N = 0;					// numer ruchu zawsze na poczatku 0
	Dec = new int **[Z]; 	// X,Y,E
	for(int i=0; i<Z; i++) 	// najpierw warstwa
	{
		Dec[i] = new int *[H] // "szerokosc"
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

~VDec()
{
	delete[] Dec;
}

int VDec::ObliczKoszt()
{
	T = 0;
	for(int z=0; z<Z, z++)
		for(int i=0; i<X*Y, i++)
			T += Dec[z][H-1][i]; // T = suma E
}

void VDec::Wyswietl()
{
	for(int i=0; i<Z; i++)
		for(int j=0; j<H; j++)
			for(int k=0; k<X*Y; k++)
				std::cout << Dec[i][j][k] = 0; // inicjalizacja
}

void VDec::updateVDec()
{	// poziom 0 - X, poziom 1 - Y, poziom 2 - E
	Dec[Rozw1.curZ][0][N] = curX;		// bardzo nieeleganckie odwolanie do konkretnego obiektu innej klasy, zamienic na przeslanie przez referencje
	Dec[Rozw1.curZ][1][N] = curY;
	N++;
}


int main(void)
{
	// <czyta dane z pliku>
	VDec Dec1;
	Dec1.Wyswietl();
}


