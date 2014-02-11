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
    double delta_error; //delta-j
    double signal_output;
public:
    vector<Edge*> inputs; // input edges
    vector<Edge*> outputs; // output edges
    Neuron(char n_type, neuron_id nid, int in_size, int out_size);
    ~Neuron();
    double get_signal_output();
    double get_delta_error();
    neuron_id get_id();
    void propogate_signal(); // collect weighted input from input edges, calculate the output and set it to all output edges
    void propogate_error();  // collect weighted delta_error from output edges, calculate self delta_error and propogate it to input edges
    void update_weights(); // update weights of each 
};

class Edge{
    double input_signal; // lower layer to high
    double input_error; // high layer to low
public:
    double weight; // weight on the edge
    double oldweight;
    Edge(double weight);
    Edge();
    ~Edge();
    void set_signal(double x);
    void set_error(double x);
    void set_weight(double x);
    double get_weight();
    double get_input_signal();
    double get_input_error();
    double get_output_signal(); //calculates the output using weight * input_signal
    double get_output_error(); 
    void print_signal();
    void print_error();
};

#endif
