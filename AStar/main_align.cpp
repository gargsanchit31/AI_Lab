#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <time.h>
#include <unordered_map>
#include "graph.h"
#include "utils.h"

#define BLANK '#'

using namespace std;

typedef vector<char> ID;			// '#' means blank, 'B' mean B, 'W' mean W
typedef Node<ID> mynode;
typedef NeighInfo<mynode> myneighinfo;

typedef struct{
	int row;
	int col;
} pos_pair;

unordered_map<string, mynode*> graph;
list<mynode*> goals;

//overload the << operator for printing vector
ostream& operator<<(ostream& os, const ID v)
{
     for(int i=0;i<v.size();++i){
     	os << v[i] << " ";
    }
    os << "\n";
    return os;
}

bool operator==(const ID& v1, const ID& v2){
 	for(int j=0;j<v1.size();++j){
 		if(v1[j]!=v2[j]){
 			return false;
 		}
	}
    return true;
}

void swap(char &a, char &b){
	char temp=a;
	a=b;
	b=temp;
}

string getkey(ID v){
	string key(v.begin(),v.end());
	return key;
}

vector<int> find_blank(ID id){
	vector<int> res;
	ID::iterator it = id.begin();
	int i=0;
	for(;it != id.end();it++){
		if(*it == BLANK){
			res.push_back(i);
		}
		++i;
	}
	return res;
}

list<myneighinfo > myneigh(mynode* n){
	list<myneighinfo> l;
	ID id = n->getid();
	vector<int> blank = find_blank(id);
	for(int i=0; i<blank.size();++i){
		int bi = blank[i];	//blank place
		// cout<<"blank at "<<bi<<endl;
		if(bi+1 < id.size() and id[bi+1] != BLANK){
			ID id1 = id;
			swap(id1[bi], id1[bi+1]);
			// cout<<"swap at "<<bi+1<<" "<<id1<<endl;

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

			
			if(bi+2 < id.size() and id[bi+2] != BLANK){
				id1 = id;
				swap(id1[bi], id1[bi+2]);
				// cout<<"swap at "<<bi+2<<" "<<id1<<endl;

				string key = getkey(id1);
				if(graph.find(key) == graph.end()){
					mynode* n1 = new mynode(id1);
					graph[key]=n1;
					
					myneighinfo info;
			        info.node = n1;
			        info.edge_cost = 2;
					l.push_back(info);
				}
				else{
					//map wala dedo
					myneighinfo info;
		            info.node = graph[key];
		            info.edge_cost = 2;
					l.push_back(info);
				}
			}
		}
		if(bi-1 >= 0 and id[bi-1] != BLANK){
			ID id1 = id;
			swap(id1[bi], id1[bi-1]);
			// cout<<"swap at "<<bi-1<<" "<<id1<<endl;

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

			if(bi-2 >= 0 and id[bi-2] != BLANK){
				id1 = id;
				swap(id1[bi], id1[bi-2]);
				// cout<<"swap at "<<bi-2<<" "<<id1<<endl;

				string key = getkey(id1);
				if(graph.find(key) == graph.end()){
					mynode* n1 = new mynode(id1);
					graph[key]=n1;
					
					myneighinfo info;
			        info.node = n1;
			        info.edge_cost = 2;
					l.push_back(info);
				}
				else{
					//map wala dedo
					myneighinfo info;
		            info.node = graph[key];
		            info.edge_cost = 2;
					l.push_back(info);
				}
			}
		}
	}
	return l;
}

float cost_1(mynode* n){
	return 7;
}

//here manhattan is number of inverted pair
float inversion(mynode* n){
	ID id = n->getid();
	float inv =0;
	for(int i=0;i<id.size();++i){
		if(id[i]=='B'){
			for(int j=i+1;j<id.size();++j){
				if(id[j]=='W'){
					++inv;
				}
			}
		}
	}
	return inv;
}

float inversion2(mynode* n){
	float x = inversion(n);
	if(x>0) return x-1;
	return x;
}

// //h(n) function
// float manhattan(Node< _8sq >* n){
// 	float cost = 0;
// 	_8sq ids = n->getid();

// 	pos_pair pos;
// 	for(int i=0;i<8;i++){ //ERROR was here. We only need to consider manhattan displaced positions (i.e numbers 1 - 8)
// 		pos_pair pos = find(ids, i+1);
// 		int row = pos.row;
// 		int col = pos.col;
// 		int man_row = (i)/3;
// 		int man_col = (i)%3;
// 		int temp = abs(man_row - row) + abs(man_col - col);
// 		//cout<< i+1 <<" error: "<< temp<<endl;
// 		cost+= temp;
// 	}
// 	//cout<< "cost is: " << cost<<endl;
// 	return cost;
// }

// float hamming(mynode* n){
//     float cost = 0;
// 	_8sq ids = n->getid();

// 	pos_pair pos;
// 	for(int i=0;i<8;i++){//ERROR was here. (see manhattan() for details)
// 		pos_pair pos = find(ids, i+1);
// 		int row = pos.row;
// 		int col = pos.col;
// 		int man_row = (i)/3;
// 		int man_col = (i)%3;
// 		int temp = abs(man_row - row) + abs(man_col - col);
// 		//cout<< i+1 <<" error: "<< temp<<endl;
// 		if(temp>0)cost+= 1;
// 	}
// 	//cout<< "cost is: " << cost<<endl;
// 	return cost;
// }

float random_cost(mynode* n){
    float x = inversion(n);
    if(x == 0) return 0;
    return get_random(x);
}

float greater_h(mynode* n){
    float x = inversion(n);
    if(x == 0) return 0;
    return x + get_random(x) + 2;
}

float zero_cost(mynode* n){
	return 0;
}

// float random_cost_2(mynode* n){
//     float x = manhattan(n);
//     if(x == 0) return 0;
//     if(x >=4) x =4;
//     return get_random(x);
// }
//0 is the blank
int main(){
	srand(time(NULL)); //seed rand

	ID ids = {'B','B','B',BLANK,'W','W','W'};
	ID idg1 = {'W','W','W','B','B','B',BLANK};
	ID idg2 = {'W','W','W','B','B',BLANK,'B'};
	ID idg3 = {'W','W','W','B',BLANK,'B','B'};
	ID idg4 = {'W','W','W',BLANK,'B','B','B'};
	ID idg5 = {'W','W',BLANK,'W','B','B','B'};
	ID idg6 = {'W',BLANK,'W','W','B','B','B'};
	ID idg7 = {BLANK,'W','W','W','B','B','B'};
	// cout<<ids<<endl;
	// swap(ids[6],ids[4]);
	// cout<<ids;
	// return 0;
	// vector<int> blank = find_blank(ids);
	// return 0;
	// for(int i=0;i<blank.size();++i){
	// 	cout<<blank[i]<<" ";
	// }
	// cout<<endl;

	// mynode* s = new mynode(ids);
	// list<mynode*> l = myneigh(s);

 //    srand(time(NULL)); //seed rand
	// _8sq ids = {{3,1,2},{0,6,8},{4,5,7}};

	// _8sq idg1 = {{1,2,3},{4,5,6},{7,8,0}};
	// _8sq idg2 = {{2,1,3},{4,5,6},{7,8,0}};
	
	// //cout<<(idg==ids)<<endl;

	// cout<<getkey(ids)<<endl;



	mynode* s = new mynode(ids);
	
	mynode* g1 = new mynode(idg1);
	mynode* g2 = new mynode(idg2);
	mynode* g3 = new mynode(idg3);
	mynode* g4 = new mynode(idg4);
	mynode* g5 = new mynode(idg5);
	mynode* g6 = new mynode(idg6);
	mynode* g7 = new mynode(idg7);

	// cout<<manhattan(s)<<endl;
	// return 0;

	graph[getkey(ids)] = s;
	
	graph[getkey(idg1)] = g1;
	graph[getkey(idg2)] = g2;
	graph[getkey(idg3)] = g3;
	graph[getkey(idg4)] = g4;
	graph[getkey(idg5)] = g5;
	graph[getkey(idg6)] = g6;
	graph[getkey(idg7)] = g7;

	goals.push_back(g1);
	goals.push_back(g2);
	goals.push_back(g3);
	goals.push_back(g4);
	goals.push_back(g5);
	goals.push_back(g6);
	goals.push_back(g7);
	// graph[getkey(idg2)] = g2;

 //    list<mynode*> goals;
	// goals.push_back(g1);
	// goals.push_back(g2);

	// list<mynode*> l1 = myneigh(s);
	// list<mynode*> l2 = myneigh(s);

	// cout<<(l1.front() == l2.front())<<endl;		//if pointer is same
	// s->print_me();
	// list<mynode*> l = myneigh(s);

 //    cout << "neigh " << endl;
	// list<mynode*>::iterator it = l.begin();
	// for(;it!=l.end();it++){
	// 	(*it)->print_me();
	// }

 //    cout << "Starting with A-star" <<endl;

	// cout<<"Start Node: "<<endl;
	// cout<<ids;
	// cout<<"End Node: "<<endl;
	// cout<<idg1;
	// cout<<idg2;

	AStar<mynode> algo(s,goals,inversion2,myneigh);
	int len = algo.run();
    cout << "Path found is of length " << len <<endl;
    cout << "Size of graph discovered " << graph.size() <<endl;
	return 0;
}
