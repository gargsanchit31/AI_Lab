
% sssssssssssss

% signal(X, S) :- member(S, [0, 1]).
% type(X, T) :- member(T, [tor, tand]).
% x1 ---|\
%       A1 >--- x3
% x2 ---|/

type(a1, tand).
type(a2, tnot).
connected(x1, in(1, a1)).
connected(x2, in(2, a1)).
connected(out(a1), in(1, a2)).
connected(out(a2), x3).
input(x1).
input(x2).
output(x3).

%======extras(elim this asap) =========
terminal(in(1,a1), x1).
terminal(in(2,a1), x2).
terminal(out(a1), t1).

terminal(in(1,a2), t1).
terminal(out(a2), x3).


%===========
signal(T, S) :- input(T), nb_getval(T, S), !.
signal(T, S) :- output(T), nb_getval(T, S), !.
signal(T, S) :- terminal(T, T1), nb_getval(T1, S), !.

setsignal(T, S) :- input(T), nb_setval(T, S), !.
setsignal(T, S) :- output(T), nb_setval(T, S), !.
setsignal(T, S) :- terminal(T, T1), nb_setval(T1, S), !.


eval(T) :- terminal(T, T1), input(T1), !. %val of T is set implicitly at start.
eval(T) :- connected(out(X), T),type(X, tand), write(X),   eval(in(1,X)), eval(in(2,X)), eval(X), !.
eval(T) :- connected(out(X), T), type(X, tnot), write(X), eval(in(1,X)), eval(X), !.

eval(G):- type(G, tand), signal(in(1,G), 1), signal(in(2,G), 1), write('AND is 1\n'), setsignal(out(G),1), !. 
% cut op ! means that futher nothing should be tried i.e next rule will not be looked upon on reaching !.
eval(G) :- type(G, tand),write('AND is 0\n'), setsignal(out(G),0), !.

eval(G):- type(G, tnot), signal(in(1,G), 1), write('NOT is 0\n'), setsignal(out(G),0), !. 
% cut op ! means that futher nothing should be tried i.e next rule will not be looked upon on reaching !.
eval(G) :- type(G, tnot),write('NOT is 1\n'), setsignal(out(G),1), !.

