:-dynamic caminho/2.

criarBaseConhecimento((Xi,Zi),(Xf,Zf)):-
	assertz(caminho((Xi,Zi),(Xf,Zf))).

listarValores(D):-
	listing(caminho/2).


procuraCaminho((Xf,Yf),(Xi,Yi),C):-
	procuraCaminhos((Xf,Yf),[[(Xi,Yi)]],C).

procuraCaminhos((Xf,Yf),[[(Xf,Yf)|T]|_],C):-
	reverse([(Xf,Yf)|T],C).

procuraCaminhos((Xf,Yf),[[(Xh,Yh)|T]|Out],C):-
	findall([(Xa,Ya),(Xh,Yh)|T],((Xf,Yf)\==(Xh,Yf),caminho((Xh,Yf),(Xa,Ya)),\+member((Xa,Ya),[(Xh,Yh)|T])),Novos),
	append(Out,Novos,Todos),
	procuraCaminhos((Xf,Yf),Todos,C).
