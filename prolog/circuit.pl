% signal(X, S) :- member(S, [0, 1]).
% type(X, T) :- member(T, [or, and]).
% x1 ---[in(1,A1)]=|\
%                A1 >=[out(A1)]--- [in(1,A2)]=|A2|>=[out(A2)]-----x3
% x2 ---[in(2,A2)]=|/

type(a1, and).
type(a2, not).
connected(x1, in(1, a1)).
connected(x2, in(2, a1)).
connected(out(a1), in(1, a2)).
connected(out(a2), x3).

signal(x1, 1).
signal(x2, 1).

%===========

%direct if lhs of connected is terminal
signal(T, 1) :- connected(T1, T), signal(T1, 1). %case when signal(in(1,a1), S) called

%AND gate
signal(T, 1) :- connected(out(G), T), type(G, and), signal(in(1,G), 1), signal(in(2,G),1), !.
signal(T, 0) :- connected(out(G), T), type(G, and),!.
%OR gate
signal(T, 0) :- connected(out(G), T), type(G, or), signal(in(1,G), 0), signal(in(2,G),0), !.
signal(T, 1) :- connected(out(G), T), type(G, or),!.
%NOT gate
signal(T, 0) :- connected(out(G), T), type(G, not), signal(in(1,G), 1), !.
signal(T, 1) :- connected(out(G), T), type(G, not),!.
