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
		int curr_X, curr_Y, curr_Z;
		point ***array = new point**[Z]; // Tablica numerowana [Z][Y][X]
		void display();
		board(int,int,int);
		void moveX(int, int);
		void moveY(int, int);
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
			curr_X = x;
			if(array[curr_Z][curr_Y][curr_X].state == '1')
				array[curr_Z][curr_Y][curr_X].state = 'X';
			else if(array[curr_Z][curr_Y][curr_X].state == '0')
				array[curr_Z][curr_Y][curr_X].state = ' ';
		}
	else
		for (x = X1; x>=X0; x--){
			curr_X = x;
			if(array[curr_Z][curr_Y][curr_X].state == '1')
				array[curr_Z][curr_Y][curr_X].state = 'X';
			else if(array[curr_Z][curr_Y][curr_X].state == '0')
				array[curr_Z][curr_Y][curr_X].state = ' ';
		};	
}

void board::moveY(int Y0, int Y1){
	int y;
	if (Y0 < Y1)
		for(y = Y0; y<=Y1; y++){
			curr_Y = y;
			if(array[curr_Z][curr_Y][curr_X].state == '1')
				array[curr_Z][curr_Y][curr_X].state = 'X';
			else if(array[curr_Z][curr_Y][curr_X].state == '0')
				array[curr_Z][curr_Y][curr_X].state = ' ';
		}
	else 
		for (y = Y1; y>=Y0; y--){
			curr_Y = y;
			if(array[curr_Z][curr_Y][curr_X].state == '1')
				array[curr_Z][curr_Y][curr_X].state = 'X';
			else if(array[curr_Z][curr_Y][curr_X].state == '0')
				array[curr_Z][curr_Y][curr_X].state = ' ';
		};	
}

board::board(int a, int b, int c){
	curr_X = 0;
	curr_Y = 0;
	curr_Z = 0;
	X = c;
	Y = b;
	Z = a;
	int i,j;
	for(i = 0;i<Z;i++){
		array[i] = new point*[X];
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

int main(int argc, char** argv) {
	board cos(1,50,50);
	cos.array[0][0][10].state = '1';
	cos.array[0][30][10].state = '1';
	cos.display();
	cos.moveX(0, 10);
	cos.moveY(0,40);
	cos.display();
	return 0;
}
