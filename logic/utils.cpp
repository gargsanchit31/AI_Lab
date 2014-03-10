#include "utils.h"
using namespace std;
FNode* parse(){ //formula is either 'a' OR (<f> - <f>)
    FNode * formula;

    char x;
    cin >> x;
    if(x != '('){//i.e its 'a'
        formula = new FNode(x);
        return formula;
    }

    //its (f - f)
    FNode * lhs;
    FNode * rhs;
    lhs = parse();

    cin >>x ; //for '-'
    if(x != '-'){ //Error checking
        cout << "Found character '" << x <<"'. Expected '-'" <<endl;
        return NULL;
    }

    rhs = parse();

    cin >> x; //for ')'
    if(x != ')'){ //Error checking
        cout << "Found character '" << x <<"'. Expected ')'" <<endl;
        return NULL;
    }

    formula = new FNode('-', lhs, rhs);

    return formula;
}
