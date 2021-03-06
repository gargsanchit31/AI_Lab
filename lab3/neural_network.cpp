#include "neural_network.h"
#include "components.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

extern int PRINTERROR; //does network has to print cum_error after every 100 cycles
extern int ITERATION; //global iteration count

using namespace std;

//size= "#(layers)", layer_vec[i] = #(neurons) at layer i
neural_network::neural_network(int size, vector<int> layer_vec, double thresh){
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
			while(l_no < layer_count - 1){
				l = new layer('H', l_id++, layer_vec[l_no], layer_vec[l_no - 1], layer_vec[l_no + 1]);
				l_no++;		//increment the layer number
				layers.push_back(l);
			}
		}

		//last layer as output layer
		l = new layer('O', l_id++, layer_vec[l_no], layer_vec[l_no - 1], 1);
		//cout<<"layer is: "<<l_no<<endl;
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
				Edge* e = new Edge(1);
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
				if(cur_index != 0){
					Edge * e = new Edge();
					e->set_signal(-1);
					cur_layer_neurons[j]->inputs.push_back(e);
				}
			}
		}

		/* for the last layer (output) create one output edge for each node
		*/
		if(cur_index == layer_count-1){
			for(int j=0;j<cur_layer->get_population();j++){
				Edge* e = new Edge(1);
				cur_layer_neurons[j]->outputs[0] = e;

				e = new Edge();
				e->set_signal(-1);
				cur_layer_neurons[j]->inputs.push_back(e);
			}
			
		}
	}
}

void neural_network::fwd_propogate(){
	for(int i=0;i<layers.size();i++){
		layers[i]->propogate_sig();
	}
}

void neural_network::back_propogate(){ //n-1 to upto layer 1 (leaving input layer i.e 0 as that is never used)
	for(int i=layers.size()-1 ; i>0 ; i--){
		layers[i]->propogate_err();
	}
}

void neural_network::weight_update(){ //1 to n-1 (leaving input layer 0) since weights of input edges are fixed 1
	for(int i=1;i<layers.size();i++){
		layers[i]->weight_update();
	}
}

void neural_network::set_input(vector<double> input){
	layer* cur_layer = layers[0];
	vector<Neuron*> cur_layer_neurons = cur_layer->neuronList;
	
	for(int i=0;i<cur_layer_neurons.size();i++){
		cur_layer_neurons[i]->inputs[0]->set_signal(input[i]);
	}
}

double neural_network::calculate_err(vector<double> z){
	vector<double> y;
	layer* cur_layer = layers[layer_count-1];
	vector<Neuron*> cur_layer_neurons = cur_layer->neuronList;
	IFBUG cout << "output: " ; ENDBUG
	for(int i=0;i<cur_layer->get_population();i++){
		double output = cur_layer_neurons[i]->get_signal_output();
		IFBUG cout << output << " "; ENDBUG
		y.push_back(output);
		cur_layer_neurons[i]->outputs[0]->set_error(z[i]-output);
	}
	IFBUG cout << endl; ENDBUG

	double Error = distance_vec(z,y);
	IFBUG cout << Error << " "; ENDBUG
	return Error;
	// //sleep(1);
	// if(Error<Threshold){
	// 	return 1;		//case successful; no need to back propogate error
	// }
	// else return -1;		//back propogate the error

}

int neural_network::training_step(vector<training_data> inp_data){
	double Error=0;
	for(int d=0;d<inp_data.size();d++){
		training_data data=inp_data[d];

		if((data.input.size()==layers[0]->get_population()) and (data.target.size()==layers[layer_count-1]->get_population())){
			//cout << "PRINTING " <<endl;
			this->set_input(data.input);
			//cout << "before propogate " <<endl;
			//this->print_network();
			this->fwd_propogate();
			//cout << "before back prop " <<endl;
			//this->print_network();
			Error += this->calculate_err(data.target);
			this->back_propogate();
			//cout << "before weight_update " <<endl;
			//this->print_network();
			this->weight_update();
			//cout << "after update weight " <<endl;
			//this->print_network();
			//printvec(data.input);
		}

		else{
			cout<<"training data's size doesn't comply with the network" <<endl;
			return -1;
		}
	}
    int num_patterns = pow(2,layers[layer_count-1]->get_population());
    Error  = Error;

	if(PRINTERROR == 1 && ITERATION%100 == 0) cout << ITERATION/100 << " " << Error << endl;
	if(Error >= Threshold){
		return -1;
	}
	return 1; // Error is within the limit, we are done with the training
}

vector<double> neural_network::calculate_output(vector<double> input){
	this->set_input(input);
	this->fwd_propogate();
	vector<double> y;
	layer* cur_layer = layers[layer_count-1];
	vector<Neuron*> cur_layer_neurons = cur_layer->neuronList;
	
	for(int i=0;i<cur_layer->get_population();i++){
		double output = cur_layer_neurons[i]->get_signal_output();
		y.push_back(output);
	}
	return y;
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

void neural_network::print_network(){
	for(int cur_index=layer_count-1; cur_index>=0; cur_index--){
		layers[cur_index]->print_layer();
	}
}

void neural_network::print_truth(){ //print o/p {0,1} for the neurons in all layers(except input)
	for(int cur_index=layer_count-1; cur_index>0; cur_index--){
		layer* cur_layer = layers[cur_index];
		vector<Neuron*> cur_layer_neurons = cur_layer->neuronList;
        for(int j=0; j<cur_layer->get_population(); j++){
            float out = cur_layer_neurons[j]->get_signal_output();
            cout << get_boolean(out) << " ";
        }
        cout << " | ";
	}
}
