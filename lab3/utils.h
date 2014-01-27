#ifndef _UTILS
#define _UTILS
#include <iostream>
#include <cmath>
using namespace std;

float sigmoid(float x){
    return 1/(1 + exp(-x));
}

#endif
