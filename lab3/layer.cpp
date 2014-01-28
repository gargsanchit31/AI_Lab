#include "layer.h"

/** this is the constructor definition **/

layer::layer(char type, char id, int number, int prev_number, int next_number){    // type, layer_id, population, prev_population, next_layer
	type = type;
	layer_id = id;
	population = number;
	prev_population = prev_number;
	next_population = next_number;
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


