#include "PriorityQueue.h"
#include <vector>
#include <iostream>
using namespace std;


typedef struct{
    string x;
    float f;
    int index;
    void setIndex(int i){
        index = i;
    }
    int getIndex(int i){
        return index;
    }
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
    cout << "lt() in action " << lt()(v1,v2) <<endl;
    Priority_Q<node*, lt> queue; //if lt is < operator, then min Priority queue will be formed
    queue.push(v1);
    cout << queue.size() <<endl;
    queue.push(v2);
    cout << queue.size() <<endl;
    queue.push(v3);
    cout << queue.size() <<endl;
    cout << "top is" << queue.top()->f <<endl;
    queue.pop();
    cout << "top is" << queue.top()->f <<endl;
    queue.pop();
    cout << "top is" << queue.top()->f <<endl;
    queue.pop();
}
