#ifndef _COMPONENTS
#define _COMPONENTS
#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <cmath>
#include <vector>
#include <ctime>
//#define EITA 0.03 // the learning rate
using namespace std;

typedef struct {
    char layer_id; // {A-Z}
    int seq_no; //order within the layer
} neuron_id;

/** class declaration **/
class Edge;
class Neuron;

/** class definition **/
class Neuron{
    char type; // {'I', 'H', 'O'}
    neuron_id id;
    float delta_error; //delta-j
    float signal_output;
public:
    vector<Edge*> inputs; // input edges
    vector<Edge*> outputs; // output edges
    Neuron(char n_type, neuron_id nid, int in_size, int out_size);
    ~Neuron();
    float get_signal_output();
    float get_delta_error();
    neuron_id get_id();
    void propogate_signal(); // collect weighted input from input edges, calculate the output and set it to all output edges
    void propogate_error();  // collect weighted delta_error from output edges, calculate self delta_error and propogate it to input edges
    void update_weights(); // update weights of each 
};

class Edge{
    float weight; // weight on the edge
    float input_signal; // lower layer to high
    float input_error; // high layer to low
public:
    Edge(float weight);
    Edge();
    ~Edge();
    void set_signal(float x);
    void set_error(float x);
    void set_weight(float x);
    float get_weight();
    float get_input_signal();
    float get_input_error();
    float get_output_signal(); //calculates the output using weight * input_signal
    float get_output_error(); 
    void print_signal();
    void print_error();
};

#endif
