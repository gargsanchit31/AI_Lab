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

/////////////////////       Struct NeighInfo      /////////////////////
template <class T> 
struct NeighInfo {
    float edge_cost; 
    T* node; 
};

/////////////////////			A-Star			/////////////////////

template<class NODE>
class AStar{
private:

	typedef float (*H)(NODE*) ;

	typedef NeighInfo<NODE> myneighinfo;
	typedef list<myneighinfo> (*neigh)(NODE*);

	typedef typename list<NODE*>::iterator l_itr;
	typedef typename list<myneighinfo>::iterator l_neighinfo_itr;

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
    for(; it!=G.end(); it++){
        Goals[*it] = true;
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
    cout << "Tracing Path " << endl;
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
		cout<<"Hurray Goal is"<<endl;
            min_node->print_me();
			int len = trace(min_node);
            return len;
		}

		//closed_list.push_back(min_node);
		min_node->cur_status=1;		//virtually push in the closed list
		//min_node->print_me();


		list<myneighinfo> neighbours = neighbour(min_node);
		//cout<<"Neighbour Size: "<<neighbours.size()<<endl;
		l_neighinfo_itr it = neighbours.begin();
		for(;it!=neighbours.end();it++){
            NODE* node = (*it).node; //neighbour node
            float edge_cost = (*it).edge_cost;

			if(node->cur_status==1){//if node exists in the closed list, do nothing
				if(min_node->_g + 1 < node->_g){ //then set minnode as its parent and update g value
                    cout<<"not monotone\n";
                    node->cur_status=0;		//put it in open node
                    node->_g =  min_node->_g + edge_cost;
                    node->setparent(min_node);
                    open_list.push(node);
                }
				continue;
			}
			else if(node->cur_status==0){
				if(min_node->_g + 1 < node->_g){ //then set minnode as its parent and update g value
				//cout << "already opennode:" <<endl;
                    node->_g =  min_node->_g + edge_cost;
                    node->setparent(min_node);
                    open_list.percolateUp(node->index); //this will update the priority queue appopriately

					continue;
				}
			}
			else{
				//cout << "discovered" <<endl;
				node->cur_status=0;		//put it in open node
				node->_g = min_node->_g + 1;	//increment the _g value by 1;
                node->_h = heuristic(node);
				node->setparent(min_node);		//set its parent 
                open_list.push(node);

                count++;
                if(count%1000==0) cout << count << "  OL Size" <<open_list.size() <<endl;
				
                continue;
			}
		}
	}
}

#endif
