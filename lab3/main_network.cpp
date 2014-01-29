#include "components.h"
#include "utils.h"
#include "neural_network.h"
#include "layer.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int main(){

	vector<int> sizes ={2, 2, 1};

	int size = sizes.size();
	neural_network* nn = new neural_network(size,sizes, 0.001);
	//training_data data[4];
	vector<training_data> data = {{ {0,0}, {0}}, { {0,1}, {1}}, { {1,0}, {1}}, { {1,1}, {0}}};
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
	float a,b;
	while(1){
		cout << "give a and b: ";
		cin >> a; cin >> b;
		vector<float> out = nn->calculate_output({a,b});
		cout << out[0] <<endl;
	}

	return 0;
}