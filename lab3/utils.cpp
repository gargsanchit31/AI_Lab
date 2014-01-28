#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

float sigmoid(float x){
    return 1/(1 + exp(-x));
}

float get_random(){
    float r = ((float) rand() / (RAND_MAX));
    return r;
}
