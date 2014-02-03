#include "components.h"
#include "utils.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

float EITA = 0.03;
int main(){
    srand(time(NULL));
    Edge *i0 = new Edge(-1);
    Edge *i1 = new Edge(3);
    Edge *o0 = new Edge(2);
    Edge *o1 = new Edge(1);

    neuron_id id = {'B', 3};

    Neuron * n = new Neuron ('H',id,2,2);
    cout << n->get_id().layer_id << n->get_id().seq_no <<endl;
    n->inputs[0] = i0;
    n->inputs[1] = i1;
    n->outputs[0] = o0;
    n->outputs[1] = o1;

    cout << "\n*****\nChecking signal prop()" <<endl;
    n->inputs[0]->set_signal(1.5);
    n->inputs[1]->set_signal(1);
    n->propogate_signal(); //propogate_signal
    cout << "printing the output edges\n";
    cout << n->get_signal_output() <<endl;
    n->outputs[0]->print_signal();
    n->outputs[1]->print_signal();
    //cout << sigmoid(1.5) <<endl;
    
    cout <<endl;

    cout << "\n*****\nChecking error prop()" <<endl;
    n->outputs[0]->set_error(3);
    n->outputs[1]->set_error(4);
    n->propogate_error();//propogate error
    cout << n->get_delta_error()<<endl;
    cout << "printing the output edges\n";
    n->inputs[0]->print_error();
    n->inputs[1]->print_error();
    cout << "expected err_in of prev edges " << 10*(0.8175)*(1-0.8175) <<"\n";

    cout << "\n*****\nChecking weight update()" <<endl;
    n->update_weights(); //run update weights
    n->inputs[0]->print_signal();
    cout << "prev edge's updated wt should be " << (-1 + 1.49164 * 0.01 * 1.5) << endl;
    n->inputs[1]->print_signal();

    //checking Edge() random constructor
    Edge * er = new Edge();
    er->print_signal();
    er = new Edge();
    er->print_signal();
    er = new Edge();
    er->print_signal();
    er = new Edge();
    er->print_signal();
    
    //checking randomness of rand function
    /*for(int i=0;i<100;i++){
        cout << get_random() <<endl;
    }*/
}
