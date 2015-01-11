#include "stdafx.h"
#include "board.h"
#include <iostream>
#include <cstdlib>	// dla funkcji int abs(int n)
using namespace std;

bool board::stop(){
	int sizex, sizey, sizez;
	int counterek = 0;
	for (sizez = 0; sizez<Z; sizez++)
		for (sizey = 0; sizey<Y; sizey++)
			for (sizex = 0; sizex<X; sizex++)
				if (array[sizez][sizey][sizex].state == '1')
					counterek++;
	if (counterek == 0) return true;
	else return false;
}

void board::display(){
	int sizex, sizey, sizez;
	for (sizez = 0; sizez<Z; sizez++){
		cout << endl;
		for (sizey = 0; sizey<Y; sizey++){
			cout << endl;
			for (sizex = 0; sizex<X; sizex++)
				cout << array[sizez][sizey][sizex].state;
		}
	}
}

void board::moveX(int X0, int X1){
	std::cout << "moveX " << std::endl; // -------------- TUUUUUUUUUU ----------
	int x;
	if (X0 < X1)
		for (x = X0; x <= X1; x++)
		{
			curX = x;
			//std::cout << X0 << ' ' << X1;
			if (array[curZ][curY][curX].state == '1')
			{
				array[curZ][curY][curX].state = 'X';
				// std::cout << "x = " << x << std::endl; // -------------- TUUUUUUUUUU ----------
				counter += 2;
			}
			else if (array[curZ][curY][curX].state == '0')
			{
				array[curZ][curY][curX].state = ' ';
				counter += 1;
			}
			curX = X1; // info dla tworzonego wektora decyzyjnego
			std::cout << "curX = " << curX << std::endl; // -------------- TUUUUUUUUUU ----------
			std::cout << "curY = " << curY << std::endl; // -------------- TUUUUUUUUUU ----------
			 this->display(); // --------------------------------------------------------------
		}
	else
		for (x = X1; x >= X0; x--)
		{
			curX = x;
			if (array[curZ][curY][curX].state == '1')
			{
				array[curZ][curY][curX].state = 'X';
				
				counter += 2;
			}
			else if (array[curZ][curY][curX].state == '0')
			{
				array[curZ][curY][curX].state = ' ';
				counter += 1;
			}
			curX = X0;
			std::cout << "curX = " << curX << std::endl; // -------------- TUUUUUUUUUU ----------
			std::cout << "curY = " << curY << std::endl; // -------------- TUUUUUUUUUU ----------
			 this->display(); // --------------------------------------------------------------
		}

}

void board::moveY(int Y0, int Y1){
	std::cout << "moveY " << std::endl; // -------------- TUUUUUUUUUU ----------
	int y;
	if (Y0 < Y1)
		for (y = Y0; y <= Y1; y++){
			curY = y;
			if (array[curZ][curY][curX].state == '1'){
				array[curZ][curY][curX].state = 'X';
				
				counter += 2;
			}
			else if (array[curZ][curY][curX].state == '0'){
				array[curZ][curY][curX].state = ' ';
				counter += 1;
			}
			curY = Y1;	// info dla tworzonego wektora decyzyjnego
						// i info dla kolejnego ruchu AlgoGreedy
			std::cout << "curX = " << curX << std::endl; // -------------- TUUUUUUUUUU ----------
			std::cout << "curY = " << curY << std::endl; // -------------- TUUUUUUUUUU ----------
			 this->display(); // --------------------------------------------------------------
		}
	else
		for (y = Y1; y >= Y0; y--)
		{
			curY = y;
			if (array[curZ][curY][curX].state == '1'){
				array[curZ][curY][curX].state = 'X';
				// std::cout << "y = " << y << std::endl; // -------------- TUUUUUUUUUU ----------
				counter += 2;
			}
			else if (array[curZ][curY][curX].state == '0'){
				array[curZ][curY][curX].state = ' ';
				counter += 1;
			}
			curY = Y0;
			std::cout << "curX = " << curX << std::endl; // -------------- TUUUUUUUUUU ----------
			std::cout << "curY = " << curY << std::endl; // -------------- TUUUUUUUUUU ----------
			 this->display(); // --------------------------------------------------------------
		}
}

board::board(int a, int b, int c){
	curX = 0;
	curY = 0;
	curZ = 0;
	X = c;
	Y = b;
	Z = a;
	int i, j;
	array = new point**[Z];
	for (i = 0; i<Z; i++)
	{
		array[i] = new point*[Y];
		for (j = 0; j < Y; j++)
			array[i][j] = new point[X];
	}
}

board::~board(){
	delete[]array;
}

void board::algoGreedy(int xStart, int yStart, int zStart, VDec &Dec1) // mozna przyjac xStart = curX
{
	int x, y, z;

	x = xStart; // punkt startowy na warstwie
	y = yStart;
	z = zStart;
	std::cout.width(3);
	std::cout << "algoGreedy(" << x << y << z << ")" << std::endl; // -------------- TUUUUUUUUUU ----------
	// przy pierwszym wywolaniu i tworzeniu rozw poczatkowego z = 0
	// prawdopodobnie szybciej bedzie wyciac jedna warstwe macierzy i operowac w 2D, a potem wrzucic ja z powrotem niz w 3D

	while (!slepa_uliczka)
		{
			x = curX;
			y = curY;
			z = curZ;
			for (int f = 0; f < 4; f++) flag[f] = false; // czyszczenie flag
			std::cout << "AlgoGreedy: x = " << x  << " " << "y = " << y << "Dziekuje." << std::endl;
			if (x == X-1 && y != 0 && y != Y-1)      // dol (nowe prawo - flaga prawo)
				if (// array[curZ][y][x + 1].state == '1' ||
					array[curZ][y][x - 1].state == '1' ||
					array[curZ][y + 1][x].state == '1' ||
					array[curZ][y - 1][x].state == '1')
				{
					flag[1] = true;
					ZnajdzKierunek(x, y, z, Dec1);
				}
			if (y == Y - 1 && x != 0 && x != X - 1)     // prawo (nowy dol - flaga dol)
				if (array[curZ][y][x + 1].state == '1' ||
					array[curZ][y][x - 1].state == '1' ||
					// array[curZ][y + 1][x].state == '1' ||
					array[curZ][y - 1][x].state == '1')
				{
					flag[0] = true;
					ZnajdzKierunek(x, y, z, Dec1);
				}
			if (x == 0 && y != 0 && y != Y - 1)     // gora (nowe lewo - flag lewo)
				if (array[curZ][y][x + 1].state == '1' ||
					// array[curZ][y][x - 1].state == '1' ||
					array[curZ][y + 1][x].state == '1' ||
					array[curZ][y - 1][x].state == '1')
				{
					flag[3] = true;
					ZnajdzKierunek(x, y, z, Dec1);
				}
			if (y == 0 && x != 0 && x != X - 1)     // lewo
				if (array[curZ][y][x + 1].state == '1' ||
					array[curZ][y][x - 1].state == '1' ||
					array[curZ][y + 1][x].state == '1' )
					// array[curZ][y - 1][x].state == '1')
				{
					flag[2] = true;
					ZnajdzKierunek(x, y, z, Dec1);
				}
			// KOMBINACJE WARUNKOW
			if (x == X-1 && y == Y-1)      // dol prawo
				if (// array[curZ][y][x + 1].state == '1' ||
					array[curZ][y][x - 1].state == '1' ||
					// array[curZ][y + 1][x].state == '1' ||
					array[curZ][y - 1][x].state == '1')
				{
					flag[0] = true;
					flag[1] = true;
					ZnajdzKierunek(x, y, z, Dec1);
				}
			if (x == X-1 && y == 0)      // dol lewo
				if (// array[curZ][y][x + 1].state == '1' ||
					array[curZ][y][x - 1].state == '1' ||
					array[curZ][y + 1][x].state == '1' )
					// array[curZ][y - 1][x].state == '1')
				{
					flag[1] = true;
					flag[2] = true;
					ZnajdzKierunek(x, y, z, Dec1);
				}
			if (x == 0 && y == Y-1)     // gora prawo
				if (array[curZ][y][x + 1].state == '1' ||
					// array[curZ][y][x - 1].state == '1' ||
					// array[curZ][y + 1][x].state == '1' ||
					array[curZ][y - 1][x].state == '1')
				{
					flag[3] = true;
					flag[0] = true;
					ZnajdzKierunek(x, y, z, Dec1);
				}
			if (x == 0 && y == 0)     // gora lewo
				if (array[curZ][y][x + 1].state == '1' ||
					// array[curZ][y][x - 1].state == '1' ||
					array[curZ][y + 1][x].state == '1' )
					// array[curZ][y - 1][x].state == '1')
				{
					flag[2] = true;
					flag[3] = true;
					ZnajdzKierunek(x, y, z, Dec1);
				}

			// flagi zabraniaja ruchow w odpowiednia strone (i bezsensownych sprawdzen!)

			/*if (array[curZ][y][x + 1].state == '1' || array[curZ][y][x - 1].state == '1' ||
				array[curZ][y + 1][x].state == '1' || array[curZ][y - 1][x].state == '1')
				{	// dopoki nie jestes w slepej uliczce

				ZnajdzKierunek();

				// TODO: wyswietl tablice z pokryciem materialem i przejdz do kolejnego ruchu
				}*/
		}
	// Przy slepej uliczce (koniec while)
	// -> sprawdz cala tablice w poszukiwaniu luk
	// -> przeskocz do punktu (najblizszego/pierwszego)
	/* -> rozpocznij algorytm zachlanny od nowego xStart,yStart
	for (i = 0; i < X; i++)
	for (j = 0; j < Y; j++)
	if (array[curZ][j][i].state == '1')
	jump(i, j, Dec1); // !!! po przeskoku zacznij od nowa algoGreedy, trzeba umiescic calosc w jeszcze jednej petli
	*/
} // koniec algoGreedy

void board::traceRouteFromVDec(VDec &Dec1)
{
	for (int i = 1; i < Dec1.N; i++)
	{
		int startX = Dec1.Dec[curZ][0][i - 1];
		int stopX = Dec1.Dec[curZ][0][i];
		int startY = Dec1.Dec[curZ][1][i - 1];
		int stopY = Dec1.Dec[curZ][1][i];

		if (startX != stopX)	// curZ czyli this.curZ (board.curZ)
		{
			if (startY != stopY)
			{	// wykryto ruch ukosny (zlozony) -> powinno to zostac rozwiazane przez VDec::simplifyVDec()
				// kod ostrzegajacy o bledzie
			}
			else
			{	// ruch po X
				moveX(startX, stopX);
			}
		}
		else // (startX == stopX)
		{
			if (startY != stopY)
			{	// ruch po Y
				moveY(startY, stopY);
			}
		}

		//Dec.curZ
	}
}

void board::jump(int x, int y, VDec &Dec1)
{	
	int koszt = abs(x - curX) + abs(y - curY);
	Dec1.T += koszt; // zwiekszenie funkcji celu
	// jesli wolisz liczyc inaczej to po prostu suma przeskokow board::int jumps+= koszt; i bedzie sie to dodawac w VDec::FunctionValue
	curX = x;
	curY = y;
}

void board::ZnajdzKierunek(int x, int y, int z, VDec &Dec1)
{
	int i, j, max=0, ruch=0;
	int droga_kierunek[4] = {0,0,0,0};
	slepa_uliczka = false;
	std::cout.width(3);
	std::cout << "ZnajdzKierunek(" << x << y << z << ")" << std::endl; // -------------- TUUUUUUUUUU ----------

	std::cout << "[ ";
	for (int t = 0; t < 4;t++)
		std::cout << flag[t] << ' ';
	std::cout << "]\n";
	// --- Znalezienie kierunku ---
	if (flag[0]) // czyli y == max
	{
		if (flag[1])
		{ // prawy dolny rog
			for (i = x - 1; i >= 0; i--)
			{	// sprawdzenie w gore
				if (array[z][y][i].state == '1')
					droga_kierunek[2]++;
				else break;
			}
			for (j = y - 1; j >= 0; j--)
			{	// sprawdzenie w lewo
				if (array[z][j][x].state == '1')
					droga_kierunek[3]++;
				else break;
			}	
		}
		if (flag[3])
		{ // lewy dolny rog
			for (i = x - 1; i >= 0; i--)
			{	// sprawdzenie w gore
				if (array[z][y][i].state == '1')
					droga_kierunek[2]++;
				else break;
			}
			for (j = y + 1; j < X; j++)
			{	// sprawdzenie w prawo
				if (array[z][j][x].state == '1')
					droga_kierunek[1]++;
				else break;
			}
		}
		else
		{
			// dolna krawedz
			for (j = y + 1; j < X; j++)
			{	// sprawdzenie w prawo
				if (array[z][j][x].state == '1')
					droga_kierunek[1]++;
				else break;
			}

			for (i = x - 1; i >= 0; i--)
			{	// sprawdzenie w gore
				if (array[z][y][i].state == '1')
					droga_kierunek[2]++;
				else break;
			}

			for (j = y - 1; j >= 0; j--)
			{	// sprawdzenie w lewo
				if (array[z][j][x].state == '1')
					droga_kierunek[3]++;
				else break;
			}
		}
	}
	else if (flag[2]) // y == 0
	{
		if (flag[1])
		{ // prawy gorny rog

			for (i = x + 1; i < X; i++)
			{	// sprawdzenie w dol
				if (array[z][y][i].state == '1')	// jesli 1 to rzeczywiscie nie wypelnione miejsce
					droga_kierunek[0]++;
				else break;
			}

			for (j = y - 1; j >= 0; j--)
			{	// sprawdzenie w lewo
				if (array[z][j][x].state == '1')
					droga_kierunek[3]++;
				else break;
			}
		}
		if (flag[3])
		{ //lewy gorny rog
			for (j = y + 1; j < X; j++)
			{	// sprawdzenie w prawo
				if (array[z][j][x].state == '1')
					droga_kierunek[1]++;
				else break;
			}
			for (i = x + 1; i < X; i++)
			{	// sprawdzenie w dol
				if (array[z][y][i].state == '1')	// jesli 1 to rzeczywiscie nie wypelnione miejsce
					droga_kierunek[0]++;
				else break;
			}
		}
		else
		{
			// gorna krawedz
			for (i = x + 1; i < X; i++)
			{	// sprawdzenie w dol
				if (array[z][y][i].state == '1')	// jesli 1 to rzeczywiscie nie wypelnione miejsce
					droga_kierunek[0]++;
				else break;
			}
			for (j = y + 1; j < X; j++)
			{	// sprawdzenie w prawo
				if (array[z][j][x].state == '1')
					droga_kierunek[1]++;
				else break;
			}
			for (j = y - 1; j >= 0; j--)
			{	// sprawdzenie w lewo
				if (array[z][j][x].state == '1')
					droga_kierunek[3]++;
				else break;
			}
		}
	}
	else if (flag[1]) // x == max
	{
		for (j = y - 1; j >= 0; j--)
		{	// sprawdzenie w lewo
			if (array[z][j][x].state == '1')
				droga_kierunek[3]++;
			else break;
		}
	}
	else if (flag[3]) // x == 0
	{
		for (j = y + 1; j < X; j++)
		{	// sprawdzenie w prawo
			if (array[z][j][x].state == '1')
				droga_kierunek[1]++;
			else break;
		}
	}
	
	// Znalezienie najdluzszej drogi z obecnego miejsca - Sortowanie przez wybór
	max = droga_kierunek[0];
	for (i = 1; i < 4; i++)
		if (droga_kierunek[i]>max)
			max = droga_kierunek[i];
	for (i = 0; i < 4; i++) // znajdz to maksimum
	{
		if (max == droga_kierunek[i])
		{
			ruch = i;
		}
	}
	std::cout << "ruch = " << ruch << " max = " << max << std::endl; // -------------------------------------
	// wykonaj ruch w wybranym kierunku
	if (max)
	{
		switch (ruch)
		{
		case 0:
			//std::cout << "x="<< x << ' ' << max;
			moveY(y, y + max);
			break;
		case 1:
			//std::cout << "x=" << x << ' ' << max;
			moveX(x, x + max);
			break;
		case 2:
			//std::cout << "x=" << x << ' ' << max;
			moveY(y, y - max);
			break;
		case 3:
			//std::cout << "x=" << x << ' ' << max;
			moveX(x, x - max);
			break;
		default:
			break;
		}
	}
	else
		slepa_uliczka = true;

	// Dec1.updateVDec(*this);	// DONE::zamienic na przeslanie przez referencje

	// curX = i;
	// curY = j; //ostatnie polozenie - po wykonanym ruchu
	std::cout << "Po wykonanym ruchu: curX = " << curX << " curY = " << curY << std::endl; // -------------------------------------
	for (i = 0; i < 4; i++)
		droga_kierunek[i] = 0;
}

