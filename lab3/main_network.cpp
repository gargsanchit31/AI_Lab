#include "components.h"
#include "utils.h"
#include "neural_network.h"
#include "layer.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include  <iostream>
#include  <fstream>
#include <string>

/** debugging symbols **/
#define DEBUG 0
#define IFBUG if(DEBUG){
#define ENDBUG }

/** debugging symbols **/

float EITA = 0.02;
float THRESH = 0.01;
int RANDNO = 1;
int ISRAND = 1; //does weights are given randomly
float FIXWEIGHT = 0.5; //if ISRAND = 0, then this weight will be used

int PRINTERROR = 0; //does network has to print cum_error after every 100 cycles
int ITERATION = 0; //global iteration count


using namespace std;

void run_network(neural_network *nn, vector<training_data>& data){
    ITERATION = 0;
    while(1){
        ITERATION++;
        //if(ITERATION % 1000 == 0) cout << ITERATION /1000 <<endl;
        if(ITERATION > 100000){
            break;
        }
        //training_data d = data[i];
        int result = nn->training_step(data);
        if(result==1){
            break;
        }
    }
}

int main(int argc, char *argv[]){

    srand(time(NULL));

    /****** input for palindrome ****/
    ifstream inFile;
    inFile.open(argv[1], ios::in);
    if(!inFile.is_open()){
        cout << "can't open control file " << argv[1] <<endl;
        exit(0);
    }
    //take layer count
    int num_layers;
    inFile >> num_layers;

    //take no of neurons in each layer
    vector<int> layer_sizes;
    layer_sizes.resize(num_layers);
    for(int i=0; i< num_layers; i++){
        inFile >> layer_sizes[i];
    }
    //take training data

    char truth_file_name[100];
    inFile >> truth_file_name;
     
    vector<training_data> data;
    int numinputs = layer_sizes[0];
    int numoutputs = layer_sizes[num_layers-1];

    int i;
    float in;
    IFBUG cout << "num " << numinputs << " "<< numoutputs <<endl; ENDBUG
    ifstream truthFile;
    truthFile.open(truth_file_name, ios::in);
    if(!truthFile.is_open()){
        cout << "can't open truth file " << truth_file_name <<endl;
        exit(0);
    }

    for(i=0;i<pow(2,numinputs);i++){
        training_data d;
        for(int j=0;j<numoutputs;j++){
            truthFile >> in;
            d.target.push_back(in);
        }
        for(int j=0;j<numinputs;j++){
            truthFile >> in;
            d.input.push_back(in);
        }
        data.push_back(d);
    }
    IFBUG cout << "input data taken "<< i<<endl; ENDBUG
    truthFile.close();

    IFBUG cout << "taking opton " <<endl; ENDBUG
    string option;
    inFile >> option; //a : print iteration vs sq_error
    IFBUG cout << "option is " << option <<endl; ENDBUG

    if(option == "a"){
        IFBUG cout << "option is 'a'" << endl; ENDBUG
        //input EITA and THRESH
        inFile >> EITA;
        IFBUG cout << "EITA is " << EITA <<endl; ENDBUG
        inFile >> THRESH;
        IFBUG cout << "THRESH is " << THRESH <<endl; ENDBUG

        PRINTERROR = 1;
	    neural_network* nn = new neural_network(num_layers,layer_sizes, THRESH);
        //nn->print_topology();
        //nn->print_network();

        run_network(nn, data);

    }
    else if(option == "demo"){ //further take eita and thresh and then take input for testing
        cout << "option is demo" << endl;
        //input EITA and THRESH
        inFile >> EITA;
        cout << "EITA is " << EITA <<endl;
        inFile >> THRESH;
        cout << "THRESH is " << THRESH <<endl;

	    neural_network* nn = new neural_network(num_layers,layer_sizes, THRESH);
        //nn->print_topology();
        //nn->print_network();

        run_network(nn, data);

        cout <<ITERATION<< "\ntraining complete";

        nn->print_network();
        while(1){
            vector<float> test;
            cout << "give the " << numinputs << " inputs seperated by spaces: ";
            int inp;
            for(int i=0;i<numinputs;i++){
                cin >> inp;
                test.push_back(inp);
            }
            vector<float> out = nn->calculate_output(test);
            printvec(out);
        }
    }

    /******************************/
    inFile.close();

	return 0;
}
