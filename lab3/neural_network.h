#ifndef _NEURAL_NETWORK
#define _NEURAL_NETWORK

#include <vector>
#include "layer.h"
#include "components.h"
#include "utils.h"

using namespace std;

class neural_network;

class neural_network{
private:
	vector<layer * > layers;
	int layer_count;	//number of layers in neural network

	void create_edges();
//methods
public:
	neural_network();
	neural_network(int, vector<int>);
	~neural_network();

	void fwd_propogate();
	void back_propogate();
	void print_topology();


};


#endif