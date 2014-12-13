#include <iostream>
//#include "stdafx.h" // tylko dla Visual Studio
#include "VDec.cpp"

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
		point ***array; // Tablica numerowana [Z][Y][X]
		board(int,int,int);
		friend class VDec;
		void display();
		void moveX(int, int);
		void moveY(int, int);
		void algoGreedy(int xStart, int yStart, int zStart, VDec &);
		void updateVDec();
		void traceRouteFromVDec(VDec &Dec);
		~board();
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
	array = new point**[Z];
	for(i = 0;i<Z;i++){
		array[i] = new point*[Y]; 
		for(j = 0;j<Y;j++)	array[i][j] = new point[X];
	};
};
	
board::~board(){
          delete []array;
}

void board::algoGreedy(int xStart, int yStart, int zStart, VDec &Dec1) // mozna przyjac xStart = curX
{
	int x, y, z, i, j, max, tmp, ruch;
	int droga_kierunek[4];

	x = xStart; // punkt startowy na warstwie
	y = yStart;
	z = zStart;
	// przy pierwszym wywolaniu i tworzeniu rozw poczatkowego z = 0
	// prawdopodobnie szybciej bedzie wyciac jedna warstwe macierzy i operowac w 2D, a potem wrzucic ja z powrotem niz w 3D

	// --- Znalezienie kierunku ---
	for (i = x + 1; i < X; i++)
	{	// sprawdzenie w dol
		if (array[z][y][i].state == '1')	// jesli 0 to rzeczywiscie nie wypelnione miejsce
			droga_kierunek[0]++;
		else break;
	}

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

	Dec1.updateVDec(*this);	// DONE::bardzo nieeleganckie odwolanie do konkretnego obiektu innej klasy, zamienic na przeslanie przez referencje

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

class tabu {
    int size;
    public:
    int **tabu_array;// Ma trzy wiersze o długości size(parametr optymalizacyjny), 0-X,1-Y,3-Z, przy sprawdzaniu ruchów na liście tabu będziemy brali uwagę co dwie sąsiednie pozycje
    tabu(int);
    ~tabu();
    void display();
    friend class board;
};

void tabu::display(){
    int i,j;
    for(i=0;i<3;i++){
        cout<<endl;
        for(j=0;j<size;j++)
            cout<<tabu_array[i][j];
    }
}

tabu::tabu(int X){
    int i,j;
    size = X;
    tabu_array = new int*[3];
    for(i=0;i<3;i++) tabu_array[i] = new int[X];
    for(i=0;i<3;i++) // początkowo wypełniamy zerami
        for(j=0;j<size;j++)
            tabu_array[i][j]=0;
}

tabu::~tabu(){
    delete[] tabu_array;
}
int main(int argc, char** argv)
{
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
