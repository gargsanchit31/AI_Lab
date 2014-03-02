#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

extern int RANDNO;
extern int ISRAND;
extern double FIXWEIGHT;

using namespace std;

double sigmoid(double x){
    return 1/(1 + exp(-x));
}

double get_random(){
    if(ISRAND == 1){ 
        double r = ((double) rand() * RANDNO/ (RAND_MAX));
        return r;
    }
    else return FIXWEIGHT;
}

double distance_vec(vector<double> Z, vector<double> Y){
	if(Z.size()!=Y.size()){
		cout<<"In dotproduct(): Error on vector sizes\n";
		exit(1);
	}
	else{
		double Error =0, z=0;
		for(int i=0;i<Z.size();i++){
			Error+=pow(Z[i]-Y[i], 2);
		}
		return Error;
	}
}

void printvec(vector<double> v){
	for(int j=0;j<v.size();j++){
		cout<<v[j]<<" ";
	}
}

bool are_equal_vec(vector<double> Z, vector<double> Y){
	if(Z.size()!=Y.size()){
		cout<<"In are_equal_vec(): Error on vector sizes\n";
		exit(1);
	}
	for(int j=0;j<Z.size();j++){
        if(Z[j] != Y[j]) return false;
	}
    return true;
}
int get_boolean(float in){
    if(in > 0.5) return 1;
    else return 0;
}
