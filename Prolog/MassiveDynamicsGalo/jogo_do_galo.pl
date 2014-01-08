%base de conhecimento
vitoria([0,1,2]).
vitoria([0,4,8]).
vitoria([0,3,6]).
vitoria([1,4,7]).
vitoria([2,5,8]).
vitoria([2,4,6]).
vitoria([3,4,5]).
vitoria([6,7,8]).

%inicio
inicio(P,J,Rf):-!,(verPcWin(P,J,Rf);counter(P,J,Rf);melhorjogada(P,J,Rf)).

verPcWin(L,J,Rf):-sort(L, L1),
	findall(A,(vitoria(A)),Lv),
	pesquisa(L1,J,Lv,_,Rf).

subset([],_,N,N).

subset([H|T],List,N,Listax):-member(H,List),N1 is N + 1,
	subset(T,List, N1,Listax).

subset([H|T],List,N,Listax):- \+member(H,List),
	!,
	subset(T,List,N,Listax).

pesquisa(L1,L2,[],Listax,Rf):-
	reverse(Listax, Lx),
	nl,
	!,
	testarvitoria(L1,L2,Lx,Rf).

pesquisa(L1,L2,[H|T],Listax,Rf):-subset(L1,H,0,HListax),
	(pesquisa(L1,L2,T,[HListax|Listax],Rf)).

testarvitoria(L1,L2,Lx,Rf):-member(2,Lx),
	pcWin(L1,L2,Lx,0,Rf,Rf).

testarvitoria(_,_,_,_):-!,fail.

pcWin(_,_,[],_,Rf,Rf).

pcWin(L1,L2,[H|T],N,Rf,_):-H \== 2,
	N1 is N + 1,
	pcWin(L1,L2,T,N1,Rf,_).

pcWin(L1,L2,[2|_],N,Rf,Rf):-N1 is N + 1,
	findall(A,(vitoria(A)),Lv),
	pcWin2(L1,L2,Lv,N1,Rf).

pcWin2(L1,L2,[H|_],1,Rf):-pcWin3(L1,L2,H,Rf).

pcWin2(L1,L2,[_|T],N,Rf):-N \== 1,
	N1 is N - 1,
	pcWin2(L1,L2,T,N1,Rf).

pcWin3([],[],[H|_],H).

pcWin3([],[H|T],L,Rf):-member(H,L),
	elimina1(H,L,L3),
	pcWin3([],T,L3,Rf).

pcWin3([],[H|T],L,Rf):- \+member(H,L),
	pcWin3([],T,L,Rf).

pcWin3([H|T],L2,L,Rf):-member(H,L),
	elimina1(H,L,L3),
	pcWin3(T,L2,L3,Rf).

pcWin3([H|T],L2,L,Rf):- \+member(H,L),
	pcWin3(T,L2,L,Rf).

elimina1(N,[N|T],T).

elimina1(N,[H|T],[H|R]):-
	elimina1(N,T,R).


% vai dar counter!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
counter(L,J,Rf):-sort(J, L1),
	findall(A,(vitoria(A)),Lv),!,
	pesquisa2(L,L1,Lv,_,Rf).

subsetCounter([],_,N,N).

subsetCounter([H|T],List,N,Listax):-member(H,List),N1 is N + 1,subsetCounter(T,List, N1,Listax).

subsetCounter([H|T],List,N,Listax):- \+member(H,List),!,subsetCounter(T,List,N,Listax).

pesquisa2(L,L1,[],Listax,Rf):-
	reverse(Listax, Lx),
	nl,
	!,
	testarcounter(L,L1,Lx,Rf).

pesquisa2(L,L1,[H|T],Listax,Rf):-subsetCounter(L1,H,0,HListax),
	(pesquisa2(L,L1,T,[HListax|Listax],Rf)).

testarcounter(L,L1,Lx,Rf):-member(2,Lx),
	pcCounter0(L,L1,Lx,Rf,Rf).

testarcounter(_,_,_,_):-!,fail.

indexOf([Element|_], Element, 0).

indexOf([_|Tail], Element, Index):-
  indexOf(Tail, Element, Index1),
  Index is Index1+1.

pcCounter0(L,L1,T,Rf,Rf):-!,indexOf(T,2,R),
	findall(A,(vitoria(A)),Lv),
	pcCounter2(L,L1,Lv,R,Rf).

pcCounter(_,_,[],_,Rf,Rf):-!.

pcCounter(L,L1,[H|T],N,Rf,_):-H \== 2,
	N1 is N + 1,
	pcCounter(L,L1,T,N1,Rf,_).

pcCounter(L,L1,[2|_],N,Rf,Rf):-N1 is N + 1,
	findall(A,(vitoria(A)),Lv),
	pcCounter2(L,L1,Lv,N1,Rf).

pcCounter2(L,L1,[H|_],0,Rf):-pcCounter3(L,L1,H,Rf).

pcCounter2(L,L1,[_|T],N,Rf):-N \== 0,
	N1 is N - 1,
	pcCounter2(L,L1,T,N1,Rf).

pcCounter3([],[],[H|_],H).

pcCounter3([],[H|T],L,Rf):-member(H,L),
	elimina1(H,L,L3),
	pcCounter3([],T,L3,Rf).

pcCounter3([],[H|T],L,Rf):- \+member(H,L),
	pcCounter3([],T,L,Rf).

pcCounter3([H|T],L2,L,Rf):-member(H,L),
	elimina1(H,L,L3),
	pcCounter3(T,L2,L3,Rf).

pcCounter3([H|T],L2,L,Rf):- \+member(H,L),
	pcCounter3(T,L2,L,Rf).


%vai jogar na melhor prob!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
melhorjogada(P,J,Rf):-sort(P, L1),
	sort(J,L2),
	findall(A,(vitoria(A)),Lv),
	pesquisa3(L1,L2,Lv,_,_,Rf).

subsetmj([],_,N,N).

subsetmj([H|T],List,N,Listax):-member(H,List),N1 is N + 1,subsetmj(T,List, N1,Listax).

subsetmj([H|T],List,N,Listax):- \+member(H,List),!,subsetmj(T,List,N,Listax).

pesquisa3(L1,L2,[],Listax,Listax2,Rf):-
	reverse(Listax, Lx),
	reverse(Listax2,Lx2),
	!,
	testarmj(L1,L2,Lx,Lx2,1,Rf).

pesquisa3(L1,L2,[H|T],Listax,Listax2,Rf):-subsetmj(L1,H,0,HListax),
	subsetmj(L2,H,0,HListax2),
	(pesquisa3(L1,L2,T,[HListax|Listax],[HListax2|Listax2],Rf)).

testarmj(L1,L2,Lx,[1|T2],N,Rf):-subs(N,Lx,Rlx),
	N1 is N + 1,
	testarmj(L1,L2,Rlx,T2,N1,Rf).

testarmj(L1,L2,Lx,[2|T2],N,Rf):-subs(N,Lx,Rlx),
	N1 is N + 1,
	testarmj(L1,L2,Rlx,T2,N1,Rf).

testarmj(L1,L2,Lx,[H|T2],N,Rf):-H \== 1,
	H \== 2,
	N1 is N + 1,
	testarmj(L1,L2,Lx,T2,N1,Rf).

testarmj(L1,_,Lx,[],_,Rf):-!,
	pcmj(L1,Lx,Rf).

subs(1,[_|T],[-1|T]).

subs(N,[H|T],[H|Lx]):-N > 1,
	N1 is N - 1,
	subs(N1,T,Lx).

pcmj(L1,Lx,Rf):-max(Lx,Max),
	pcmj1(L1,Lx,Max,0,Rf).

pcmj1(L1,[H|T],Max,N,Rf):-H \== Max,
	N1 is N + 1,
	pcmj1(L1,T,Max,N1,Rf).

pcmj1(L1,[Max|_],Max,N,Rf):-N1 is N + 1,
	findall(A,(vitoria(A)),Lv),
	pcmj2(L1,Lv,N1,Rf).

pcmj2(L1,[H|_],1,Rf):-pcmj3(L1,H,Rf).

pcmj2(L1,[_|T],N,Rf):-N \== 1,
	N1 is N - 1,
	pcmj2(L1,T,N1,Rf).

pcmj3([],[H|_],H).

pcmj3([H|T],[H2|T2],Rf):-H \== H2,
	pcmj3(T,[H2|T2],Rf).

pcmj3([H|T],[H|B],Rf):-pcmj3(T,B,Rf).

max([X],X).

max([X|Xs],X):- max(Xs,Y), X >=Y.

max([X|Xs],N):- max(Xs,N), N > X.