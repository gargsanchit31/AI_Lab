#ifndef _GRAPH
#define _GRAPH

#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <unordered_map>
#include "PriorityQueue.h"
using namespace std;

template <class ID>
class Node{
private:
	ID _id;
	Node<ID>* parent;

public:	
	int cur_status;		//-1 -> not seen yet, 0 -> in open_list, 1-> in closed_list

    /*** to be used by A-star **/
	float _g; // this value is set and updated by A-star as algo progresses. Set first just before putting into open list
    float _h; // this value is set just before putting it into OL of A-star.And then it is never changed.
    int index;//position in the PriorityQueue
    /*** to be used by A-star **/

	Node(ID);
	~Node();
	ID getid();
	void setparent(Node*);
	Node* getparent();
	void print_me();
	//friend ostream& operator<<(ostream& os, const Date& dt);
};


template<class ID>
Node<ID>::Node(ID id){
	_id = id;

    _g = -1;
    _h = -1;
    index = -1;

	parent = NULL;
	cur_status = -1; //not seen yet
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

template<class NODE>
struct lt { //less than defined for all nodes (comparing f = g+h)
    bool operator()(const NODE* v1, const NODE* v2){
        if( (v1->_g + v1->_h) < (v2->_g + v2->_h) ) return true;
        return false;
    }
};


/////////////////////			A-Star			/////////////////////

template<class NODE>
class AStar{
private:

	typedef float (*H)(NODE*) ;
	typedef list<NODE*> (*neigh)(NODE*);
	typedef typename list<NODE*>::iterator l_itr;

	NODE* Start;
    unordered_map<NODE*, bool> Goals;

	H heuristic; //func
	neigh neighbour; //func
	Priority_Q<NODE*, lt<NODE> > open_list;

public:
	AStar(NODE*, list<NODE*>, H, neigh);
	~AStar();
	int run();
	NODE* getStart();
	NODE* lowest_fnode();
	NODE* find_in_list(NODE*, list<NODE*>);
	int trace(NODE*);
};

template<class NODE>
AStar<NODE>::AStar(NODE* S, list<NODE*> G, H h,  neigh n){
	Start=S;
	l_itr it = G.begin();
    NODE * temp;
    for(; it!=G.end(); it++){
        temp = *it;
        Goals[*it] = true;
    }
	if(Goals.find(temp) != Goals.end()){
        cout << "Hash Map working" <<endl;
    }
	heuristic = h;
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
NODE* AStar<NODE>::lowest_fnode(){ //assuming open list is not null(check before calling this)
    NODE * n = open_list.top();
    open_list.pop();
    return n;
}

template<class NODE>
int AStar<NODE>::trace(NODE* n){
    int len=0;
	while(n!=NULL){
		n->print_me();
		n=n->getparent();
        len++;
	}
    cout << "Length of the optimal path is " << len-1 <<endl;
    return len-1;
}

template<class NODE>
int AStar<NODE>::run(){ //returns length of path found(if any) else return -1
    
	Start->_g = 0;
    Start->_h = heuristic(Start);

	open_list.push(Start);

	int count=0;

	while(1){
		if(open_list.empty()){
			cout<<"Something went wront. open_list can't be empty"<<endl;
            return -1; //path len is -1 (since no path could be found)
		}

		NODE * min_node = lowest_fnode();

		if(Goals.find(min_node) != Goals.end()){
			cout<<"Hurray"<<endl;
			int len = trace(min_node);
            return len;
		}

		//closed_list.push_back(min_node);
		min_node->cur_status=1;		//virtually push in the closed list
		//min_node->print_me();


		list<NODE*> neighbours = neighbour(min_node);
		//cout<<"Neighbouor Size: "<<neighbours.size()<<endl;
		l_itr it = neighbours.begin();
		for(;it!=neighbours.end();it++){

			if((*it)->cur_status==1){//if node exists in the closed list, do nothing
				if(min_node->_g + 1 < (*it)->_g){ //then set minnode as its parent and update g value
                    cout<<"not monotone\n";
                    (*it)->cur_status=0;		//put it in open node
                    (*it)->_g =  min_node->_g + 1;
                    (*it)->setparent(min_node);
                    open_list.push(*it);
                }
				continue;
			}
			else if((*it)->cur_status==0){
				if(min_node->_g + 1 < (*it)->_g){ //then set minnode as its parent and update g value
				//cout << "already opennode:" <<endl;
                    (*it)->_g =  min_node->_g + 1;
                    (*it)->setparent(min_node);
                    open_list.percolateUp((*it)->index); //this will update the priority queue appopriately

					continue;
				}
			}
			else{
				//cout << "discovered" <<endl;
				(*it)->cur_status=0;		//put it in open node
				(*it)->_g = min_node->_g + 1;	//increment the _g value by 1;
                (*it)->_h = heuristic(*it);
				(*it)->setparent(min_node);		//set its parent 
                open_list.push(*it);

                count++;
                if(count%1000==0) cout << count << "  OL Size" <<open_list.size() <<endl;
				
                continue;
			}
		}
	}
}

#endif
