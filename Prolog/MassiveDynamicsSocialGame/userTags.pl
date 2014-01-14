user(joao,[lol,lal,lil]).
user(joel,[lel,lul]).
user(miguel,[ola, lel, lul]).
user(cristiano,[ola,lal,lil,lol]).
user(fabio,[lol,lal,lelelelele]).

amigos(joao,joel).
amigos(joao,miguel).
amigos(joao,cristiano).
amigos(joao,fabio).
amigos(miguel,cristiano).
amigos(cristiano, fabio).


procuraTagsComum(U,N,LR):-
	user(U,LTagU),
	findall(User,(amigos(U,User)),LA),
	procuraAmigos(N,LTagU,LA,LR,LR).

procuraAmigos(_,_,[],LR,LR).

procuraAmigos(N,LTagU,[H|T],LR,RF):-
	user(H,LTagH),
	inter(LTagU,LTagH,LRT),
	length(LRT,TL),
	TL>=N,
	!,
        procuraAmigos(N,LTagU,T,[H|LR],RF).

procuraAmigos(N,LTagU,[_|T],LR,RF):-
	procuraAmigos(N,LTagU,T,LR,RF).

inter([], _, []).

inter([H1|T1], L2, [H1|Res]) :-
    member(H1, L2),
    !,
    inter(T1, L2, Res).

inter([_|T1], L2, Res) :-
    inter(T1, L2, Res).
