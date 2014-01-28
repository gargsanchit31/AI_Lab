#include "components.h"
#include "utils.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
int main(){
    Edge *i0 = new Edge(-1);
    Edge *i1 = new Edge(3);
    Edge *o0 = new Edge(2);
    Edge *o1 = new Edge(1);

    neuron_id id = {'A', 0};

    Neuron * n = new Neuron ('H',id,2,2);
    n->inputs[0] = i0;
    n->inputs[1] = i1;
    n->outputs[0] = o0;
    n->outputs[1] = o1;

    cout << "Checking signal prop()" <<endl;
    n->inputs[0]->set_signal(1.5);
    n->inputs[1]->set_signal(1);
    n->propogate_signal();
    cout << "printing the output edges\n";
    cout << n->get_signal_output() <<endl;
    n->outputs[0]->print_signal();
    n->outputs[1]->print_signal();
    //cout << sigmoid(1.5) <<endl;
    
    cout <<endl;

    cout << "Checking error prop()" <<endl;
    n->outputs[0]->set_error(3);
    n->outputs[1]->set_error(4);
    n->propogate_error();
    cout << n->get_delta_error()<<endl;
    cout << "printing the output edges\n";
    n->inputs[0]->print_error();
    n->inputs[1]->print_error();
    cout << 10*(0.8175)*(1-0.8175) <<"\n";

    /*printf ("First number: %d\n", rand()%100);
    srand (time(NULL));
    printf ("Random number: %d\n", rand()%100);
    srand (1);
    printf ("Again the first number: %d\n", rand()%100);*/
}
