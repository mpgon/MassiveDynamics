#include "Arco.h"
Arco::Arco(){

}
Arco::Arco(const int& noiP, const int& nofP, const  float& pesoP, const float& larguraP){

	noi = noiP;
	nof = nofP;
	peso = pesoP;
	largura = larguraP;

}
/*
istream& operator>>(std::istream& is, Arco& obj)
{
// read obj from stream
/*if ( /* no valid object of T found in stream ){
is.setstate(std::ios::failbit);
}
return is;
}*/