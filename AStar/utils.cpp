#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

using namespace std;


float get_random(int RANDNO){
    float r = rand()%(RANDNO);
    return r;
}
