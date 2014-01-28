#ifndef _LAYER
#define _LAYER

#include <iostream>
#include <stdio.h>  
#include <cmath>
#include <vector>

#include "components.h"



class layer;

class layer {
private:
	char type;					// I , H, O  are the allowed types
	char layer_id;				// this is the id of the layer
	int population;				// number of nodes in the layer
	int prev_population;		// population of previous layer
	int next_population;		// population of next layer


public:
	vector<Neuron*> neuronList;				// array of nodes
	
	layer(char, char, int, int, int);		// constructor : type, layer_id, population, prev_population, next_layer
	~layer();
	char get_type();						//return type of neuron
	char get_layerid();						//returns the id of layer
	int get_population();					//returns the number of neurons in the layer
	int get_prev_population();				//returns the number of neurons in the previoous layer
	int get_next_population();				//returns the number of neurons in the next layer
	void addnode();							// adds nodes to the layer upon initialization
	void propogate_sig();					// propogates signal after 
	void propogate_err();					// propogates error
	void weight_update();					// updates teh weight of the lower layer neurons connected to it 	
};


#endif