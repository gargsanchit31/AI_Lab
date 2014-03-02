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

double EITA = 0.02;
double THRESH = 0.01;
int RANDNO = 1;
int ISRAND = 1; //does weights are given randomly
double FIXWEIGHT = 0.5; //if ISRAND = 0, then this weight will be used
double MOMENTUM = 0.9;

int PRINTERROR = 1; //does network has to print cum_error after every 100 cycles
int ITERATION = 0; //global iteration count


using namespace std;

void run_network(neural_network *nn, vector<training_data>& data){
    ITERATION = 0;
    while(1){
        ITERATION++;
        //cout << "iteration " << ITERATION <<endl;
        if(ITERATION > 1000){
            cout << "inside "<< endl;
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
    cout << "Taken layer info" << endl;

    char train_truth_file[100];
    int train_record_count;
    vector<training_data> data;

    inFile >> train_truth_file;
    inFile >> train_record_count;
    cout << "Taken record count" << endl;

    int numinputs = layer_sizes[0];
    int numoutputs = layer_sizes[num_layers-1];

    int i;
    double in;
    IFBUG cout << "num " << numinputs << " "<< numoutputs <<endl; ENDBUG
    ifstream truthFile;
    truthFile.open(train_truth_file, ios::in);
    if(!truthFile.is_open()){
        cout << "can't open truth file " << train_truth_file <<endl;
        exit(0);
    }

    for(i=0; i<train_record_count;i++){
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
    char x;
    truthFile >> x;
    cout << " The end character is " << x << endl;  
    IFBUG cout << "input data taken "<< i<<endl; ENDBUG
    truthFile.close();

    IFBUG cout << "taking opton " <<endl; ENDBUG
    string option;
    inFile >> option; //a : print iteration vs sq_error
    IFBUG cout << "option is " << option <<endl; ENDBUG

    if(option == "tweets"){ //further take eita and thresh and then take input for testing
        cout << "option is" << option << endl;
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

        //nn->print_network();
        //5-fold  verification phase
        char test_truth_file[100];
        int test_record_count;
        int correct_count = 0; //no of test tweets classified correctly

        inFile >> test_truth_file;
        inFile >> test_record_count;

        truthFile.open(test_truth_file, ios::in);
        if(!truthFile.is_open()){
            cout << "can't open truth file " << test_truth_file <<endl;
            exit(0);
        }

        cout << "Test record count " <<endl;
        cout << "no of input /outputs" << numinputs<<" " <<numoutputs <<endl;
        for(int i=0; i<test_record_count;i++){
            training_data d;
            for(int j=0;j<numoutputs;j++){
                truthFile >> in;
                d.target.push_back(in);
            }
            vector<double> zero;
            zero.push_back(0);
            zero.push_back(0);
            zero.push_back(0);
            if(are_equal_vec(d.target,zero)) cout << "Some mishap occured @ input " << i  <<endl;

            for(int j=0;j<numinputs;j++){
                truthFile >> in;
                d.input.push_back(in);
            }
            vector<double> out = nn->calculate_output(d.input);
            printvec(out);
            printvec(d.target);
            cout << "---" << endl;
            //if(are_equal_vec({1,3,4}, {1, 3, 4}) cout << "Hello \n";
            if(are_equal_vec(out, d.target)){
                cout << "correct\n";
                correct_count++;
            }
            else{
                cout << "wrong\n";
            }
        }
        char x;
        truthFile >> x;
        cout << " The end character is " << x << endl;  
        cout << "accuracy " << ((float)correct_count * 100)/test_record_count << endl;

        truthFile.close();
    }

    /******************************/
    inFile.close();

	return 0;
}
