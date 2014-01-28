#include "neural_network.h"
#include "components.h"
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

//size= "#(layers)", layer_vec[i] = #(neurons) at layer i
neural_network::neural_network(int size, vector<int> layer_vec){
	int l_no=0;		//layer no.
	char l_id='A';		//layer id
	layer_count=size;
	
	//if more than one layer
	if(layer_count > 1){

		//first layer as input layer
		layer* l = new layer('I', l_id++, layer_vec[l_no], 1, layer_vec[l_no+1]);
		l_no++;		//increment the layer number
		layers.push_back(l);
	
		//hidden layer if number of layer is more than 2
		if(layer_count > 2){
			while(l_no < size - 1){
				l = new layer('H', l_id++, layer_vec[l_no], layer_vec[l_no - 1], layer_vec[l_no + 1]);
				l_no++;		//increment the layer number
				layers.push_back(l);
			}
		}

		//last layer as output layer
		l = new layer('O', l_id++, layer_vec[l_no], layer_vec[l_no - 1], 1);
		l_no++;		//increment the layer number
		layers.push_back(l);

		//create all the edges between the layers
		create_edges();
	}
}

neural_network::neural_network(){
	layer_count=0;
}

void neural_network::create_edges(){

	for(int cur_index=0; cur_index<layer_count; cur_index++){
		layer* cur_layer = layers[cur_index];
		vector<Neuron*> cur_layer_neurons = cur_layer->neuronList;

		//set input to the input layer. input vector is of size 1
		if(cur_index == 0){
			for(int j=0;j<cur_layer->get_population();j++){
				Edge* e = new Edge();
				cur_layer_neurons[j]->inputs[0] = e;
			}
		}
		
		/*for all layers connect kth output of the jth neuron in current layer
		 * to the jth input of the kth neuron in the next layer.
		 * and weights of edges are assigned arbitarily
		 */

		if(cur_index != layer_count-1){
			layer* next_layer = layers[cur_index+1];
			vector<Neuron*> next_layer_neurons = next_layer->neuronList;
			
			for(int j=0;j<cur_layer->get_population();j++){
				for(int k=0;k<next_layer->get_population();k++){
					Edge* e = new Edge();
					cur_layer_neurons[j]->outputs[k] = next_layer_neurons[k]->inputs[j] = e;
				}
			}
		}

		/* for the last layer (output) create one output edge for each node
		*/
		if(cur_index == layer_count-1){
			for(int j=0;j<cur_layer->get_population();j++){
				Edge* e = new Edge();
				cur_layer_neurons[j]->outputs[0] = e;
			}
		}
	}
}


void neural_network::print_topology(){
	for(int cur_index=0; cur_index<layer_count; cur_index++){
		layer* cur_layer = layers[cur_index];
		vector<Neuron*> cur_layer_neurons = cur_layer->neuronList;

		for(int j=0;j<cur_layer->get_population();j++){
			cout<<(cur_layer_neurons[j]->inputs).size()<<"	";
		}
		cout<<endl;

		for(int j=0;j<cur_layer->get_population();j++){
			neuron_id id = cur_layer_neurons[j]->get_id();
			cout<<id.layer_id<<id.seq_no<<"	";
		}
		cout<<endl;

		for(int j=0;j<cur_layer->get_population();j++){
			cout<<(cur_layer_neurons[j]->outputs).size()<<"	";
		}
		cout<<endl;
	}
}
