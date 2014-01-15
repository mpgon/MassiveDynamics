user(joao,[lol,lal,lil],20).
user(joel,[lel,lul],30).
user(miguel,[ola, lel, lul],80).
user(cristiano,[ola,lal,lil,lol],35).
user(fabio,[lol,lal,lelelelele],50).
user(marco,[lol,lal,lil],200).
user(gorila,[lol,lal,lil,lelelelelelelellelelele],10).

amigos(joao,joel).
amigos(joao,miguel).
amigos(joao,cristiano).
amigos(joao,fabio).
amigos(miguel,cristiano).
amigos(cristiano, fabio).

amigos(joel,joao).
amigos(miguel,joao).
amigos(cristiano,joao).
amigos(fabio,joao).
amigos(cristiano,miguel).
amigos(fabio,cristiano).

%tamanho da rede de um utilizador
tamanhoRedeUt(Ut,Tam):-amigosUtilizador(Ut,L),length(L,Tam).

%saber a rede de amigos de um utilizador
amigosUtilizador(Ut,Lamif):-amigos1grau(Ut,Lami),amigos2grau(Ut,Lami,Lami,Lamif).

amigos1grau(Ut,Lami):-findall(Ami,amigos(Ut,Ami),Lami).

amigos2grau(Ut,[H|T],Laux,Lamif):-findall(Ami,amigos(H,Ami),Lami),
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

%----------------------------------------------
%Procurar por tags e amigos
%----------------------------------------------
%
inter([], _, []).

inter([H1|T1], L2, [H1|Res]) :-
    member(H1, L2),
    !,
    inter(T1, L2, Res).

inter([_|T1], L2, Res) :-
    inter(T1, L2, Res).


procuraTagsComum(U,N,LR):-
	user(U,LTagU),
	findall(User,(amigos(U,User)),LA),
	procuraAmigos(N,LTagU,LA,[],LR).

procuraAmigos(_,_,[],LR,LR).

procuraAmigos(N,LTagU,[H|T],LR,RF):-
	user(H,LTagH,_),
	inter(LTagU,LTagH,LRT),
	length(LRT,TL),
	TL>=N,
	!,
        procuraAmigos(N,LTagU,T,[H|LR],RF).

procuraAmigos(N,LTagU,[_|T],LR,RF):-
	procuraAmigos(N,LTagU,T,LR,RF).
