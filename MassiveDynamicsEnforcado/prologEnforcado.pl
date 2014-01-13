palavra(objecto, cadeira, [c,a,d,e,i,r,a]).
palavra(objecto, mesa, [m,e,s,a]).
palavra(objecto, lapis, [l,a,p,i,s]).
palavra(objecto, livro, [l,i,v,r,o]).
palavra(objecto, telemovel, [t,e,l,e,m,o,v,e,l]).
palavra(pessoa, fernando, [f,e,r,n,a,n,d,o]).
palavra(pessoa, ana, [a,n,a]).
palavra(pessoa, joni, [j,o,n,i]).
palavra(pessoa, fabio, [f,a,b,i,o]).
palavra(pessoa, marco, [m,a,r,c,o]).

caracterEm(Car,Pal,X):-
	palavra(_,Pal,L),
	member(Car,L),
	!,
	X is 1.
caracterEm(Car,Pal,0).

getPalavra(Cat,Num,X):-
	findall(P,
	       palavra(Cat,P,_),
	       L),
	nth1(Num,L,X).
