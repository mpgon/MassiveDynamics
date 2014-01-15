:-dynamic caminho/2.

criarBaseConhecimento((Xi,Zi),(Xf,Zf)):-
	assertz(caminho((Xi,Zi),(Xf,Zf))).

listarValores:-
	listing(caminho/2).


procuraCaminho((Xf,Zf),(Xi,Zi),C):-
	procuraCaminhos((Xf,Zf),[[(Xi,Zi)]],C).

procuraCaminhos((Xf,Zf),[[(Xf,Zf)|T]|_],C):-
	reverse([(Xf,Zf)|T],C).

procuraCaminhos((Xf,Zf),[[(Xh,Zh)|T]|Out],C):-
	findall([(Xa,Za),(Xh,Zh)|T],((Xf,Zf)\==(Xh,Zf),caminho((Xh,Zf),(Xa,Za)),\+member((Xa,Za),[(Xh,Zh)|T])),Novos),
	append(Out,Novos,Todos),
	procuraCaminhos((Xf,Zf),Todos,C).
