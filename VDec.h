// #pragma once
#ifndef VDEC_H_
#define VDEC_H_

#define H 3

class VDec				// wektor decyzyjny
{
private:
	int*** Dec; 	// 3 na X*Y na Z
	int kierunek; 	// flaga - pion/poziom
	int X, Y, Z, N; 	// N - numer ruchu i kolumny VDec
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
	void simplifyVDec(board &Rozw1);	// zamienia ruchy zlozone na sume ruchow prostych
	void swap(int, int, int); // nasz pierwszy RUCH!
	int FunctionValue(board); // funkcja celu, robie bez referencji �eby dzia�a� na kopii, a nie na oryginale
};

#endif VDEC_H_
