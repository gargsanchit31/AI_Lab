#ifndef _UTILS
#define _UTILS

#include <vector>

#define DEBUG 0
#define IFBUG if(DEBUG){
#define ENDBUG }


float sigmoid(float x);

float get_random(); //get random number b/w 0 and 1

float distance_vec(vector<float>, vector<float>);

void printvec(vector<float> v);
#endif
