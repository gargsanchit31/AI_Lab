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
    //cin >> x;
    //printf("sigmoid %f = %f\n",x, sigmoid(x));

    Edge *i0 = new Edge(-1);
    Edge *i1 = new Edge(3);
    Edge *o0 = new Edge(2);
    Edge *o1 = new Edge(1);

    Neuron * n = new Neuron (2,2);
    n->inputs[0] = i0;
    n->inputs[1] = i1;
    n->outputs[0] = o0;
    n->outputs[1] = o1;

    n->inputs[0]->set_input(1.5);
    n->inputs[1]->set_input(1);
    n->trigger();
    cout << n->inputs[0]->get_output() << endl;
    

    /*printf ("First number: %d\n", rand()%100);
    srand (time(NULL));
    printf ("Random number: %d\n", rand()%100);
    srand (1);
    printf ("Again the first number: %d\n", rand()%100);*/
}
