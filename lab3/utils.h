#ifndef _UTILS
#define _UTILS

#include <vector>

#define DEBUG 0
#define IFBUG if(DEBUG){
#define ENDBUG }


double sigmoid(double x);

double get_random(); //get random number b/w 0 and 1

double distance_vec(vector<double>, vector<double>);

void printvec(vector<double> v);
#endif
