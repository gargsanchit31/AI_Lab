New Strategy:
* if some lhs is of the form (A-B) add axiom1 :  B-(A-B)
* if whole line is of form  (A-(B-C)):  expand it using axiom2 
    i.e add (A-(B-C)) - ((A-B)-(A-C)) to list
    Here we are simplifying a complicated expr into two simpler expression, when we later apply modes-pones

    Optimization : once expanded, the newly added formula must not be considered for further expansion.Its useless.

* if some lhs is of the form (A-B)-(A-C): treat it as rhs of axiom2
    i.e add (A-(B-C)) - ((A-B)-(A-C))
    So now we need to prove (A-(B-C))
* if some lhs is of the form (A-F), we can't use axiom1
    So use axiom2, but now treat   (A-F) as
                                     |
                                     \/
                (A-(X-C)) - ((A-X)-(A-C))
    Now for X use all seeds and previous expression in proof-list

* if whole line is of the for (A-F)-F
    Simply use axiom3 to add
      ((A-F)-F)-A)
    So on applying MP, we get A in next round
