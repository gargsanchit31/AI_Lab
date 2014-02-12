#include "components.h"
#include "utils.h"
/** Edge **/
extern double EITA;
extern double MOMENTUM;

Edge::Edge(){
    weight = get_random();
    oldweight = weight;
}

Edge::Edge(double wt){
    weight = wt;
    oldweight = 0;
}

Edge::~Edge(){
}

void Edge::set_signal(double in){
    input_signal = in;
}
void Edge::set_error(double err){
    input_error = err;
}
void Edge::set_weight(double x){
    weight = x;
}

double Edge::get_weight(){
    return weight;
}
double Edge::get_input_signal(){
    return input_signal;
}
double Edge::get_input_error(){
    return input_error;
}
double Edge::get_output_signal(){
    return (input_signal * weight);
}
double Edge::get_output_error(){
    return (input_error * weight);
}

void Edge::print_signal(){
    printf("Edge sig: wt=%f, sig_in=%f, sig_out=%f\n", weight, input_signal, get_output_signal());
}
void Edge::print_error(){
    printf("Edge err: wt=%f, err_in=%f, err_out=%f\n", weight, input_error, get_output_error());
}

/** Neuron **/
Neuron::Neuron(char n_type, neuron_id nid, int in_size, int out_size){
    type = n_type;
    id = nid;
    inputs.resize(in_size);
    outputs.resize(out_size);
}

double Neuron::get_signal_output(){
    return signal_output;
}
double Neuron::get_delta_error(){
    return delta_error;
}

void Neuron::propogate_signal(){
    double weighted_signal = 0;
    for(int i=0; i<inputs.size(); i++){
        weighted_signal += inputs[i]->get_output_signal();
    }
    IFBUG cout << "wt in" <<weighted_signal << endl; ENDBUG
    if(type == 'I'){
        signal_output = weighted_signal;
    }
    else{
        signal_output = sigmoid(weighted_signal);
       // signal_output = weighted_signal;
    }
    IFBUG cout <<"out " << signal_output << endl; ENDBUG
    for(int i=0; i< outputs.size(); i++){
        outputs[i]->set_signal(signal_output);
        IFBUG cout << outputs[i]->get_output_signal() << endl; ENDBUG
    }
}

void Neuron::propogate_error(){
    double weighted_error = 0;
    for(int i=0; i<outputs.size(); i++){
        weighted_error += outputs[i]->get_output_error();
    }
    IFBUG cout << "weighted error" <<weighted_error << endl; ENDBUG
    delta_error = weighted_error * signal_output* (1 - signal_output); // deltaj = sigma(wted err-k) * dy/dx
    IFBUG cout <<"out " << delta_error << endl; ENDBUG
    for(int i=0; i< inputs.size(); i++){
        inputs[i]->set_error(delta_error);
        IFBUG cout << inputs[i]->get_output_error() << endl; ENDBUG
    }
}

void Neuron::update_weights(){ //for each input edge, update its weight acc to DELTA_W = delta_j * eita * output_i(of prev neuron NOT WEIGHTED)
    static int x= 0;
    if(x == 0) {
        cout << "Momentuem " << MOMENTUM << endl; x++;
    }
    for(int i=0; i<inputs.size() ;i++){
        double weight = inputs[i]->weight;
        double oldweight = inputs[i]->oldweight;
        double delta_W = (1- MOMENTUM)* delta_error * EITA * inputs[i]->get_input_signal() + MOMENTUM * (weight - oldweight);
        inputs[i]->oldweight = weight;
        inputs[i]->set_weight(weight + delta_W);
    }
}

neuron_id Neuron::get_id(){
    return id;
}
