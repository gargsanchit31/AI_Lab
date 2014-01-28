#include "components.h"
#include "utils.h"
#include "neural_network.h"
#include "layer.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int main(){

	vector<int> sizes ={3,5,2,3,4};
	int size = sizes.size();
	neural_network* nn = new neural_network(size,sizes);

	nn->print_topology();

	return 0;
}