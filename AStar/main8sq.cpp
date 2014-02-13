#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <time.h>
#include <unordered_map>
#include "graph.h"
#include "utils.h"

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

list<mynode* > myneigh(mynode* n){
	list<mynode*> l;

	_8sq id = n->getid();
	pos_pair p = find(id, 0);

	int row=p.row;
	int col = p.col;

	if(row == 0 or row == 1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row+1][col]);
		string key = getkey(id1);
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1);
			graph[key]=n1;
			l.push_back(n1);
		}
		else{
			//map wala dedo
			l.push_back(graph[key]);
		}
	}
	if(row == 2 or row == 1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row-1][col]);
		string key = getkey(id1);
		
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1);
			graph[key]=n1;
			l.push_back(n1);
		}
		else{
			//map wala dedo
			l.push_back(graph[key]);
		}
	}
	if(col==0 or col==1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row][col+1]);
		string key = getkey(id1);
		
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1);
			graph[key]=n1;
			l.push_back(n1);
		}
		else{
			//map wala dedo
			l.push_back(graph[key]);
		}
	}
	if(col==2 or col==1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row][col-1]);
		string key = getkey(id1);
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1);
			graph[key]=n1;
			l.push_back(n1);
		}
		else{
			//map wala dedo
			l.push_back(graph[key]);
		}
	}
	return l;
}


//h(n) function
float manhattan(Node< _8sq >* n){
	float cost = 0;
	_8sq ids = n->getid();

	pos_pair pos;
	for(int i=0;i<8;i++){ //ERROR was here. We only need to consider manhattan displaced positions (i.e numbers 1 - 8)
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

float hamming(Node< _8sq >* n){
    float cost = 0;
	_8sq ids = n->getid();

	pos_pair pos;
	for(int i=0;i<8;i++){//ERROR was here. (see manhattan() for details)
		pos_pair pos = find(ids, i+1);
		int row = pos.row;
		int col = pos.col;
		int man_row = (i)/3;
		int man_col = (i)%3;
		int temp = abs(man_row - row) + abs(man_col - col);
		//cout<< i+1 <<" error: "<< temp<<endl;
		if(temp>0)cost+= 1;
	}
	//cout<< "cost is: " << cost<<endl;
	return cost;
}

float random_cost(mynode* n){
    float x = manhattan(n);
    if(x == 0) return 0;
    return get_random(x);
}

//0 is the blank
int main(){
    srand(time(NULL)); //seed rand
	_8sq ids = {{2,6,1},{0,3,8},{4,5,7}};

	_8sq idg = {{1,2,3},{4,5,6},{7,8,0}};
	
	//cout<<(idg==ids)<<endl;

	cout<<getkey(ids)<<endl;



	mynode* s = new mynode(ids);
	mynode* g = new mynode(idg);

	graph[getkey(ids)] = s;
	graph[getkey(idg)] = g;

    /*
    //check if graph is generated wholly
    int count = 0;
    list<mynode*> ln ;
    list<mynode*> G;
    s->cur_status = 0;
    G.push_back(s);
	list<mynode*>::iterator itn ;
    while(!G.empty()){
        mynode * n = G.front();
        G.pop_front();
        ln = myneigh(n);
        for(itn=ln.begin();itn!=ln.end();itn++){
            if((*itn)->cur_status != 0){
                count++;
                (*itn)->cur_status = 0;
                if(*itn == g) {
                    cout<<"found goal node" <<endl;
                    cout << "Final count of Test Graph " << count <<endl;
                }
                G.push_back((*itn));
            }
        }
    }

    cout << "Final count of Test Graph " << count <<endl;
    return 0;
    */

    

	list<mynode*> l1 = myneigh(s);
	list<mynode*> l2 = myneigh(s);

	cout<<(l1.front() == l2.front())<<endl;		//if pointer is same
	s->print_me();
	list<mynode*> l = myneigh(g);


    cout << "neigh " << endl;
	list<mynode*>::iterator it = l.begin();
	for(;it!=l.end();it++){
		(*it)->print_me();
	}

    cout << "Starting with A-star" <<endl;

	cout<<"Start Node: "<<endl;
	cout<<ids;
	cout<<"End Node: "<<endl;
	cout<<idg;

	AStar<Node<_8sq > > algo(s,g,random_cost,myneigh);
	int len = algo.run();
    cout << "Path found is of length " << len <<endl;
    cout << "Size of graph discovered " << graph.size() <<endl;

	return 0;
}
