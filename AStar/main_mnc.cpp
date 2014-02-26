#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <time.h>
#include <unordered_map>
#include "graph.h"
#include "utils.h"

using namespace std;

typedef struct{
	int missionaries;	//number of missionaries on left bank
	int cannibles;		//number of cannibles on left bank
	bool position;		//position of boat	"true" = on the left & "false" = on the right
} ID;

typedef struct{
	int m_move;
	int c_move;
} mnc_move;

typedef Node<ID> mynode;
typedef list<mynode* > node_list;
typedef node_list::iterator node_it;
typedef NeighInfo<mynode> myneighinfo;

unordered_map<string, mynode*> graph;
vector<mnc_move> move_list = {{1,0},{0,1},{2,0},{0,2},{1,1}};
mynode* s;
mynode* g;

ostream& operator<<(ostream& os, const ID id){
	os << id.missionaries << " " << id.cannibles << " " << id.position << "\n";
    return os;
}

bool operator==(const ID& id1, const ID id2)
{
     return (id1.missionaries==id2.missionaries and id1.cannibles == id2.cannibles and id1.position == id2.position );
}

void print_list(node_list l){
	for(node_list::iterator it = l.begin();it!=l.end();it++){
		cout<<(*it)->getid();
	}
}

string getkey(ID id){
	string key= "";
	key+= to_string(id.missionaries);
	key+= to_string(id.cannibles);
	key+= to_string(id.position);
	return key;
}

bool isvalid(ID id){
	if(id.missionaries < 0 or id.cannibles < 0){
		return false;
	}
	else if(id.missionaries%3==0){
		return true;
	}
	else if(id.missionaries==id.cannibles){
		return true;
	}
	return false;
}

list<myneighinfo> myneigh(mynode* n){
	int factor = 1;
	list<myneighinfo> l;
	if(n->getid().position){
		factor=-1;
	}
	ID oldid = n->getid();
	oldid.position = !oldid.position;
	
	for(int i=0;i<move_list.size();++i){
		ID newid = oldid;
		newid.missionaries += factor*move_list[i].m_move;
		newid.cannibles += factor*move_list[i].c_move;
		string key = getkey(newid);
		if(!isvalid(newid)) continue;
		if(graph.find(key) == graph.end()){
			mynode* n1 = new mynode(newid);
			graph[key]=n1;
			
			myneighinfo info;
            info.node = n1;
            info.edge_cost = 1;
			l.push_back(info);
		}
		else{
			myneighinfo info;
            info.node = graph[key];
            info.edge_cost = 1;
			l.push_back(info);
		}
	}
	return l;
}

float cost(mynode* n){
	ID id = n->getid();
	return (id.cannibles + id.missionaries + !id.position)/(float)2;
}

float zero_cost(mynode* n){
	return 0;
}

int main(){
	ID ids = {3,3,1};
	ID idg = {0,0,0};
	s = new mynode(ids);
	g = new mynode(idg);
	graph[getkey(ids)] = s;
	graph[getkey(idg)] = g;

    list<mynode*> goals;
    goals.push_back(g);

	//cout<<cost(s);

//	node_list l = myneigh(s);

	AStar<mynode> algo(s,goals,zero_cost,myneigh);
	int len = algo.run();
    cout << "Path found is of length " << len <<endl;
    cout << "Size of graph discovered " << graph.size() <<endl;
	return 0;
}
