#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "graph.h"
using namespace std;

typedef vector<vector<int> > _8sq;

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
    }
    //os << "\n";
    return os;
}

//neighbour function
list<Node< _8sq >* > myneigh(Node< _8sq >* n){
	list<Node< _8sq >*> l;


	_8sq id = {{1,2,3},{4,5,6},{7,8,9}};
	_8sq idg = {{1,2,3},{4,5,6},{7,8,9}};
	Node< _8sq >* s = new Node< _8sq >(idg,2);
	Node< _8sq >* g = new Node< _8sq >(id,2);
	l.push_back(s);
	l.push_back(g);
	

	return l;
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
	_8sq idg = {{1,2,3},{4,5,6},{7,8,9}};
	_8sq ids = {{1,2,8},{4,7,6},{5,3,9}};
	
	Node<_8sq >* s = new Node< _8sq >(ids,0);
	Node< _8sq >* g = new Node< _8sq >(idg,5);

	//manhattan(s);

	AStar<Node<_8sq > > algo(s,g,manhattan,myneigh);
	cout<<algo.getStart()->getid()<<endl;
	cout<<algo.f(s)<<endl;
	
	return 0;

}
