%base de conhecimento que depois e substituida por BdD
amizade(marco,joao).
amizade(marco,fabio).
amizade(joao,miguel).
amizade(joao,joel).
amizade(joao,fabio).
amizade(joao,marco).
amizade(miguel,cristiano).
amizade(miguel,maria).
amizade(miguel,marco).

%tamanho da rede de um utilizador
tamanhoRedeUt(Ut,Tam):-amigosUtilizador(Ut,L),length(L,Tam).

%saber a rede de amigos de um utilizador
amigosUtilizador(Ut,Lamif):-amigos1grau(Ut,Lami),amigos2grau(Ut,Lami,Lami,Lamif).

amigos1grau(Ut,Lami):-findall(Ami,amizade(Ut,Ami),Lami).

amigos2grau(Ut,[H|T],Laux,Lamif):-findall(Ami,amizade(H,Ami),Lami),
	append(Lami,Laux,L),
	amigos2grau(Ut,T,L,Lamif).

amigos2grau(Ut,[],Laux,Lamif):-delete(Laux,Ut,Laux2),
	set(Laux2,Lamif).

%para eliminar duplicados
set([],[]).

set([H|T],[H|Out]) :-
    \+(member(H,T)),
    set(T,Out).

set([H|T],Out) :-
    member(H,T),
    set(T,Out).