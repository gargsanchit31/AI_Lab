#include "PriorityQueue.h"
#include <vector>
#include <iostream>
using namespace std;


typedef struct{
    string x;
    float f;
    int index;
} node;

struct lt {
    bool operator()(const node * v1, const node * v2){
        if(v1->f < v2->f) return true;
        return false;
    }
};

int main(){
    node *v1 = new node();
    node *v2 = new node();
    node *v3 = new node();
    v1->f = 6;
    v2->f = 3;
    v3->f = 4;
    v1->index = -1;
    v2->index = -1;
    v3->index = -1;
    cout << "lt() in action " << lt()(v1,v2) <<endl;
    Priority_Q<node*, lt> queue; //if lt is < operator, then min Priority queue will be formed

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
