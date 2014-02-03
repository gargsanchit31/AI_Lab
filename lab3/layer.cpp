#include "layer.h"
#include <algorithm>    // std::max

/** this is the constructor definition **/

layer::layer(char t, char id, int number, int prev_number, int next_number){    // type, layer_id, population, prev_population, next_layer
	type = t;
	layer_id = id;
	population = number;
	prev_population = prev_number;
	next_population = next_number;
	addnode();
}

/** 
	* 	this function add nodes to the layer 
	* 	Neuron(char n_type, neuron_id nid, int in_size, int out_size);
**/

void layer::addnode(){
	neuronList.resize(population);

	for (int i = 0; i < population ; i ++){
		neuron_id nid;
		nid.layer_id = layer_id;
		nid.seq_no = i;
		Neuron* node = new Neuron(type, nid, prev_population, next_population);
		neuronList[i] = node;						
	}
}

/**
	*	this function propogates the signal to the upper layer after doing necessary calculation 
**/

void layer::propogate_sig(){
	for (int i = 0; i < population; i++){
		neuronList[i]->propogate_signal();
	}
}

/**
	*	this function propogates the error from the upper layer to the lower layer after doing necessary calculation 
**/

void layer::propogate_err(){
	for (int i = 0; i < population; i++){
		neuronList[i]->propogate_error();
	}
}


/**
	*	this function updates the weights after doing necessary calculation 
**/

void layer::weight_update(){
	for (int i = 0; i < population; i++){
		neuronList[i]->update_weights();
	}
}

void layer::print_layer(){
	cout << "Layer :" << layer_id <<endl;
	cout << "\t\t";
	for(int i=0;i<population;i++){
		Neuron *nn = neuronList[i];
		//print o/p weights
		for(int j=0; j< nn->outputs.size(); j++){
			printf("%-7.3f", nn->outputs[j]->get_weight());
		}
        cout << " | ";
	}
	cout <<endl;
	cout << "\t\t";
	for(int i=0;i<population;i++){
		Neuron *nn = neuronList[i];
		int x = max(nn->outputs.size(),nn->inputs.size());
		cout << "o/p " <<nn->get_signal_output();
		for(int i=0; i< x ; i++){
			printf("      ");
		}
	}
	cout <<endl;
	cout << "\t\t";
	for(int i=0;i<population;i++){
		Neuron *nn = neuronList[i];
		int x = max(nn->outputs.size(),nn->inputs.size());
		cout << "DELTA: " <<nn->get_delta_error();
		for(int i=0; i< x ; i++){
			printf("      ");
		}
	}
	cout <<endl;
	cout << "\t\t";
	for(int i=0;i<population;i++){
		Neuron *nn = neuronList[i];
		int x = max(nn->outputs.size(),nn->inputs.size());
		cout << "#"<< nn->get_id().seq_no;
		for(int i=0; i< x ; i++){
			printf("      ");
		}
	}
	cout <<endl;	
	
	cout << "\t\t";	
	for(int i=0;i<population;i++){
		Neuron *nn = neuronList[i];
		//print input weights
		for(int j=0; j< nn->inputs.size(); j++){
			printf("%-7.3f", nn->inputs[j]->get_weight());
		}
        cout << " | ";
	}
	cout << endl <<endl;
}

char layer::get_type(){
	return type;
}

char layer::get_layerid(){
	return layer_id;
}

int layer::get_population(){
	return population;
}

int layer::get_prev_population(){
	return prev_population;
}

int layer::get_next_population(){
	return next_population;
}
