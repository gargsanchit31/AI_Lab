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
typedef NeighInfo<mynode> myneighinfo;
typedef unordered_map<string, mynode*> mygraphtype;

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

list<myneighinfo> myneigh(mynode* n, mygraphtype &graph){
	list<myneighinfo> l;

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

            myneighinfo info;
            info.node = n1;
            info.edge_cost = 1;
			l.push_back(info);
		}
		else{
			//map wala dedo
            myneighinfo info;
            info.node = graph[key];
            info.edge_cost = 1;
			l.push_back(info);
		}
	}
	if(row == 2 or row == 1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row-1][col]);
		string key = getkey(id1);
		
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1);
			graph[key]=n1;

            myneighinfo info;
            info.node = n1;
            info.edge_cost = 1;
			l.push_back(info);
		}
		else{
			//map wala dedo
            myneighinfo info;
            info.node = graph[key];
            info.edge_cost = 1;
			l.push_back(info);
		}
	}
	if(col==0 or col==1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row][col+1]);
		string key = getkey(id1);
		
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1);
			graph[key]=n1;

            myneighinfo info;
            info.node = n1;
            info.edge_cost = 1;
			l.push_back(info);
		}
		else{
			//map wala dedo
            myneighinfo info;
            info.node = graph[key];
            info.edge_cost = 1;
			l.push_back(info);
		}
	}
	if(col==2 or col==1){
		_8sq id1 = id;
		swap(id1[row][col], id1[row][col-1]);
		string key = getkey(id1);
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(id1);
			graph[key]=n1;

            myneighinfo info;
            info.node = n1;
            info.edge_cost = 1;
			l.push_back(info);
		}
		else{
			//map wala dedo
            myneighinfo info;
            info.node = graph[key];
            info.edge_cost = 1;
			l.push_back(info);
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

float random_cost_2(mynode* n){
    float x = manhattan(n);
    if(x == 0) return 0;
    return x * (get_random(x) + 2)		;
}

float rel_displace_cost(mynode* n){
	pos_pair node[8];
	_8sq id = n->getid();
	float cost=0;
	for(int i=0;i<8;i++){
		node[i]=find(id, i+1);
	}
	for(int i=0;i<8;i++){
		float temp=0;
		switch(i){
			case 0:
				if((node[1].col - node[0].col) != 1){
					temp+=1;
				}
				if((node[3].row - node[0].row) != 1){
					temp+=1;
				}
				cost += temp/2;
			break;

			case 1:
				if((node[1].col - node[0].col) != 1){
					temp+=1;
				}
				if((node[4].row - node[1].row) != 1){
					temp+=1;
				}
				if((node[2].col - node[1].col) != 1){
					temp+=1;
				}
				cost += temp/3;
			break;

			case 2:
				if((node[2].col - node[1].col) != 1){
					temp+=1;
				}
				if((node[5].row - node[2].row) != 1){
					temp+=1;
				}
				cost += temp/2;
			break;

			case 3:
				if((node[3].row - node[0].row) != 1){
					temp+=1;
				}
				if((node[4].col - node[3].col) != 1){
					temp+=1;
				}
				if((node[6].row - node[3].row) != 1){
					temp+=1;
				}
				cost += temp/3;
			break;

			case 4:
				if((node[4].row - node[1].row) != 1){
					temp+=1;
				}
				if((node[4].col - node[3].col) != 1){
					temp+=1;
				}
				if((node[7].row - node[4].row) != 1){
					temp+=1;
				}
				if((node[5].col - node[4].col) != 1){
					temp+=1;
				}
				cost += temp/4;
			break;

			case 5:
				if((node[5].row - node[2].row) != 1){
					temp+=1;
				}
				if((node[5].col - node[4].col) != 1){
					temp+=1;
				}
				cost += temp/2;
			break;

			case 6:
				if((node[7].col - node[6].col) != 1){
					temp+=1;
				}
				if((node[6].row - node[3].row) != 1){
					temp+=1;
				}
				cost += temp/2;
			break;

			case 7:
				if((node[7].col - node[6].col) != 1){
					temp+=1;
				}
				if((node[7].row - node[4].row) != 1){
					temp+=1;
				}
				cost += temp/2;
			break;			
		}
	}
	return cost/2;
}

//0 is the blank
int main(){
    mygraphtype * graph = new mygraphtype() ;

    srand(time(NULL)); //seed _8sq

	_8sq ids = {{1,4,5},{0,8,2},{7,3,6}};
	_8sq idg1 = {{1,2,3},{4,5,6},{7,8,0}};

	mynode* s = new mynode(ids);
	mynode* g1 = new mynode(idg1);

	(*graph)[getkey(ids)] = s;
	(*graph)[getkey(idg1)] = g1;

    list<mynode*> goals;
	goals.push_back(g1);

    cout << "Starting with A-star" <<endl;
	cout<<"Start Node: "<<endl;
	cout<<ids;

	int len;
input_heuristic:
	cout<<"Press 0 to exit: \n";
    cout<<"Press 1 for manhattan heuristic: \n";
    cout<<"Press 2 for hamming heuristic: \n";
    cout<<"Press 3 for random_cost heuristic: \n";
    cout<<"Press 4 for rel_displace_cost heuristic: \n";
    cout<<"Press 5 for random_cost_2 heuristic: \n";
    cout<<"Enter your choice: ";
	cin>>len;
	float (*f)(mynode*);

	switch(len){
		case 0:
			cout<<"Exit\n";
			return 0;
		break;

		case 1:
			f=manhattan;
		break;

		case 2:
			f=hamming;
		break;

		case 3:
			f=random_cost;
		break;

		case 4: 
			f=rel_displace_cost;
		break;

		case 5:
			f=random_cost_2;
		break;

		default:
			cout<<"Undesired Input\n";
			goto input_heuristic;
	}
	AStar<Node<_8sq > > algo(s,goals,f,myneigh,graph);
	len = algo.run();
    cout << "Number of steps required " << len <<endl;
    cout << "Size of graph discovered " << (*graph).size() <<endl;

	return 0;
}


