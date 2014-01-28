#include "neural_network.h"
#include "components.h"
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

//size= "#(layers)", layer_vec[i] = #(neurons) at layer i
neural_network::neural_network(int size, vector<int> layer_vec, float thresh){
	int l_no=0;		//layer no.
	char l_id='A';		//layer id
	layer_count=size;
	Threshold=thresh;
	
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
	Threshold=0.1;
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

void neural_network::fwd_propogate(){
	for(int i=0;i<layers.size();i++){
		layers[i]->propogate_sig();
	}
}

void neural_network::back_propogate(){
	for(int i=layers.size()-1 ; i>=0 ; i--){
		layers[i]->propogate_err();
	}
}

void neural_network::weight_update(){
	for(int i=0;i<layers.size();i++){
		layers[i]->weight_update();
	}
}

void neural_network::set_input(vector<float> input){
	layer* cur_layer = layers[0];
	vector<Neuron*> cur_layer_neurons = cur_layer->neuronList;
	
	for(int i=0;i<cur_layer_neurons.size();i++){
		cur_layer_neurons[i]->inputs[0]->set_signal(input[i]);
	}
}

int neural_network::calculate_err(vector<float> z){
	vector<float> y;
	layer* cur_layer = layers[layer_count-1];
	vector<Neuron*> cur_layer_neurons = cur_layer->neuronList;
	
	for(int i=0;i<cur_layer->get_population();i++){
		float output = cur_layer_neurons[i]->get_signal_output();
		y.push_back(output);
		cur_layer_neurons[i]->outputs[0]->set_error(z[i]-output);
	}

	float Error = distance_vec(z,y);

	if(Error<Threshold){
		return 1;		//case successful; no need to back propogate error
	}
	else return -1;		//back propogate the error

}

int neural_network::training_step(vector<float> input, vector<float> output){
	if((input.size()==layers[0]->get_population()) and (output.size()==layers[layer_count-1]->get_population())){
		this->set_input(input);
		this->fwd_propogate();
		int success = this->calculate_err(output);
		if(success == 1){
			return 1;
		}
		this->back_propogate();
		this->weight_update();
		return -1;	
		}

	else{
		cout<<"training data's size doesn't comply with the network" <<endl;
	}
	return 0;
}


//print the neural network
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
