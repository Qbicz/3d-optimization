#include <iostream>
using namespace std;

class point {
	float delay;
	int X,Y,Z;
	public:
		char state;
		friend class board;
		point(){
			state = '0';
		}
	protected:

};
class board {

	int X,Y,Z;
	public:
		int curX, curY, curZ;
		point ***array = new point**[Z]; // Tablica numerowana [Z][Y][X]
		void display();
		board(int,int,int);
		void moveX(int, int);
		void moveY(int, int);
		void algoGreedy(int xStart, int yStart, int zStart);
		void updateVDec();
		void traceRouteFromVDec(VDec &Dec);
		friend class VDec;
		//~board();
	protected:

};

void board::display(){
	int sizex, sizey, sizez;
	for(sizez=0;sizez<Z;sizez++){
		cout<<endl;
		for(sizey=0;sizey<Y;sizey++){
			cout<<endl;
			for(sizex=0;sizex<X;sizex++)
				cout<<array[sizez][sizey][sizex].state;
		};
	};
}

void board::moveX(int X0, int X1){
	int x;
	if (X0 < X1)
		for(x = X0; x<=X1; x++){
			curX = x;
			if(array[curZ][curY][curX].state == '1')
				array[curZ][curY][curX].state = 'X';
			else if(array[curZ][curY][curX].state == '0')
				array[curZ][curY][curX].state = ' ';
			curX = X1; // info dla tworzonego wektora decyzyjnego
		}
	else
		for (x = X1; x>=X0; x--){
			curX = x;
			if(array[curZ][curY][curX].state == '1')
				array[curZ][curY][curX].state = 'X';
			else if(array[curZ][curY][curX].state == '0')
				array[curZ][curY][curX].state = ' ';
			curX = X0;
		}
	
}

void board::moveY(int Y0, int Y1){
	int y;
	if (Y0 < Y1)
		for(y = Y0; y<=Y1; y++){
			curY = y;
			if(array[curZ][curY][curX].state == '1')
				array[curZ][curY][curX].state = 'X';
			else if(array[curZ][curY][curX].state == '0')
				array[curZ][curY][curX].state = ' ';
			curY = Y1; // info dla tworzonego wektora decyzyjnego
		}
	else 
		for (y = Y1; y>=Y0; y--){
			curY = y;
			if(array[curZ][curY][curX].state == '1')
				array[curZ][curY][curX].state = 'X';
			else if(array[curZ][curY][curX].state == '0')
				array[curZ][curY][curX].state = ' ';
			curY = Y0;
		};	
}

board::board(int a, int b, int c){
	curX = 0;
	curY = 0;
	curZ = 0;
	X = c;
	Y = b;
	Z = a;
	int i,j;
	for(i = 0;i<Z;i++){
		array[i] = new point*[X]; // tutaj bedzie X czy Y? pisze metode tak jak mowiles, [Z][Y][X]
		for(j = 0;j<X;j++)	array[i][j] = new point[Y];
	};
};
	
/*board::~board(){
	int i,j;
	for (int i=0;i<X;i++)
          {
                  for (int j=0;j<Z;j++)
                  {
                          delete []array[i][j];
                  }
                  delete []array[i];
          }
          delete []array;

}*/

void board::algoGreedy(xStart, yStart, zStart) // mozna przyjac xStart = curX
{
	//bool board[X][Y]; //statycznie, nie bedzie czesto alokowana
	int x, y, z, i, j, max, tmp, ruch;
	int xStart = 0, yStart = 0;
	int droga_kierunek[4];

	x = xStart; // punkt startowy na warstwie
	y = yStart;
	z = zStart;
	// przy pierwszym wywolaniu i tworzeniu rozw poczatkowego z = 0
	// prawdopodobnie szybciej bedzie wyciac jedna warstwe macierzy i operowac w 2D, a potem wrzucic ja z powrotem niz w 3D

	// --- Znalezienie kierunku ---
	for (i = x + 1; i < X; i++)
	{	// sprawdzenie w dol
		if (array[z][y][i] == 0)
			droga_kierunek[0]++;
		else break;
	}

	for (j = y + 1; j < X; j++)
	{	// sprawdzenie w prawo
		if (array[z][j][x] == 0)
			droga_kierunek[1]++;
		else break;
	}

	for (i = x - 1; i >= 0; i--)
	{	// sprawdzenie w gore
		if (array[z][y][i] == 0)
			droga_kierunek[2]++;
		else break;
	}

	for (j = y - 1; j >= 0; j--)
	{	// sprawdzenie w lewo
		if (array[z][j][x] == 0)
			droga_kierunek[3]++;
		else break;
	}
	// Znalezienie najdluzszej drogi z obecnego miejsca - Sortowanie przez wybór
	max = droga_kierunek[0];
	for (i = 1; i < 4; i++)
		if (droga_kierunek[i]>max)
			max = droga_kierunek[i];
	for (i = 0; i < 4; i++)
		if (max == droga_kierunek[i])
		{
			ruch = i;
			break;
		}
	// wykonaj ruch w wybranym kierunku
	switch (ruch)
	{
	case 1:
		moveX(x, x + max);
	case 2:
		moveY(y, y + max);
	case 3:
		moveX(x, x - max);
	case 4:
		moveY(y, y - max);
	}

	Dec1.updateVDec();	// bardzo nieeleganckie odwolanie do konkretnego obiektu innej klasy, zamienic na przeslanie przez referencje

	//switch (ruch)
	//{
	//case 1:
	//	for (i = x + 1; i < x + max; i++)
	//	{	// pokrywam w dol
	//		if (array[z][i][y] == 0)
	//			array[z][i][y] = 1;
	//	}
	//	break;
	//case 2:
	//	for (j = y + 1; j <= y + max; j++)
	//	{	// pokrywam w prawo
	//		if (array[z][x][j] == 0)
	//			array[z][x][j] = 1;
	//	}
	//	break;
	//case 3:
	//	for (i = x - 1; i >= x - max; i--)
	//	{	// pokrywam w gore
	//		if (array[z][i][y] == 0)
	//			array[z][i][y] = 1;
	//	}
	//	break;
	//case 4:
	//	for (j = y - 1; j < y - max; j--)
	//	{	// pokrywam w lewo
	//		if (array[z][x][j] == 0)
	//			array[z][x][j] = 1;
	//	}
	//	break;
	//}

	curX = i;
	curY = j; //ostatnie polozenie - po wykonanym ruchu

	// TODO: wyswietl tablice z pokryciem materialem i przejdz do kolejnego ruchu

	// Przy slepej uliczce (while)
	// -> sprawdz cala tablice w poszukiwaniu luk
	// -> przeskocz do punktu (najblizszego/pierwszego)
	// -> rozpocznij algorytm zachlanny od nowego xStart,yStart

} // koniec algoGreedy

void traceRouteFromVDec(VDec &Dec)
{
	for (int i = 1; i < Dec.N; i++)
	{
		if (Dec[curZ][0][i] != Dec[curZ][0][i - 1]
			&& Dec[curZ][1][i] != Dec[curZ][1][i - 1])	// curZ czyli this.curZ (board.curZ)
		{	// wykryto ruch ukosny (zlozony)

		}
	Dec.curZ
}

int main(int argc, char** argv) {
	// trzeba zainicjowac VDec
	board cos(1,50,50);
	cos.array[0][0][10].state = '1';
	cos.array[0][30][10].state = '1';
	cos.display();
	cos.moveX(0, 10);
	cos.moveY(0,40);
	cos.display();
	return 0;
}
