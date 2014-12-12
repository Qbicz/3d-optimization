// Algo_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#define X 5
#define Y 6

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	bool board[X][Y]; //statycznie, nie bedzie czesto alokowana
	int x, y, i, j, max, maxp, tmp, ruch;
	int xStart = 0, yStart = 0;
	int droga_kierunek[4];

	x = xStart; // punkt startowy na warstwie
	y = yStart;

	// --- Znalezienie kierunku ---
	for (i = x + 1; i < X; i++)
	{	// sprawdzenie w dol
		if (board[i][y] == 0)
			droga_kierunek[0]++;
		else break;
	}

	for (j = y + 1; j < X; j++)
	{	// sprawdzenie w prawo
		if (board[x][j] == 0)
			droga_kierunek[1]++;
		else break;
	}

	for (i = x - 1; i >= 0; i--)
	{	// sprawdzenie w gore
		if (board[i][y] == 0)
			droga_kierunek[2]++;
		else break;
	}

	for (j = y - 1; j >= 0; j--)
	{	// sprawdzenie w lewo
		if (board[x][j] == 0)
			droga_kierunek[3]++;
		else break;
	}
	// Znalezienie najdluzszej drogi z obecnego miejsca - Sortowanie przez wybór
	max = droga_kierunek[0];
	for (i = 1; i < 4; i++)
	{
		if (droga_kierunek[i]>max)
			max = droga_kierunek[i];
	}
	for (i = 0; i < 4; i++)
		if (max == droga_kierunek[i])
		{
			ruch = i;
			break;
		}
	// wykonaj ruch w wybranym kierunku
	switch (ruch)
		{
		case 1: // TODO
			for (i = x + 1; i < x + max; i++)
			{	// pokrywam w dol
				if (board[i][y] == 0)
					board[i][y] = 1;
			}
			break;
		case 2:
			for (j = y + 1; j <= y + max; j++)
			{	// pokrywam w prawo
				if (board[x][j] == 0)
					board[x][j] = 1;
			}
			break;
		case 3:
			for (i = x - 1; i >= x - max; i--)
			{	// pokrywam w gore
				if (board[i][y] == 0)
					board[i][y] = 1;
			}
			break;
		case 4:
			for (j = y - 1; j < y - max; j--)
			{	// pokrywam w lewo
				if (board[x][j] == 0)
					board[x][j] = 1;
			}
			break;
		}
	
	x = i;
	y = j; //ostatnie polozenie - po wykonanym ruchu

	// TODO: wyswietl tablice z pokryciem materialem i przejdz do kolejnego ruchu
	 for ()
	cout << "Hello world" << endl;
	cin.get();
	return 0;
}



