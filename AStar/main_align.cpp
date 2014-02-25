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

typedef struct{
	int row;
	int col;
} pos_pair;

unordered_map<string, mynode*> graph;

vector<int> find_blank(ID);
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

list<mynode* > myneigh(mynode* n){
	list<mynode*> l;
	ID id = n->getid();
	vector<int> blank = find_blank(id);
	for(int i=0; i<blank.size();++i){
		int bi = blank[i];	//blank place
		cout<<"blank at "<<bi<<endl;
		if(bi+1 < id.size() and id[bi+1] != BLANK){
			ID id1 = id;
			swap(id1[bi], id1[bi+1]);
			cout<<"swap at "<<bi+1<<" "<<id1<<endl;

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

			
			if(bi+2 < id.size() and id[bi+2] != BLANK){
				id1 = id;
				swap(id1[bi], id1[bi+2]);
				cout<<"swap at "<<bi+2<<" "<<id1<<endl;

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
		}
		if(bi-1 >= 0 and id[bi-1] != BLANK){
			ID id1 = id;
			swap(id1[bi], id1[bi-1]);
			cout<<"swap at "<<bi-1<<" "<<id1<<endl;

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

			if(bi-2 >= 0 and id[bi-2] != BLANK){
				id1 = id;
				swap(id1[bi], id1[bi-2]);
				cout<<"swap at "<<bi-2<<" "<<id1<<endl;

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
		}
	}
	return l;
}

float cost_1(mynode* n){
	return 1;
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

// float random_cost(mynode* n){
//     float x = manhattan(n);
//     if(x == 0) return 0;
//     return get_random(x);
// }

// float random_cost_2(mynode* n){
//     float x = manhattan(n);
//     if(x == 0) return 0;
//     if(x >=4) x =4;
//     return get_random(x);
// }
//0 is the blank
int main(){
	ID ids = {'B','B','B','#','W','W','W'};
	ID idg = {'W','W','W','B','B','B','#'};
	cout<<ids<<endl;
	// swap(ids[6],ids[4]);
	// cout<<ids;
	// return 0;
	vector<int> blank = find_blank(ids);
	// return 0;
	for(int i=0;i<blank.size();++i){
		cout<<blank[i]<<" ";
	}
	cout<<endl;

	// mynode* s = new mynode(ids);
	// list<mynode*> l = myneigh(s);

 //    srand(time(NULL)); //seed rand
	// _8sq ids = {{3,1,2},{0,6,8},{4,5,7}};

	// _8sq idg1 = {{1,2,3},{4,5,6},{7,8,0}};
	// _8sq idg2 = {{2,1,3},{4,5,6},{7,8,0}};
	
	// //cout<<(idg==ids)<<endl;

	// cout<<getkey(ids)<<endl;



	mynode* s = new mynode(ids);
	
	mynode* g1 = new mynode(idg);
	// mynode* g2 = new mynode(idg2);

	graph[getkey(ids)] = s;
	
	graph[getkey(idg)] = g1;
	list<mynode*> goals;
	goals.push_back(g1);
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

	AStar<mynode> algo(s,goals,cost_1,myneigh);
	int len = algo.run();
    cout << "Path found is of length " << len <<endl;
    cout << "Size of graph discovered " << graph.size() <<endl;
	return 0;
}
