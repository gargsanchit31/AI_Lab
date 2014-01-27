#include "components.h"
#include "utils.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
int main(){
    //float result = exp (1);
    //cout << result << endl;
    Edge e(2.0);
    e.set_input(3);
    e.print();
    e.set_input(6.32);
    e.print();

    float x;
    cin >> x;
    printf("sigmoid %f = %f\n",x, sigmoid(x));
    /*printf ("First number: %d\n", rand()%100);
    srand (time(NULL));
    printf ("Random number: %d\n", rand()%100);
    srand (1);
    printf ("Again the first number: %d\n", rand()%100);*/
}
