#include "A_Star.h"


void A_Star::propogate(){
	list<Node *>::iterator it;
	it = open_list.begin();
	list<Node* > neighbours;
	neighbours.assign(give_neighbours(it).begin(),give_neighbours(it).end());
	list<Node *>::iterator neighbour_it;
	for (neighbour_it = neighbours.begin();neighbour_it != neighbours.end(); neighbour_it++){

	}
}



void A_Star::update_in_cl(Node updatenode, int g_val){
	list<Node *>::iterator it;
	it = closed_list.begin();
	Node* return_node = NULL;
	while(it != closed_list.end()){
		if (it == updatenode){
			it->g_value = it->g_value > g_val ? it->g_value : g_val;
			return;
		}
		it++;
	}
	Node* insert_node = new Node();


	return;
}