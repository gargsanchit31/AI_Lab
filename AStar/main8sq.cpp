#include <iostream>
#include <list>
#include <vector>
#include "graph.h"
using namespace std;

typedef vector<vector<int> > _8sq;
typedef Node<_8sq> mynode;

typedef struct{
	int row;
	int col;
} pos_pair;

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
list<Node< _8sq >* > myneigh(Node< _8sq >* n){
	list<Node< _8sq >*> l;

	_8sq id = n->getid();
	pos_pair p = find(id, 9);
	int row=p.row;
	int col = p.col;
	if(row == 0 or row == 1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row+1][col]);
		Node<_8sq>* n1 = new Node<_8sq>(id1,-1);
		l.push_back(n1);
	}
	if(row == 2 or row == 1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row-1][col]);
		Node<_8sq>* n1 = new Node<_8sq>(id1,-1);
		l.push_back(n1);
	}
	if(col==0 or col==1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row][col+1]);
		Node<_8sq>* n1 = new Node<_8sq>(id1,-1);
		l.push_back(n1);
	}
	if(col==2 or col==1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row][col-1]);
		Node<_8sq>* n1 = new Node<_8sq>(id1,-1);
		l.push_back(n1);
	}

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

	Node<_8sq >* s = new Node< _8sq >(ids,0);
	Node< _8sq >* g = new Node< _8sq >(idg,0);

	//manhattan(s);
	s->print_me();
	list<mynode*> l = myneigh(s);

	list<mynode*>::iterator it = l.begin();
	// for(;it!=l.end();it++){
	// 	(*it)->print_me();
	// }

	cout<<"Start Node: "<<endl;
	cout<<ids;
	cout<<"End Node: "<<endl;
	cout<<idg;

	AStar<Node<_8sq > > algo(s,g,manhattan,myneigh);
	//cout<<algo.getStart()->getid()<<endl;
	//cout<<algo.f(s)<<endl;
	algo.run();
	return 0;

}
