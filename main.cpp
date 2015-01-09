#include <iostream>
#include "stdafx.h" // tylko dla Visual Studio

int main(void)
{
	board cus(1, 50, 50);
	cus.display();
	VDec wektor(50,50,1);
	/* cus.array[0][0][10].state = '1';
	cus.array[0][30][10].state = '1';
	cus.array[0][30][40].state = '1';
	cus.display();
	cus.moveX(0, 10);
	cus.moveY(0, 40);
	cus.moveX(10, 40);
	cus.display();*/
	
	cus.algoGreedy(0, 0, 0, wektor);
	std::cout << "Sukces" << std::endl;
	cus.display();
	// wektor.Wyswietl();
	std::cin.get();
	return 0;
}
