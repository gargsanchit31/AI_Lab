#ifndef _UTILS
#define _UTILS

#include <vector>

#define DEBUG 0
#define IFBUG if(DEBUG){
#define ENDBUG }


double sigmoid(double x);

double get_random(); //get random number b/w 0 and 1

double distance_vec(vector<double>, vector<double>);
double are_equal_vec(vector<double> Z, vector<double> Y);

void printvec(vector<double> v);
int get_boolean(float in);
#endif
