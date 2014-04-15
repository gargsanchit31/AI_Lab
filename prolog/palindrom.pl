type(xor1,xor).
type(xor2,xor).
type(not1,not).
type(not2,not).
type(and1,and).

connected(x1,in(1,xor1)).
connected(x5,in(2,xor1)).
connected(x2,in(1,xor2)).
connected(x4,in(2,xor2)).

connected(out(xor1),in(1,not1)).
connected(out(xor2),in(1,not2)).

connected(out(not1), in(1,and1)).
connected(out(not2), in(2,and1)).

connected(out(and1), x6).

%============================

signal(x1,1).
signal(x2,0).
signal(x3,1).
signal(x4,1).
signal(x5,1).

% ===========================

%AND gate
signal(T, 1) :- connected(out(G), T), type(G, and), signal(in(1,G), Y1), signal(in(2,G),Y2), Y1 is 1, Y2 is 1, print(G), write(' : AND 1\n'), !.
signal(T, 0) :- connected(out(G), T), type(G, and), print(G), write(' : AND 0\n'),!.

%OR gate
signal(T, 0) :- connected(out(G), T), type(G, or), signal(in(1,G), Y1), signal(in(2,G),Y2), Y1 is 0, Y2 is 0, print(G), write(': OR 0\n'), !.
signal(T, 1) :- connected(out(G), T), type(G, or), print(G), write(' : OR 1\n'), !.

%NOT gate
signal(T, 0) :- connected(out(G), T), type(G, not), signal(in(1,G), Y1), Y1 is 1, print(G), write(' : NOT 0\n'), !.
signal(T, 1) :- connected(out(G), T), type(G, not),print(G), write(' : NOT 1\n'),!.

%XOR gate
signal(T, 0) :- connected(out(G), T), type(G, xor),  signal(in(1,G), Y1), signal(in(2,G),Y2), equal(Y1,Y2), print(G), write(' : XOR 0\n'), !.
signal(T, 1) :- connected(out(G), T), type(G, xor), signal(in(1,G), Y1), signal(in(2,G),Y2), \+ equal(Y1,Y2), print(G), write(' : XOR 1\n'), !.

%direct if lhs of connected is terminal
signal(T, 1) :- connected(T1, T), signal(T1, 1),print(T1), write(' : direct 1\n'), !. %case when signal(in(1,a1), S) called
signal(T, 0) :- connected(T1, T), signal(T1, 0),print(T1), write(' : direct 0\n'), !. %case when signal(in(1,a1), S) called

%check equality
equal(X,X).
