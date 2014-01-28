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
	float tolerance;	//% error which can be accepted
	float Threshold;
	void create_edges();
//methods
public:
	neural_network();
	neural_network(int, vector<int>, float thresh=0.1);
	~neural_network();

	void fwd_propogate();
	void back_propogate();
	void print_topology();
	void weight_update();
	int training_step(vector<float>, vector<float>);
	void set_input(vector<float>);
	int calculate_err(vector<float>);
};


#endif