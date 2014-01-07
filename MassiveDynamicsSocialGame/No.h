#ifndef NO_
#define NO_
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class No {

public:
	float x;
	float y; 
	float z;
	float largura;

public:
	No();
	No(const float& x1, const float& y1,const float& z1);
	
	float getX()const{ return x; }
	float getY()const{ return y; }
	float getZ()const{ return z; }
	float getLargura()const{ return largura; }
	void setX(const float& xP);
	void setY(const float& yP);
	void setZ(const float& zP);
};

#endif