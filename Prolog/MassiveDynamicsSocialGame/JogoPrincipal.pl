:-use_module(library(odbc)).

:-dynamic user1/2.
:-dynamic relacoes/3.

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

odbc_con:-
	odbc_connect('ConDB', _,[ user('ARQSI042'),password('potato'),alias('ConDB'),encoding(utf8),open(once)]).

getHumors(X):-
	findall(Y,odbc_query('ConDB','select nome from Humors',row(Y)),X).

getUsers(LR):-
	odbc_con,
	findall((Id,User),odbc_query('ConDB','select Id,UserName from AspNetUsers',
	row(Id,User)),LR),
	insertUser(LR),
	odbc_disconn.

insertUser([]).

insertUser([H|T]):-
	assertz(user1(H)),
	insertUser(T).

getRelations(LR):-
	odbc_con,
	findall((UserID1,UserID2,Peso),
	odbc_query('ConDB','select R.user1ID, R.user2ID, R.peso from Relacaos R;',
	    row(UserID1,UserID2,Peso)),LR),
	insertRelations(LR),
	odbc_disconn.

insertRelations([]).

insertRelations([H|T]):-
	assertz(relacoes(H)),
	insertRelations(T).

odbc_disconn:-
	odbc_disconnect('ConDB').


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

%Sugestão de amigos

sugerirAmigosPorTag(U, LR):-
	user(U,LTag,_),
	length(LTag,TL),
        TL>=3,
	sugestaoAmigosTag(U,3,LR).

sugestaoAmigosTag(U,N,LR):-
	user(U,LTagU),
	findall(User,(amigos(U,User)),LA),
	findall(User,(user(User,_),User\==U,\+member(User,LA)),LU),
	%eliminaAmigos(LA,LU,[],LRAUX),
	sugestaoAmigosTag(N,LTagU,LU,[],LR).

sugestaoAmigosTag(_,_,[],RF,RF).

sugestaoAmigosTag(N,LTagU,[H|T],LR,RF):-
	user(H,LTagH),
	inter(LTagU,LTagH,LRT),
	length(LRT,TL),
	TL>=N,
        sugestaoAmigosTag(N,LTagU,T,[H|LR],RF).

sugestaoAmigosTag(N,LTagU,[_|T],LR,RF):-
	sugestaoAmigosTag(N,LTagU,T,LR,RF).



sugestaoAmigosTag(_,_,[],RF,RF).

sugestaoAmigosTag(N,LTagU,[H|T],LR,RF):-
	user(H,LTagH),
	inter(LTagU,LTagH,LRT),
	length(LRT,TL),
	TL>=N,
        sugestaoAmigosTag(N,LTagU,T,[H|LR],RF).

sugestaoAmigosTag(N,LTagU,[_|T],LR,RF):-
	sugestaoAmigosTag(N,LTagU,T,LR,RF).

%Sugestão por outros amigos

%sugerir amizades para utilizador X
sugerirAmizades(User,L):-getLigacoes1,
                                        getTagsUtilizadores,
                                        getIdAmigos(User,LA,User),
                                        amigosSug(LA,LX,User),
                                        eliminaRep(LA,LX,LX1),
                                        conexoesPart(LA,LX1,LF),
                                        tagsPar(LF,User,LT),
                                        sort(LT,LTS),
                                        reverse(LTS,LTSR),
                                        LTSR=L,
                                        retractall(nos(_,_)),
                                        retractall(ligas(_,_,_,_,_)).

%elimina os amigos do utilizador
eliminaRep(_,[],[]).
eliminaRep(LA,[H|T],[H|T1]):-not(member(H,LA)),
                           eliminaRep(LA,T,T1).
eliminaRep(LA,[_|T],T1):-eliminaRep(LA,T,T1).

%vai buscar a rede do utilizador
amigosSug([],[],_).
amigosSug([H|T],L,Orig):-getIdAmigos(H,L1,Orig),
        amigosSug(T,L2,Orig),
        append(L1,L2,L).

%calculo das ligaçoes em comum
conexoesPart(_,[],_).
conexoesPart(LA,[H|T],[(C,H)|LF]):-conexoesPart1(LA,H,C),
                                                conexoesPart(LA,T,LF).

conexoesPart1(LA,H,C):-getIdAmigos(H,L1,H),
                                                contaConexoes(LA,L1,C).

contaConexoes([],_,0).
contaConexoes([H|T],L1,C):-member(H,L1),contaConexoes(T,L1,C1),C is C1+1.
contaConexoes([_|T],L1,C):-contaConexoes(T,L1,C).

%calculo das tags em comum
tagsPar([],_,[]).
tagsPar([(C,U1)|T],User,[(Total,U1)|LT]):-nos(U1,LU1),
                                                        nos(User,LUP),
                                                        contaTags(LU1,LUP,Cont),
                                                        Total is Cont+C,
                                                        tagsPar(T,User,LT).

contaTags(_,[],0).
contaTags(LU1,[H|T],Cont):-member(H,LU1),contaTags(LU1,T,C1),Cont is C1+1.
contaTags(LU1,[_|T],Cont):-contaTags(LU1,T,Cont).

%Caminho Mais Forte
%%	--------------------------------------------

caminhoMaisForte(Orig, Dest, Cam, Custo):-
    caminhoMaisForte2(Dest,[(0,[Orig])],Cam, Custo).

caminhoMaisForte2(Dest,[(Custo,[Dest|T])|_],Cam,Custo):-
    !,reverse([Dest|T],Cam).

caminhoMaisForte2(Dest,[(Ca,[H|T])|Outros], Cam, Custo):-
    findall((Cax,[X,H|T]),(Dest\==H,arco(H,X,Cx),\+member(X,[H|T]),
                   Cax is Cx+Ca),Novos),
    append(Novos,Outros,Todos),
    sort(Todos,TodosOrd),
    reverse(TodosOrd,To),
    caminhoMaisForte2(Dest,To,Cam,Custo).



















































