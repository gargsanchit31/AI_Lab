#include "components.h"
#include "utils.h"
#include "neural_network.h"
#include "layer.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include  <iostream>
#include  <fstream>

float EITA = 0.03;

using namespace std;

int main(){

	vector<int> sizes ={5, 4, 1};

	int size = sizes.size();
	neural_network* nn = new neural_network(size,sizes, 0.01);
	//training_data data[4];
	//vector<training_data> data = {{ {0,0}, {0}}, { {0,1}, {1}}, { {1,0}, {1}}, { {1,1}, {0}}};
    vector<training_data> data;

    /****** input for palindrome ****/
    ifstream inFile;
    inFile.open("palindrome_input.txt", ios::in);
    int N;
    float in;
    inFile >> N;
    int i;
    for(i=0;i<pow(2,N);i++){
        training_data d;
        inFile >> in;
        d.target.push_back(in);
        for(int j=0;j<N;j++){
            inFile >> in;
            d.input.push_back(in);
        }
        data.push_back(d);
    }
    cout << "input data taken "<< i<<endl;

    /******************************/
	nn->print_topology();


	int iteration = 0;
	for(int i=0; i<data.size();){
		iteration++;
		if(iteration % 1000 == 0) cout << iteration /1000 <<endl;
		if(iteration > 1000000){
			break;
		}
		//training_data d = data[i];
		int result = nn->training_step(data);
		if(result==1){
			i++;
			continue;
		}
		else i=0;
	}

	cout <<iteration<< "\ntraining complete";
    nn->print_network();
	float a,b,c,d,e;
	while(1){
		cout << "give a, b, c, d, e ";
		cin >> a; cin >> b;cin >> c;cin >> d;cin >> e;
		vector<float> out = nn->calculate_output({a,b,c,d,e});
		cout << out[0] <<endl;
	}

	return 0;
}
