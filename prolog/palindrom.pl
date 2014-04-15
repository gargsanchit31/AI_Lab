type(xor1,xor).
type(xor2,xor).
type(not1,not).
type(not2,not).
type(and1,and).

type(x1,term).
type(x2,term).
type(x3,term).
type(x4,term).
type(x5,term).
type(x6,term).

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

signal(X1,X2,X3,X4,X5, Y) :- valid(X1,X2,X3,X4,X5,Y), signal(X1,X2,X3,X4,X5,x6,Y).

% ===========================

%AND gate
signal(X1,X2,X3,X4,X5,T,1) :- connected(out(G), T), type(G, and), signal(X1,X2,X3,X4,X5,in(1,G),1), signal(X1,X2,X3,X4,X5,in(2,G),1).
signal(X1,X2,X3,X4,X5,T,0) :- connected(out(G), T), type(G, and), \+ signal(X1,X2,X3,X4,X5,T,1).

%OR gate
signal(X1,X2,X3,X4,X5,T,0) :- connected(out(G), T), type(G, or), signal(X1,X2,X3,X4,X5,in(1,G),0), signal(X1,X2,X3,X4,X5,in(2,G),0).
signal(X1,X2,X3,X4,X5,T,1) :- connected(out(G), T), type(G, or), \+ signal(X1,X2,X3,X4,X5,T,0).


%NOT gate
signal(X1,X2,X3,X4,X5,T, 0) :- connected(out(G), T), type(G, not), signal(X1,X2,X3,X4,X5,in(1,G),1).
signal(X1,X2,X3,X4,X5,T, 1) :- connected(out(G), T), type(G, not), \+ signal(X1,X2,X3,X4,X5,T, 0).

%XOR gate
signal(X1,X2,X3,X4,X5,T,0) :- connected(out(G), T), type(G, xor), signal(X1,X2,X3,X4,X5,in(1,G),Y1), signal(X1,X2,X3,X4,X5,in(2,G),Y2), 								equal(Y1,Y2).
signal(X1,X2,X3,X4,X5,T,1) :- connected(out(G), T), type(G, xor), \+ signal(X1,X2,X3,X4,X5,T,0).

%direct if lhs of connected is terminal
signal(X1,X2,X3,X4,X5,T, 1) :- connected(T1, T), type(T1, term), signal(X1,X2,X3,X4,X5,T1, 1). %case when signal(in(1,a1), S) called
signal(X1,X2,X3,X4,X5,T, 0) :- connected(T1, T), type(T1, term), signal(X1,X2,X3,X4,X5,T1, 0). %case when signal(in(1,a1), S) called

signal(X1,X2,X3,X4,X5,x1,X1) :- valid(X1,X2,X3,X4,X5,0).
signal(X1,X2,X3,X4,X5,x2,X2) :- valid(X1,X2,X3,X4,X5,0).
signal(X1,X2,X3,X4,X5,x3,X3) :- valid(X1,X2,X3,X4,X5,0).
signal(X1,X2,X3,X4,X5,x4,X4) :- valid(X1,X2,X3,X4,X5,0).
signal(X1,X2,X3,X4,X5,x5,X5) :- valid(X1,X2,X3,X4,X5,0).

%check equality
equal(X,X).

%for fixing domain
valid(X1,X2,X3,X4,X5,Y) :- valid(X1), valid(X2), valid(X3), valid(X4), valid(X5), valid(Y).
valid(X) :- member(X,[0,1]).
