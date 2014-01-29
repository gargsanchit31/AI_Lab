#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

using namespace std;

float sigmoid(float x){
    return 1/(1 + exp(-x));
}

float get_random(){
    float r = ((float) rand() / (RAND_MAX));
    return r;
}

float distance_vec(vector<float> Z, vector<float> Y){
	if(Z.size()!=Y.size()){
		cout<<"In dotproduct(): Error on vector sizes\n";
		exit(1);
	}
	else{
		float Error =0, z=0;
		for(int i=0;i<Z.size();i++){
			Error+=pow(Z[i]-Y[i], 2);
		}
		return Error;
	}
}

void printvec(vector<float> v){
	for(int j=0;j<v.size();j++){
		cout<<v[j]<<" ";
	}
	cout<<endl;
}