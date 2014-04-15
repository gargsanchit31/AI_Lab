type(a1,and).
type(a2,and).
type(a3,and).
type(a4,and).
type(a5,and).
type(a6,and).
type(a7,and).
type(a8,and).
type(a9,and).
type(a10,and).
type(a11,and).
type(a12,and).
type(a13,and).
type(a14,and).
type(a15,and).
type(a16,and).
type(a17,and).
type(a18,and).
type(a19,and).
type(a20,and).

type(o1,or).
type(o2,or).
type(o3,or).
type(o4,or).
type(o5,or).
type(o6,or).
type(o7,or).
type(o8,or).
type(o9,or).

type(x1,term).
type(x2,term).
type(x3,term).
type(x4,term).
type(x5,term).
type(x6,term).

connected(x1, in(1, a1)).
connected(x2, in(2, a1)).
connected(out(a1), in(1, a2)).
connected(x3, in(2, a2)).

connected(out(a2), in(1, o1)).

connected(x1, in(1, a3)).
connected(x2, in(2, a3)).
connected(out(a3), in(1, a4)).
connected(x4, in(2, a4)).

connected(out(a4), in(2, o1)).

connected(x1, in(1, a5)).
connected(x2, in(2, a5)).
connected(out(a5), in(1, a6)).
connected(x5, in(2, a6)).

connected(out(a6), in(1, o2)).

connected(x1, in(1, a7)).
connected(x3, in(2, a7)).
connected(out(a7), in(1, a8)).
connected(x4, in(2, a8)).

connected(out(a8), in(2, o2)).

connected(x1, in(1, a9)).
connected(x3, in(2, a9)).
connected(out(a9), in(1, a10)).
connected(x5, in(2, a10)).

connected(out(a10), in(1, o3)).

connected(x1, in(1, a11)).
connected(x4, in(2, a11)).
connected(out(a11), in(1, a12)).
connected(x5, in(2, a12)).

connected(out(a12), in(2, o3)).

connected(x2, in(1, a13)).
connected(x3, in(2, a13)).
connected(out(a13), in(1, a14)).
connected(x4, in(2, a14)).

connected(out(a14), in(1, o4)).

connected(x2, in(1, a15)).
connected(x3, in(2, a15)).
connected(out(a15), in(1, a16)).
connected(x5, in(2, a16)).

connected(out(a16), in(2, o4)).

connected(x2, in(1, a17)).
connected(x4, in(2, a17)).
connected(out(a17), in(1, a18)).
connected(x5, in(2, a18)).

connected(out(a18), in(1, o5)).

connected(x3, in(1, a19)).
connected(x4, in(2, a19)).
connected(out(a19), in(1, a20)).
connected(x5, in(2, a20)).

connected(out(a20), in(2, o5)).


connected(out(o1), in(1,o6)).
connected(out(o2), in(2,o6)).

connected(out(o3), in(1,o7)).
connected(out(o4), in(2,o7)).

connected(out(o6), in(1,o8)).
connected(out(o7), in(2,o8)).

connected(out(o8), in(1,o9)).
connected(out(o5), in(2,o9)).

%result
connected(out(o9), x6).

% ===========================

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
