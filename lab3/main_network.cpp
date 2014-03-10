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
#define  MAXITERATION 10000
#define INF 10000000

double EITA = 0.02;
double THRESH = 0.01;
double RANDNO = 1;
int ISRAND = 1; //does weights are given randomly
double FIXWEIGHT = 0.5; //if ISRAND = 0, then this weight will be used
double MOMENTUM = 0.7;

int PRINTERROR = 1; //does network has to print cum_error after every 100 cycles
int ITERATION = 0; //global iteration count


using namespace std;

void run_network(neural_network *nn, vector<training_data>& data){
    ITERATION = 0;
    while(1){
        ITERATION++;
        //cout << "iteration " << ITERATION <<endl;
        if(ITERATION == MAXITERATION){
            cout << "inside "<< endl;
            break;
        }
        //training_data d = data[i];
        int result = nn->training_step(data);
	//nn->print_network();
        if(result==1){
            break;
        }
    }
}

int main(int argc, char *argv[]){ //args control-file-name  #block in 4/5 testing

    srand(time(NULL));

    /****** input for palindrome ****/
    ifstream inFile;
    inFile.open(argv[1], ios::in);
    int block_no = atoi(argv[2]);
    cout << "BLOCK no is  " << block_no << endl;
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

    char truth_file[100];
    int record_count;
    vector<training_data> data;
    vector<training_data> test_data;

    inFile >> truth_file;
    inFile >> record_count;
    int size_block = record_count/5;
    cout << "Taken record count" << endl;

    string to_normalise; //whether to normalise the input data or not
    inFile >> to_normalise;
    float normal_factor =1;
    if(to_normalise == "yes"){
        inFile>> normal_factor;
        cout << "Asked to normalise by factor of " << normal_factor <<endl;
    }

    int numinputs = layer_sizes[0];
    int numoutputs = layer_sizes[num_layers-1];
    cout << "numinputs " << numinputs << " " << numoutputs << endl;

    int i;
    double in;
    IFBUG cout << "num " << numinputs << " "<< numoutputs <<endl; ENDBUG
    ifstream truthFile;
    truthFile.open(truth_file, ios::in);
    if(!truthFile.is_open()){
        cout << "can't open truth file " << truth_file <<endl;
        exit(0);
    }

    for(i=0; i<record_count;i++){
        training_data d;
        for(int j=0;j<numoutputs;j++){
            truthFile >> in;
            d.target.push_back(in);
        }
        for(int j=0;j<numinputs;j++){
            truthFile >> in;
            d.input.push_back(in/normal_factor);
            //d.input.push_back(in);
        }
        //printvec(d.target); printvec( d.input); cout << endl;
        if(i/size_block == block_no){
         //   cout << i << " t\n";
            test_data.push_back(d);
        }
        else{
          //  cout << i << " i\n";
            data.push_back(d);
        }
    }
    char x;
    truthFile >> x;

    cout << " The end character is " << x << endl;  
    IFBUG cout << "All data taken "<< i<<endl; ENDBUG
    truthFile.close();

    IFBUG cout << "taking option " <<endl; ENDBUG
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
        inFile >> MOMENTUM;
        cout << "MOMENTUM is " << MOMENTUM <<endl;

	    neural_network* nn = new neural_network(num_layers,layer_sizes, THRESH);
        //nn->print_topology();
        
        run_network(nn, data);

        cout <<ITERATION<< "\ntraining complete";

        cout << "test_record_count " << size_block <<endl;
        float correct_count = 0; //no of test tweets classified correctly

        for(int i=0; i<test_data.size();i++){
            vector<double> out = nn->calculate_output(test_data[i].input);
            printvec(out);
            printvec(test_data[i].target);
            cout << "---" << endl;
            //if(are_equal_vec({1,3,4}, {1, 3, 4}) cout << "Hello \n";
            cout << "c/s " << are_equal_vec(out, test_data[i].target) <<endl;
            correct_count += are_equal_vec(out, test_data[i].target);
        }
        cout << "correct_count " << correct_count <<endl;
        cout << "accuracy " << ((float)correct_count * 100)/test_data.size()<< endl;
    }

    /******************************/
    inFile.close();

	return 0;
}
