#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

extern double RANDNO;
extern int ISRAND;
extern double FIXWEIGHT;

using namespace std;

double sigmoid(double x){
    return 1/(1 + exp(-x));
}

double get_random(){
    if(ISRAND == 1){ 
        double r =( (double)rand() * RANDNO/ (RAND_MAX));
	//cout << "returning random " << r << endl;
        return r;
    }
    else {
	//cout << "returning fixweight" <<endl;
	return FIXWEIGHT;
	}
}

double distance_vec(vector<double> Z, vector<double> Y){
	if(Z.size()!=Y.size()){
		cout<<"In dotproduct(): Error on vector sizes\n";
		exit(1);
	}
	else{
		double Error =0, z=0;
		for(int i=0;i<Z.size();i++){
			Error+=(Z[i]-Y[i])*(Z[i]-Y[i]);
		}
		return Error;
	}
}

void printvec(vector<double> v){
	for(int j=0;j<v.size();j++){
		cout<<v[j]<<" ";
	}
}

double are_equal_vec(vector<double> Z, vector<double> Y){
	if(Z.size()!=Y.size()){
		cout<<"In are_equal_vec(): Error on vector sizes\n";
		exit(1);
	}
    int c = 0;
    float s = Z.size();
	for(int j=0;j<Z.size();j++){
        if(Z[j] == Y[j]) c++;
	}
    double ratio;
    ratio = ((float)c)/s;
    if(ratio >= 1) return 1;
    else return 0;
    //cout << "returning c " << c << "S " << s <<" "<< ratio << endl;
    return ratio;
}

int get_boolean(float in){
    if(in > 0.5) return 1;
    else return 0;
}
