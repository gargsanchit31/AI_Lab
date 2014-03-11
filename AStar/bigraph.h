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
    float parent_edge_cost;//this is cost of the edge to the current set parent
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
    parent_edge_cost =0;

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
    typedef unordered_map<string, NODE*> mygraphtype;
	typedef list<myneighinfo> (*neigh)(NODE*, mygraphtype&);

	typedef typename list<NODE*>::iterator l_itr;
	typedef typename list<myneighinfo>::iterator l_neighinfo_itr;

	NODE* Start;
	NODE* Goal;
    mygraphtype* graph;

	H heuristic; //func
	neigh neighbour; //func
	Priority_Q<NODE*, lt<NODE> > open_list;

public:
	AStar(NODE*, NODE*, H, neigh, mygraphtype*);
	~AStar();
	int run();
	NODE* getStart();
	NODE* lowest_fnode();
	NODE* find_in_list(NODE*, list<NODE*>);
	int trace(NODE*);
	void init();
	int step(NODE*);
	bool open_list_empty();
	long long open_list_size();
};

template<class NODE>
AStar<NODE>::AStar(NODE* S, NODE* Gl, H h, neigh n, mygraphtype* in_graph){
	Start=S;
	Goal = Gl;
	heuristic = h;
	neighbour = n;
    graph = in_graph;
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
    float cost =0;
	while(n!=NULL){
		n->print_me();
		cost+= n->parent_edge_cost;
		n=n->getparent();
        len++;

	}
    cout << "Length of the optimal path is " << len-1 <<endl;
    cout << "Cost of the optimal path is " << cost <<endl;
    return len-1;
}

template<class NODE>
bool AStar<NODE>::open_list_empty(){
	return open_list.empty();
}

template<class NODE>
void AStar<NODE>::init(){
	Start->_g = 0;
    Start->_h = heuristic(Start);
	open_list.push(Start);
}

template<class NODE>
long long AStar<NODE>::open_list_size(){
	return open_list.size();
}

template<class NODE>
int AStar<NODE>::step(NODE* node){

	NODE * min_node = lowest_fnode();

	//if(Goals.find(min_node) != Goals.end()){
	if(min_node == Goal){
	cout<<"Hurray Goal is"<<endl;
        min_node->print_me();
		int len = trace(min_node);
        return len;
	}

	//closed_list.push_back(min_node);
	min_node->cur_status=1;		//virtually push in the closed list
	node=min_node;

	list<myneighinfo> neighbours = neighbour(min_node, *graph);

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
                node->parent_edge_cost = edge_cost;
                open_list.push(node);
            }
			continue;
		}
		else if(node->cur_status==0){
			if(min_node->_g + 1 < node->_g){ //then set minnode as its parent and update g value
			//cout << "already opennode:" <<endl;
                node->_g =  min_node->_g + edge_cost;
                node->setparent(min_node);
                node->parent_edge_cost = edge_cost;
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
			node->parent_edge_cost = edge_cost; 
            open_list.push(node);

            continue;
		}
	}
	return -1;
}

template<class NODE>
int AStar<NODE>::run(){ //returns length of path found(if any) else return -1
    
	init();

	int count=0;

	while(1){
		if(open_list.empty()){
			cout<<"Something went wrong. open_list can't be empty"<<endl;
            return -1; //path len is -1 (since no path could be found)
		}
		NODE* n1 = (NODE*)malloc(sizeof(NODE));
		int len = step(n1);
		if(len!=-1){
			break;
		}
		free(n1);
	}
}

#endif
