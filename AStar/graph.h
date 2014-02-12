#ifndef _GRAPH
#define _GRAPH

#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <class ID>
class Node{
private:
	ID _id;
	Node<ID>* parent;

public:	
	float _g;
	Node(ID, float);
	~Node();
	ID getid();
	void setparent(Node*);
	Node* getparent();
	void print_me();
	//friend ostream& operator<<(ostream& os, const Date& dt);

};


template<class ID>
Node<ID>::Node(ID id, float g){
	_id = id;
	_g = g;
	parent = NULL;
}

template<class ID>
Node<ID>::~Node(){
	parent=NULL;
}

template<class ID>
ID Node<ID>::getid(){
	return _id;
}

template<class ID>
void Node<ID>::setparent(Node* n){
	parent=n;
}

template<class ID>
Node<ID>* Node<ID>::getparent(){
	return parent;
}

template<class ID>
void Node<ID>::print_me(){
	cout<<_id<<endl;
}

/////////////////////			A-Star			/////////////////////

template<class NODE>
class AStar{
private:

	typedef float (*H)(NODE*) ;
	typedef list<NODE*> (*neigh)(NODE*);

	NODE* Start;
	NODE* Goal;
	H _h;
	list<NODE*> open_list;
	list<NODE*> closed_list;

public:
	AStar(NODE*, NODE*, H, neigh);
	~AStar();
	neigh neighbour;
	float f(NODE*);
	void run();
	NODE* getStart();
	NODE* getGoal();

};

template<class NODE>
AStar<NODE>::AStar(NODE* S, NODE* G, H h,  neigh n){
	Start=S;
	Goal = G;
	_h = h;
	neighbour = n;
}

template<class NODE>
AStar<NODE>::~AStar(){
	
}

template<class NODE>
NODE* AStar<NODE>::getStart(){
	return Start;
}

template<class NODE>
NODE* AStar<NODE>::getGoal(){
	return Goal;
}

template<class NODE>
float AStar<NODE>::f(NODE* n){
	float ret = n->_g + _h(n);
}

template<class NODE>
void AStar<NODE>::run(){
	
}

#endif