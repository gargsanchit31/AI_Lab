#ifndef _NEURAL_NETWORK
#define _NEURAL_NETWORK

#include <vector>
#include "layer.h"
#include "components.h"
#include "utils.h"

using namespace std;

class neural_network;

typedef struct {
	vector<double> input;
	vector<double> target;
} training_data;

class neural_network{
private:
	vector<layer * > layers;
	int layer_count;	//number of layers in neural network
	double tolerance;	//% error which can be accepted
	double Threshold;
	void create_edges();
	//vector<double> get_output();
//methods
public:
	neural_network();
	neural_network(int, vector<int>, double thresh=0.1);
	~neural_network();

	void fwd_propogate();
	void back_propogate();
	void print_topology();
	void print_network();
	void weight_update();
	int training_step(vector<training_data>);
	void set_input(vector<double>);
	double calculate_err(vector<double>);			//returns the diatance between output layer vector and vector
	vector<double> calculate_output(vector<double>);
};


#endif
