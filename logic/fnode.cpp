#include "fnode.h"
using namespace std;

FNode::FNode(){
    lhs = NULL;
    rhs = NULL;
    val = '-';
}

FNode::FNode(char tval, FNode * tlhs, FNode * trhs){
    lhs = tlhs;
    rhs = trhs;
    val = tval;
}

FNode::FNode(char tval){
    lhs = NULL;
    rhs = NULL;
    val = tval;
}

void FNode::print(){
    if(val == '-'){//recusively print lhs & rhs
        cout << "(";
        lhs->print();
        cout << "-";
        rhs->print();
        cout<<")";
    }
    else{//it's leaf
        cout << val;
    }
}

bool FNode::operator == (const FNode & node){
    if(val == node.val && val=='-'){
        //recusively check lhs and rhs
        return ((*lhs == *node.lhs) && (*rhs == *node.rhs));
    }
    else if(val == node.val){
        return true;
    }
    return false;
}
