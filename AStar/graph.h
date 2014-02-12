#ifndef _GRAPH
#define _GRAPH

#include <iostream>
#include <cstdlib>
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
	typedef typename list<NODE*>::iterator l_itr;

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
	NODE* lowest_fnode();
	NODE* find_in_list(NODE*, list<NODE*>);
	void trace(NODE*);

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
NODE* AStar<NODE>::lowest_fnode(){ //assuming open list is not null(check before calling this)
	l_itr it=open_list.begin();
	float min_f = f(*it);
	NODE* min_node = *it;
	l_itr min_itr = it;

	for(;it!=open_list.end();it++){
		if(f(*it) < min_f){
			min_f = f(*it);
			min_node = *it;
			min_itr = it;
		}
		else if(f(*it) == min_f){
			if((*it)->_g > min_node->_g){
				min_node = *it;
				min_itr = it;
			}
		}
	}
	open_list.erase(min_itr);
	return min_node;
}

template<class NODE>
NODE* AStar<NODE>::find_in_list(NODE* n, list<NODE*> l){
	l_itr it=l.begin();
	for(;it!=l.end();it++){
		if(n->getid() == (*it)->getid()){
			return (*it);
		}
	}
	return NULL;
}

template<class NODE>
void AStar<NODE>::trace(NODE* n){
	while(n!=NULL){
		n->print_me();
		n=n->getparent();
	}
}

template<class NODE>
void AStar<NODE>::run(){
	Start->_g = 0;
	open_list.push_back(Start);
	int count=0;

	while(1){
		if(open_list.empty()){
			cout<<"open_list can't be empty"<<endl;
			exit(0);
		}

		NODE * min_node = lowest_fnode();

		if(min_node->getid() == Goal->getid()){
			cout<<"Hurray"<<endl;
			trace(min_node);
			break;
		}

		closed_list.push_back(min_node);
		//min_node->print_me();
		//cout<<"Count is: "<<++count<<endl;


		list<NODE*> neighbours = neighbour(min_node);
		//cout<<"Neighbouor Size: "<<neighbours.size()<<endl;
		l_itr it = neighbours.begin();
		for(;it!=neighbours.end();it++){
			NODE * orig = find_in_list(*it, closed_list);
			if(orig != NULL) { //if node exists in the closed list, the delete the copy 
				cout << "a" <<endl;
				delete  *it;
				continue;
			}

			orig = find_in_list(*it, open_list);
			if(orig != NULL) { //if node exists in the open list, update g if neccessary, and the delete the copy 
				if((*it)->_g < orig->_g){
					cout << "b" <<endl;
					orig->_g = (*it)->_g;
					orig->setparent(min_node);
				}
				delete  *it;
				continue;
			}
			cout << "c" <<endl;
			(*it)->_g = min_node->_g + 1;
			(*it)->setparent(min_node);
			open_list.push_back(*it);
		}

	}
}

#endif