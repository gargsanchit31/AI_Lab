#ifndef _LAYER
#define _LAYER

#include "components.h"

class layer;

class layer {
public:
	char type;					// I , H, O  are the allowed types
	char layer_id;				// this is the id of the layer
	int population;			// number of nodes in the layer
	int prev_population;	// population of previous layer
	int next_population;	// population of next layer
	Neuron * nodeList;		// array of nodes

	layer(char, char, int, int, int);		// constructor : type, layer_id, population, prev_population, next_layer
	~layer()

private:
	void addnode();
};


#endif