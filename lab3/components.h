#ifndef _COMPONENTS
#define _COMPONENTS
#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <cmath>
#include <vector>
#include <ctime>
using namespace std;

/** class declaration **/
class Edge;
class Neuron;

/** class definition **/
class Neuron{
public:
    vector<Edge*> inputs; // input edges
    vector<Edge*> outputs; // output edges
    Neuron(int in_size, int out_size);
    ~Neuron();
    void trigger(); // collect weighted input from input edges, calculate the output and set it to all output edges
};

class Edge{
    float weight; // weight on the edge
    float input; // input at start end
    //Neuron * start, *end; // contain the starting and ending peceptrons which it connects
public:
    Edge(float weight);
    Edge();
    ~Edge();
    void set_input(float x);
    void set_weight(float x);
    float get_weight();
    float get_output(); //calculates the output using weight * input
    void print();
};

#endif
