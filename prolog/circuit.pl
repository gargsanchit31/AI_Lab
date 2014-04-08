% signal(X, S) :- member(S, [0, 1]).
% type(X, T) :- member(T, [or, and]).
% x1 ---[in(1,A1)]=|\
%                A1 >=[out(A1)]--- [in(1,A2)]=|A2|>=[out(A2)]-----x3
% x2 ---[in(2,A2)]=|/

type(a1, and).
type(a2, or).
connected(x1, in(1, a1)).
connected(x2, in(2, a1)).

connected(out(a1), in(1, a2)).
connected(x3, in(2, a2)).

connected(out(a2), x4).

signal(x1, 1).
signal(x2, 1).
signal(x3, 0).

type(x1, end).
type(x2, end).
type(x3, end).

%===========


%AND gate
signal(T, 1) :- connected(out(G), T), type(G, and), signal(in(1,G), Y1), signal(in(2,G),Y2), Y1 is 1, Y2 is 1, print(G), write(' : AND 1\n'), !.
signal(T, 0) :- connected(out(G), T), type(G, and), print(G), write(' : AND 0\n'),!.
%OR gate
signal(T, 0) :- connected(out(G), T), type(G, or), signal(in(1,G), Y1), signal(in(2,G),Y2), Y1 is 0, Y2 is 0, print(G), write(': OR 0\n'), !.
signal(T, 1) :- connected(out(G), T), type(G, or), print(G), write(' : OR 1\n'), !.
%NOT gate
signal(T, 0) :- connected(out(G), T), type(G, not), signal(in(1,G), Y1), Y1 is 1, print(G), write(' : NOT 0\n'), !.
signal(T, 1) :- connected(out(G), T), type(G, not),print(G), write(' : NOT 0\n'),!.

%direct if lhs of connected is terminal
signal(T, 1) :- connected(T1, T),type(T1,end), signal(T1, 1),print(T1), write(' : direct 1\n'), !. %case when signal(in(1,a1), S) called
signal(T, 0) :- connected(T1, T),type(T1,end), signal(T1, 0),print(T1), write(' : direct 0\n'), !. %case when signal(in(1,a1), S) called
