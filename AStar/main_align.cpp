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

typedef unordered_map<string, mynode*> mygraphtype;

typedef struct{
	int row;
	int col;
} pos_pair;

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

list<myneighinfo > myneigh(mynode* n, mygraphtype &graph){
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
	return 1;
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

int main(){
	srand(time(NULL)); //seed rand
	mygraphtype * graph = new mygraphtype() ;

	ID ids = {'B','B','B',BLANK,'W','W','W'};
	ID idg1 = {'W','W','W','B','B','B',BLANK};
	ID idg2 = {'W','W','W','B','B',BLANK,'B'};
	ID idg3 = {'W','W','W','B',BLANK,'B','B'};
	ID idg4 = {'W','W','W',BLANK,'B','B','B'};
	ID idg5 = {'W','W',BLANK,'W','B','B','B'};
	ID idg6 = {'W',BLANK,'W','W','B','B','B'};
	ID idg7 = {BLANK,'W','W','W','B','B','B'};

	mynode* s = new mynode(ids);
	mynode* g1 = new mynode(idg1);
	mynode* g2 = new mynode(idg2);
	mynode* g3 = new mynode(idg3);
	mynode* g4 = new mynode(idg4);
	mynode* g5 = new mynode(idg5);
	mynode* g6 = new mynode(idg6);
	mynode* g7 = new mynode(idg7);

	(*graph)[getkey(ids)] = s;
	(*graph)[getkey(idg1)] = g1;
	(*graph)[getkey(idg2)] = g2;
	(*graph)[getkey(idg3)] = g3;
	(*graph)[getkey(idg4)] = g4;
	(*graph)[getkey(idg5)] = g5;
	(*graph)[getkey(idg6)] = g6;
	(*graph)[getkey(idg7)] = g7;

	goals.push_back(g1);
	goals.push_back(g2);
	goals.push_back(g3);
	goals.push_back(g4);
	goals.push_back(g5);
	goals.push_back(g6);
	goals.push_back(g7);


	int len;
input_heuristic:
	cout<<"Press 0 to exit: \n";
    cout<<"Press 1 for inversion heuristic: \n";
    cout<<"Press 2 for inversion2 heuristic: \n";
    cout<<"Press 3 for random_cost heuristic: \n";
    cout<<"Press 4 for greater_h heuristic: \n";
    cout<<"Press 5 for zero_cost heuristic: \n";
    cout<<"Enter your choice: ";
	cin>>len;
	float (*f)(mynode*);

	switch(len){
		case 0:
			cout<<"Exit\n";
			return 0;
		break;

		case 1:
			f=inversion;
		break;

		case 2:
			f=inversion2;
		break;

		case 3:
			f=random_cost;
		break;

		case 4: 
			f=greater_h;
		break;

		case 5:
			f=zero_cost;
		break;

		default:
			cout<<"Undesired Input\n";
			goto input_heuristic;
	}

	AStar<mynode> algo(s,goals,f,myneigh,graph);
	len = algo.run();
    cout << "Number of steps required " << len <<endl;
    cout << "Size of graph discovered " << (*graph).size() <<endl;
	return 0;
}
