#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"
using namespace std;

typedef vector<vector<int> > _8sq;
typedef Node<_8sq> mynode;

typedef struct{
	int row;
	int col;
} pos_pair;

unordered_map<string, mynode*> graph;

//overload the << operator for printing vector
ostream& operator<<(ostream& os, const _8sq v)
{
     for(int i=0;i<v.size();++i){
     	for(int j=0;j<v[i].size();++j){
     		os << v[i][j]<< " ";
    	}
    	os << "\n";
    }
    return os;
}

bool operator==(const _8sq& v1, const _8sq& v2)
{
     for(int i=0;i<v1.size();++i){
     	for(int j=0;j<v1[i].size();++j){
     		if(v1[i][j]!=v2[i][j]){
     			return false;
     		}
    	}
    }
    return true;
}

void swap(int &a, int &b){
	int temp=a;
	a=b;
	b=temp;
}

string getkey(_8sq v){
	string key= "";
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v[i].size();j++){
			key+= to_string(v[i][j]);
		}
	}
	return key;
}

pos_pair find(_8sq v, int n){
	pos_pair p;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(v[i][j]==n){
				p.row=i;
				p.col=j;
				return p;
			}
		}
	}
}

//neighbour function
// list<Node< _8sq >* > myneigh(Node< _8sq >* n){
// 	list<Node< _8sq >*> l;

// 	_8sq id = n->getid();
// 	pos_pair p = find(id, 9);
// 	int row=p.row;
// 	int col = p.col;
// 	if(row == 0 or row == 1){
// 		_8sq id1 = id;
// 		swap(id1[row][col], id1[row+1][col]);
// 		Node<_8sq>* n1 = new Node<_8sq>(id1,-1);
// 		l.push_back(n1);
// 	}
// 	if(row == 2 or row == 1){
// 		_8sq id1 = id;
// 		swap(id1[row][col], id1[row-1][col]);
// 		Node<_8sq>* n1 = new Node<_8sq>(id1,-1);
// 		l.push_back(n1);
// 	}
// 	if(col==0 or col==1){
// 		_8sq id1 = id;
// 		swap(id1[row][col], id1[row][col+1]);
// 		Node<_8sq>* n1 = new Node<_8sq>(id1,-1);
// 		l.push_back(n1);
// 	}
// 	if(col==2 or col==1){
// 		_8sq id1 = id;
// 		swap(id1[row][col], id1[row][col-1]);
// 		Node<_8sq>* n1 = new Node<_8sq>(id1,-1);
// 		l.push_back(n1);
// 	}

// 	return l;
// }


list<mynode* > myneigh(mynode* n){
	list<mynode*> l;

	_8sq id = n->getid();
	pos_pair p = find(id, 9);

	int row=p.row;
	int col = p.col;

	if(row == 0 or row == 1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row+1][col]);
		string key = getkey(id1);
		//cout<<"a"<<endl;
		if(graph.find(key) == graph.end()){
			cout<<"a1"<<endl;
			mynode* n1 = new mynode(id1,-1);
			graph[key]=n1;
			l.push_back(n1);
		}
		else{
			//map wala dedo
			cout<<"a2"<<endl;
			l.push_back(graph[key]);
		}
	}
	if(row == 2 or row == 1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row-1][col]);
		string key = getkey(id1);
		
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1,-1);
			graph[key]=n1;
			l.push_back(n1);
			cout<<"b1"<<endl;
		}
		else{
			//map wala dedo
			cout<<"b2"<<endl;
			l.push_back(graph[key]);
		}
	}
	if(col==0 or col==1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row][col+1]);
		string key = getkey(id1);
		
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1,-1);
			graph[key]=n1;
			l.push_back(n1);
			cout<<"c1"<<endl;
		}
		else{
			//map wala dedo
			l.push_back(graph[key]);
			cout<<"c2"<<endl;
		}
	}
	if(col==2 or col==1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row][col-1]);
		string key = getkey(id1);
		cout<<"d"<<endl;
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1,-1);
			graph[key]=n1;
			l.push_back(n1);
		}
		else{
			//map wala dedo
			l.push_back(graph[key]);
		}
	}
	cout <<l.size() <<endl;
	cout<<l.front()->getid()<<endl;
	return l;
}


//h(n) function
float manhattan(Node< _8sq >* n){
	float cost = 0;
	_8sq ids = n->getid();

	pos_pair pos;
	for(int i=0;i<9;i++){
		pos_pair pos = find(ids, i+1);
		int row = pos.row;
		int col = pos.col;
		int man_row = (i)/3;
		int man_col = (i)%3;
		int temp = abs(man_row - row) + abs(man_col - col);
		//cout<< i+1 <<" error: "<< temp<<endl;
		cost+= temp;
	}

	//cout<< "cost is: " << cost<<endl;
	return cost;
}

//9 is the blank
int main(){
	_8sq ids = {{1,5,3},{9,2,6},{4,7,8}};

	_8sq idg = {{1,2,3},{4,5,6},{7,8,9}};
	
	//cout<<(idg==ids)<<endl;

	cout<<getkey(ids)<<endl;


	mynode* s = new mynode(ids,0);
	mynode* g = new mynode(idg,0);

	graph[getkey(ids)] = s;
	graph[getkey(idg)] = g;



	// list<mynode*> l1 = myneigh(s);
	// list<mynode*> l2 = myneigh(s);

	// cout<<(l1.front() == l2.front())<<endl;		//if pointer is same
	return 0;
	s->print_me();
	list<mynode*> l = myneigh(s);

	// list<mynode*>::iterator it = l.begin();
	// for(;it!=l.end();it++){
	// 	(*it)->print_me();
	// }

	cout<<"Start Node: "<<endl;
	cout<<ids;
	cout<<"End Node: "<<endl;
	cout<<idg;

	AStar<Node<_8sq > > algo(s,g,manhattan,myneigh);
	algo.run();

	return 0;
}
