typedef struct
{
	float xt, yt, zt;  //coordenadas extremo superior
	float xd, yd, zd;  //coordenadas extremo inferior
	float xv, yv, zv;  //velocidade em cada eixo
	float visib;       //visibilidade para o canal alpha
}GOTA;

typedef struct
{
	float fade; 
	int   x, y, z;     //coordenadas do cubo que vai conter a chuva
	float grosor;      //espessura da chuva
	float longitud;    //longitude das gotas
	float xg, yg, zg;  //gravidade em cada eixo
	GOTA *gotas;
}CHUVA;

void InicializarChuva(CHUVA &rain, int numgotas);

void DesenharChuva(CHUVA &rain, int numgotas);