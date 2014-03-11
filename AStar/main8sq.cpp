#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <time.h>
#include <unordered_map>
#include "bigraph.h"
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
    if(x >=4) x =4;
    return get_random(x);
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
    mygraphtype * graph1 = new mygraphtype();
    mygraphtype * graph2 = new mygraphtype();

    srand(time(NULL)); //seed _8sq
	// rand ids = {{1,4,7},{2,5,3},{8,6,0}};
	_8sq ids = {{1,4,5},{0,8,2},{7,3,6}};
	_8sq idg = {{1,2,3},{4,5,6},{7,8,0}};


	mynode* s1 = new mynode(ids);
	mynode* g1 = new mynode(idg);

	mynode* g2 = new mynode(ids);
	mynode* s2 = new mynode(idg);

	(*graph1)[getkey(ids)] = s1;
	(*graph1)[getkey(idg)] = g1;

	(*graph2)[getkey(ids)] = g2;
	(*graph2)[getkey(idg)] = s2;

    cout << "Starting with Bi-directional A-star" <<endl;

	cout<<"Start Node: "<<endl;
	cout<<ids;
	cout<<"End Nodes: "<<endl;
	cout<<idg;

	AStar<Node<_8sq > > algo1(s1,g1,rel_displace_cost,myneigh,graph1);
	AStar<Node<_8sq > > algo2(s2,g2,rel_displace_cost,myneigh,graph2);
	
	//int len = algo1.run();
    // cout << "Path found is of length " << len <<endl;
    // cout << "Size of graph discovered " << (*graph).size() <<endl;

    algo1.init();
    algo2.init();
    int count = 0;
    while(1){
		if((algo1.open_list_empty()) || (algo2.open_list_empty())){
			cout<<"Something went wrong. open_list can't be empty"<<endl;
            return -1; //path len is -1 (since no path could be found)
		}

		mynode* n1 = (mynode*)malloc(sizeof(mynode));
		mynode* n2 = (mynode*)malloc(sizeof(mynode));

		int len1 = algo1.step(n1);
		int len2 = algo2.step(n2);
		
		if(len1!=-1){
			cout<<"Algo1 found the path\n";
			break;
		}

		if(len2!=-1){
			cout<<"Algo2 found the path\n";
			break;
		}


		free(n1);
		free(n2);
		count++;
		if(count%1000==0){
			cout<<count<<endl<<"OL1 Size: " <<algo1.open_list_size()<<endl<<"OL2 Size" <<algo2.open_list_size()<<endl;
		}
	}
	return 0;
}


