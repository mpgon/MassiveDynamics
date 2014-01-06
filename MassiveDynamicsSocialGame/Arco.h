#ifndef ARCO_
#define ARCO_
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Arco{
public:
	int noi, nof;
	float peso, largura;

public:
	Arco();
	Arco(const int& noiP, const int& nofP, const float& pesoP, const float& larguraP);
	
	int getNOI()const{ return noi; }
	int getNOF()const{ return nof; }
	float getPeso()const{ return peso; }
	float getLargura()const{ return largura; }
};

#endif