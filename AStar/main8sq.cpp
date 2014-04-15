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
float manhattan(mynode* n, mynode* g){
	float cost = 0;
	_8sq ids = n->getid();
	_8sq idg = g->getid();

	pos_pair pos;
	for(int i=0;i<8;i++){
		pos_pair pos = find(ids, i+1);
		pos_pair posg = find(idg, i+1);
		cost += abs(pos.row - posg.row) + abs(pos.col - posg.col);
	}
	return cost;
}

float hamming(mynode* n,mynode* g){
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

float random_cost(mynode* n, mynode* g){
    float x = manhattan(n,g);
    if(x == 0) return 0;
    return get_random(x);
}

float random_cost_2(mynode* n, mynode* g){
    float x = manhattan(n,g);
    if(x == 0) return 0;
    if(x >=4) x =4;
    return get_random(x);
}

float rel_displace_cost(mynode* n, mynode* g){
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
	_8sq ids = {{2,8,1},{4,0,7},{5,3,6}};
	_8sq idg = {{1,2,3},{4,5,6},{7,8,0}};



	mynode* s1 = new mynode(ids);
	mynode* g1 = new mynode(idg);

	cout<<"costs are: "<<manhattan(s1,g1)<<" "<<manhattan(g1,s1);
	//return 0;

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
	float (*f)(mynode*,mynode*);

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




	AStar<Node<_8sq > > algo1(s1,g1,f,myneigh,graph1);
	AStar<Node<_8sq > > algo2(s2,g2,f,myneigh,graph2);

    algo1.init();
    algo2.init();
    int count = 0;
    while(1){
		if((algo1.open_list_empty()) || (algo2.open_list_empty())){
			cout<<"Something went wrong. open_list can't be empty"<<endl;
            return -1;
		}

		mynode *n1, *n2;

		int len1 = algo1.step(n1);
		
		if(len1!=-1){
			cout<<"Algo1 found the path\n";
			break;
		}
		count++;
		
		int len2 = algo2.step(n2);
		if(len2!=-1){
			cout<<"Algo2 found the path\n";
			break;
		}
		count++;

		string key1 = getkey(n1->getid());
		
		string key2 = getkey(n2->getid());

		if(graph1->find(key2) != graph1->end()){
			mynode* n = (*graph1)[key2];
			if(n->cur_status == 1){
				algo2.trace(n2);
				algo1.trace(n);
				break;
			}
		}

		if(graph2->find(key1) != graph2->end()){
			mynode* n = (*graph2)[key1];
			if(n->cur_status == 1){
				algo2.trace(n);
				algo1.trace(n1);
				break;
			}
		}

		count++;
		if(count%1000==0){
			cout<<count<<endl<<"OL1 Size: " <<algo1.open_list_size()<<endl<<"OL2 Size" <<algo2.open_list_size()<<endl;
		}
	}
	int elem = 0;
	cout << "Number of steps required " << count <<endl;
	cout<<"size of graph1: "<<graph1->size()<<endl;
	cout<<"size of graph2: "<<graph2->size()<<endl;
	
	mygraphtype::iterator it = graph2->begin();

	for(;it!=graph2->end();it++){
		string key = getkey(((*it).second)->getid());
		if(graph1->find(key) != graph1->end()){
			continue;
		}
		++elem;
	}

	cout<<"total graph explored: "<<graph1->size() + elem << endl;

	return 0;
}


