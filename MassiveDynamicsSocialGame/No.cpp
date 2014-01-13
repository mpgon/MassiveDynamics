#include "No.h"
No::No(){

}
No::No(const float& x1, const float& y1, const float& z1){

	x = x1;
	y = y1;
	z = z1;

}
void No::setX(const float& xP){
	x = xP;
}
void No::setY(const float& yP){
	y = yP;
}
void No::setZ(const float& zP){
	z = zP;
}

void No::setTipo(const char t){
	tipo = t;
}

/*
istream& operator>>(std::istream& is, No& obj)
{
// read obj from stream
/*if ( /* no valid object of T found in stream ){
is.setstate(std::ios::failbit);
}
return is;
}*/