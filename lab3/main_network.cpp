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

double EITA = 0.02;
double THRESH = 0.01;
int RANDNO = 1;
int ISRAND = 1; //does weights are given randomly
double FIXWEIGHT = 0.5; //if ISRAND = 0, then this weight will be used
double MOMENTUM = 0.2;

int PRINTERROR = 1; //does network has to print cum_error after every 100 cycles
int ITERATION = 0; //global iteration count


using namespace std;

void run_network(neural_network *nn, vector<training_data>& data){
    ITERATION = 0;
    while(1){
        ITERATION++;
        //if(ITERATION % 1000 == 0) cout << ITERATION /1000 <<endl;
        if(ITERATION > 1000000000){
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
    double in;
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
    if(option == "e"){//vary eita for fixed thresh
        IFBUG cout << "option is 'e'" << endl; ENDBUG
        //input EITA and THRESH
        inFile >> THRESH;
        IFBUG cout << "THRESH is " << THRESH <<endl; ENDBUG

        for(EITA=0.01; EITA<0.8 ; EITA+=0.02){
            neural_network* nn = new neural_network(num_layers,layer_sizes, THRESH);
            run_network(nn, data);
            cout << EITA << " " << ITERATION <<endl;
        }
    }
    if(option == "t"){//vary thresh for fixed eita
        IFBUG cout << "option is 't'" << endl; ENDBUG
        //input EITA and THRESH
        inFile >> EITA;
        IFBUG cout << "EITA is " << EITA <<endl; ENDBUG

        for(THRESH=0.01; THRESH<0.4 ; THRESH+=0.01){
            neural_network* nn = new neural_network(num_layers,layer_sizes, THRESH);
            run_network(nn, data);
            cout << THRESH << " " << ITERATION <<endl;
        }
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
            vector<double> test;
            cout << "give the " << numinputs << " inputs seperated by spaces: ";
            int inp;
            for(int i=0;i<numinputs;i++){
                cin >> inp;
                test.push_back(inp);
            }
            vector<double> out = nn->calculate_output(test);
            printvec(out); cout << endl;
        }
    }
    else if(option == "truth"){ //further take eita and thresh and then take input for testing
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

        cout << " - - - -  - - - - -  - - - - THE TRUTH IS HERE - - - - - - -  - - - - -  " <<endl;

        for(int i=0; i < data.size(); i++){
            nn->calculate_output(data[i].input);
            printvec(data[i].input); //this contains
            cout << " | ";
            nn->print_truth();
            cout <<endl;
        }
    }

    /******************************/
    inFile.close();

	return 0;
}
