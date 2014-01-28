#include "layer.h"

/** this is the constructor definition **/

layer::layer(int depth, int nodecount){
	index = depth;
	population = nodecount;
}

/** this function add nodes to the layer **/

void layer::addnodes(){
	nodes = new Neuron[population];

	for (int i = 0; i < population ; i ++){
		
	}
}