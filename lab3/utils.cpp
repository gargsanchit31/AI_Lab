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

float distance_vec(vector<float> v1, vector<float> v2){
	if(v1.size()!=v2.size()){
		cout<<"In dotproduct(): Error on vector sizes\n";
		exit(1);
	}
	else{
		float Error =0;
		for(int i=0;i<v1.size();i++){
			Error+=pow(v1[i]-v2[i], 2);
		}
		return Error;
	}
}