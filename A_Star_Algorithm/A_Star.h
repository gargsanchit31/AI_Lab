#include <iostream>

using namespace std;

class A_Star;

class A_Star{
public:
	A_Star();
	~A_Star();

	Node* start_node;
	Node* goal_node;

	list<Node* > open_list;
	list<Node* > closed_list;

	void propogate();
	list<Node* > give_neighbours(Node* );
	void insert_into_ol(Node* );
	void delete_from_ol(Node* );
	void insert_into_cl(Node* );
	void delete_from_cl(Node* );
	void update_cl();
	void update_in_cl(Node* );
};