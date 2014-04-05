% prolog
likes(mary,food).
likes(mary,wine).
likes(john,wine).
likes(john,mary).

size([], 0).
size([X|L1], S) :- size(L1, S1), S is S1+1.


myappend([], L, L).
myappend([X|L], L1, [X|R]) :- myappend(L, L1, R).

myreverse([],[]).
myreverse([X|L], L1) :- myreverse(L, L2), myappend(L2, [X], L1).

% sssssssssssss

% signal(X, S) :- member(S, [0, 1]).
% type(X, T) :- member(T, [tor, tand]).

type(gand, tand).
type(gnot, tnot).
in(1, gand, t1). %input 1 of 'g' is t1
in(2, gand, t2). %input 2 of 'g' is t2
out(gand, t3). %input 2 of 'g' is t2
in(1, gnot, t3).
out(gnot, t4).

signal(T, S) :- nb_getval(T, S).
setsignal(T, S) :- nb_setval(T, S).

% And gate
eval(X) :- type(X, tand), in(1, X, I1), in(2, X, I2), signal(I1, 1), signal(I1, 1), write('AND is 1'), out(X, O), setsignal(O,1), !. 
% cut op ! means that futher nothing should be tried i.e next rule will not be looked upon on reaching !.
eval(X) :- type(X, tand),write('AND is 0'), out(X, O), setsignal(O,0), !.

% Or gate
eval(X) :- type(X, tor), in(1, X, I1), in(2, X, I2), signal(I1, 0), signal(I1, 0),  write('OR is 0'), out(X, O), setsignal(O,0), !. 
eval(X) :- type(X, tor),write('OR is 1'), out(X, O), setsignal(O,1),!.

% Not gate
eval(X) :- type(X, tnot), in(1, X, I1), signal(I1, 0),write('NOT is 1'), out(X, O), setsignal(O, 1), !. 
eval(X) :- type(X, tnot), write('NOT is 0'), out(X, O), setsignal(O, 0), !.

% Looping over list
printall([]).
printall([X|L]) :- write(X), print(', '), printall(L).


% Looping over values of signal t1
varyt1([]).
varyt1([X|L]) :- signal(t1, S), S is X, out(g, Y), write(Y), print('\n').
