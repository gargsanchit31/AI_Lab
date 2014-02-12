#include "PriorityQueue.h"
#include <vector>
#include <iostream>
using namespace std;



template<class ID>
struct node{
    string x;
    ID f;
    int index;
};

template<class ID>
struct lt {
    bool operator()(const node<ID>* v1, const node<ID> * v2){
        if(v1->f < v2->f) return true;
        return false;
    }
};

int main(){
    node<int> *v1 = new node<int>();
    node<int> *v2 = new node<int>();
    node<int> *v3 = new node<int>();
    v1->f = 6;
    v2->f = 3;
    v3->f = 4;
    v1->index = -1;
    v2->index = -1;
    v3->index = -1;
    
    cout << "lt() in action " << lt<int>()(v1,v2) <<endl;
    Priority_Q< node<int>*, lt<int> > queue; //if lt is < operator, then min Priority queue will be formed

    queue.push(v1);
    queue.print();
    queue.push(v2);
    queue.print();
    queue.push(v3);
    queue.print();

    v3->f = v3->f - 11;
    queue.percolateUp(v3->index);
    queue.print();

    cout << "poppings " <<endl;
    queue.pop();
    queue.print();
    queue.pop();
    queue.print();
    queue.pop();
    queue.print();
}
