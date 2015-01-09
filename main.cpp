#include <iostream>
#include "stdafx.h" // tylko dla Visual Studio

int main(void)
{
	board cus(1, 50, 50);
	cus.display();
	VDec wektor(50,50,1);
	// cus.algoGreedy(0, 0, 0, wektor);
	wektor.Wyswietl();
	std::cin.get();
}
