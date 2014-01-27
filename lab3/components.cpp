#include "components.h"
#include "utils.h"
/** Edge **/
Edge::Edge(){
    weight = 0;
}

Edge::Edge(float wt){
    weight = wt;
}

Edge::~Edge(){
}

void Edge::set_input(float in){
    input = in;
}

float Edge::get_output(){
    float out;
    out = input * weight;
    return out;
}

void Edge::set_weight(float x){
    weight = x;
}

float Edge::get_weight(){
    return weight;
}

void Edge::print(){
    printf("Edge: wt=%f, in=%f, out=%f\n", weight, input, get_output());
}

/** Neuron **/
Neuron::Neuron(int in_size, int out_size){
    inputs.resize(in_size);
    outputs.resize(out_size);
}

void Neuron::trigger(){
    float weighted_input = 0;
    for(int i=0; i<inputs.size(); i++){
        weighted_input += inputs[i]->get_output();
    }
    IFBUG cout << "wt in" <<weighted_input << endl; ENDBUG
    float output = sigmoid(weighted_input);
    IFBUG cout <<"out " << output << endl; ENDBUG
    for(int i=0; i< outputs.size(); i++){
        outputs[i]->set_input(output);
        IFBUG cout << outputs[i]->get_output() << endl; ENDBUG
    }
}
