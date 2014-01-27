#include "components.h"
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
