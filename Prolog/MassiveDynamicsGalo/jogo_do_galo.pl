%base de conhecimento
vitoriax([0,1,2]).
vitoriax([0,4,8]).
vitoriax([0,3,6]).
vitoriax([1,4,7]).
vitoriax([2,5,8]).
vitoriax([2,4,6]).
vitoriax([3,4,5]).
vitoriax([6,7,8]).

vitoriax([2,1,0]).
vitoriax([8,4,0]).
vitoriax([6,3,0]).
vitoriax([7,4,1]).
vitoriax([8,5,2]).
vitoriax([6,4,2]).
vitoriax([5,4,3]).
vitoriax([8,7,6]).

vitoriao([0,1,2]).
vitoriao([0,4,8]).
vitoriao([0,3,6]).
vitoriao([1,4,7]).
vitoriao([2,5,8]).
vitoriao([2,4,6]).
vitoriao([3,4,5]).
vitoriao([6,7,8]).

vitoriao([2,1,0]).
vitoriao([8,4,0]).
vitoriao([6,3,0]).
vitoriao([7,4,1]).
vitoriao([8,5,2]).
vitoriao([6,4,2]).
vitoriao([5,4,3]).
vitoriao([8,7,6]).

%inicio
inicio(P,J):-verPcWin(P);counter(J);melhorjogada(P,J).

subset([],_,N,N).
subset([H|T],List,N,Listax):-member(H,List),N1 is N + 1,subset(T,List, N1,Listax).
subset([H|T],List,N,Listax):- \+member(H,List),!,subset(T,List,N,Listax).

pesquisa(L1,[],Listax):-
	reverse(Listax, Lx),
	%print(Lx),
	nl,
	%print(L1),
	!,
	testarvitoria(L1,Lx).

pesquisa(L1,[H|T],Listax):-subset(L1,H,0,HListax),
	%print(Listax),nl,
	%pcWin(L1,Listax,0),
	(pesquisa(L1,T,[HListax|Listax])).

testarvitoria(L1,Lx):-member(2,Lx),
	pcWin(L1,Lx,0).

testarvitoria(_,_):-!,fail.

%pesquisa(L1,[H|T],[]):-subset(L1,H,0,HListax),
%	print(Listax),nl,
%	pcWin(L1,Listax,0),
%	(pesquisa(L1,T,[HListax])).

verPcWin(L):-sort(L, L1),
	findall(A,(vitoriax(A)),Lv),
	pesquisa(L1,Lv,_).

pcWin(_,[],_).

pcWin(L1,[H|T],N):-H \== 2,
	N1 is N + 1,
	pcWin(L1,T,N1).

pcWin(L1,[2|_],N):-N1 is N + 1,
	findall(A,(vitoriax(A)),Lv),
	pcWin2(L1,Lv,N1).

pcWin2(L1,[H|_],1):-pcWin3(L1,H).

pcWin2(L1,[_|T],N):-N \== 1,
	N1 is N - 1,
	pcWin2(L1,T,N1).

pcWin3([],[H|_]):-tell('pcWin.txt'),
	write('PcWin#'),
	write(H),
	nl,
	told.

pcWin3([H|T],[H2|T2]):-H \== H2,
	pcWin3(T,[H2|T2]).

pcWin3([H|T],[H|B]):-pcWin3(T,B).


% vai dar counter!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
counter(J):-sort(J, L1),
	findall(A,(vitoriax(A)),Lv),
	pesquisa2(L1,Lv,_).

subsetCounter([],_,N,N).

subsetCounter([H|T],List,N,Listax):-member(H,List),N1 is N + 1,subsetCounter(T,List, N1,Listax).

subsetCounter([H|T],List,N,Listax):- \+member(H,List),!,subsetCounter(T,List,N,Listax).

pesquisa2(L1,[],Listax):-
	reverse(Listax, Lx),
	%print(Lx),
	nl,
	%print(L1),
	!,
	testarcounter(L1,Lx).

pesquisa2(L1,[H|T],Listax):-subsetCounter(L1,H,0,HListax),
	%print(Listax),nl,
	%pcWin(L1,Listax,0),
	(pesquisa2(L1,T,[HListax|Listax])).

testarcounter(L1,Lx):-member(2,Lx),
	pcCounter(L1,Lx,0).

testarcounter(_,_):-!,fail.

%pesquisa2(L1,[H|T],[]):-subsetCounter(L1,H,0,HListax),
	%print(Listax),nl,
	%pcWin(L1,Listax,0),
%	(pesquisa2(L1,T,[HListax])).

pcCounter(_,[],_).

pcCounter(L1,[H|T],N):-H \== 2,
	N1 is N + 1,
	pcCounter(L1,T,N1).

pcCounter(L1,[2|_],N):-N1 is N + 1,
	findall(A,(vitoriax(A)),Lv),
	pcCounter2(L1,Lv,N1).

pcCounter2(L1,[H|_],1):-pcCounter3(L1,H).

pcCounter2(L1,[_|T],N):-N \== 1,
	N1 is N - 1,
	pcCounter2(L1,T,N1).

pcCounter3([],[H|_]):-tell('Counter.txt'),
	write('PcCounter#'),
	write(H),
	nl,
	told.

pcCounter3([H|T],[H2|T2]):-H \== H2,
	pcCounter3(T,[H2|T2]).

pcCounter3([H|T],[H|B]):-pcCounter3(T,B).


%vai jogar na melhor prob!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
melhorjogada(P,J):-sort(P, L1),
	sort(J,L2),
	findall(A,(vitoriax(A)),Lv),
	pesquisa3(L1,L2,Lv,_,_).

subsetmj([],_,N,N).

subsetmj([H|T],List,N,Listax):-member(H,List),N1 is N + 1,subsetmj(T,List, N1,Listax).

subsetmj([H|T],List,N,Listax):- \+member(H,List),!,subsetmj(T,List,N,Listax).

pesquisa3(L1,L2,[],Listax,Listax2):-
	reverse(Listax, Lx),
	reverse(Listax2,Lx2),
	%print(Lx),
	nl,
	%print(L1),
	!,
	testarmj(L1,L2,Lx,Lx2,1).

pesquisa3(L1,L2,[H|T],Listax,Listax2):-subsetmj(L1,H,0,HListax),
	subsetmj(L2,H,0,HListax2),
	%print(Listax),nl,
	%pcWin(L1,Listax,0),
	(pesquisa3(L1,L2,T,[HListax|Listax],[HListax2|Listax2])).

testarmj(L1,L2,Lx,[1|T2],N):-subs(N,Lx,Rlx),
	N1 is N + 1,
	testarmj(L1,L2,Rlx,[T2],N1).
	%pcmj(L1,Lx,0).

testarmj(L1,L2,Lx,[2|T2],N):-subs(N,Lx,Rlx),
	N1 is N + 1,
	testarmj(L1,L2,Rlx,[T2],N1).
	%pcmj(L1,Lx,0).

testarmj(L1,L2,Lx,[H|T2],N):-H \== 1,
	H \== 2,
	N1 is N + 1,
	testarmj(L1,L2,Lx,T2,N1).

testarmj(L1,_,Lx,[],_):-!,
	pcmj(L1,Lx).

subs(1,[_|T],[0|T]).

subs(N,[H|T],[H|Lx]):-N > 1,
	N1 is N - 1,
	subs(N1,T,Lx).

%pesquisa2(L1,[H|T],[]):-subsetCounter(L1,H,0,HListax),
	%print(Listax),nl,
	%pcWin(L1,Listax,0),
%	(pesquisa2(L1,T,[HListax])).

%pcmj(_,[],_).

pcmj(L1,Lx):-max(Lx,Max),
	pcmj1(L1,Lx,Max,0).

pcmj1(L1,[H|T],Max,N):-H \== Max,
	N1 is N + 1,
	pcmj1(L1,T,Max,N1).

pcmj1(L1,[Max|_],Max,N):-N1 is N + 1,
	findall(A,(vitoriax(A)),Lv),
	pcmj2(L1,Lv,N1).

pcmj2(L1,[H|_],1):-pcmj3(L1,H).

pcmj2(L1,[_|T],N):-N \== 1,
	N1 is N - 1,
	pcmj2(L1,T,N1).

pcmj3([],[H|_]):-tell('MelhorJogada.txt'),
	write('PcProb#'),
	write(H),
	nl,
	told.

pcmj3([H|T],[H2|T2]):-H \== H2,
	pcmj3(T,[H2|T2]).

pcmj3([H|T],[H|B]):-pcmj3(T,B).

max([X],X).

max([X|Xs],X):- max(Xs,Y), X >=Y.

max([X|Xs],N):- max(Xs,N), N > X.


%testes!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
%
%pesqui([],[],N,N).
%pesqui([Q|W], [H|T],N,_):-member(Q,H),
%	N1 is N + 1,
%	pesquisa2(W,T, N1).

print([]) :- !.
print([H|T]) :- write(H), nl, print(T).

ficheiro:-tell('teste.txt'),
	write('GrizATE'),
	nl,
	told.

verfindall:-findall(A, (vitoriax(A)),Lv),
	print(Lv).

verlista([[H|_]|_]):-H \== 2,
	write('difetente de e').
