#ifndef PRI_Q
#define PRI_Q
#include <iostream>
#include <vector>
using namespace std;

/*
 * Comparable class must have a public member (int index) which will keep track the index in the vector<Comparable>
 * Comparable must be a pointer so that we use -> to access index
 */
template <class Comparable, class Compare>
class Priority_Q{
private:
	vector<Comparable> vec;
	int currSize;   
	//int capacity;
	
public:
	
	void percolateDown(int hole);
	void percolateUp(int hole);
	//Priority_Q(){}
	Priority_Q(){
		vec.resize(100);
		currSize=0;
	}
	void pop();
	void push(Comparable x); //inserts and update Dlist if type DEPARTURE

	void print();
	int size();
	bool empty();
	Comparable top();
};

template <class Comparable, class Compare>
void Priority_Q<Comparable, Compare>::percolateUp(int hole){
	int parent;
	Comparable tmp=vec[hole];
	
	for(; hole >1 ; hole=parent){
		parent = hole/2;
		if(Compare()(tmp, vec[parent])){
			vec[hole]=vec[parent]; //copy into hole(lower) the parent
            vec[hole]->index = hole; //**index
		}
		else break;
	}
	vec[hole]=tmp;
    vec[hole]->index = hole; //**index
}

template <class Comparable, class Compare>
void Priority_Q<Comparable, Compare>::percolateDown(int hole){
    if(currSize==0) return;

	int child;
	Comparable tmp=vec[hole];
	for(;hole * 2 <=currSize; hole=child){
		child=hole*2;
		if(child!=currSize  && Compare()(vec[child+1], vec[child])){  //make sure hole's left child is
			child++;//not the last elem and compare lchild and rchild to find the min of the two store 
					//its index in child variable
		}
		if(Compare()(vec[child],tmp)){ //if temp > min of the two children move hole into the minchild 
			vec[hole]=vec[child];
            vec[hole]->index = hole; //**index
		}
		else 
			break;  //as ( temp < both children) and this hole is where temp should be
	}
	vec[hole]=tmp;
    vec[hole]->index = hole; //**index
}

template <class Comparable, class Compare>
void Priority_Q<Comparable, Compare>::push(Comparable x){
	if(currSize ==vec.size()) {cout<<"into \n" ;vec.resize(vec.size()*2);}
	
	vec[++currSize] = x;
    x->index = currSize; //**index
	percolateUp(currSize);
}

template <class Comparable, class Compare>
void Priority_Q<Comparable, Compare>::pop(){
	if(empty()){cout<<"  ERROR !! empty priority q\n";}

    vec[1]->index = -1; //**index : means popped element has no position in the PQ

	vec[1]=vec[currSize];  //copy last element to first
    if(currSize > 1) vec[1]->index = 1; //**index don't do this if popped element is the last one left(i.e 1 == currSize)
    currSize--;
	percolateDown(1);   	//call percolateDown with index 1 as this is 
							//where disturbance occured and 
							//its val is greater than what was before
}
	
//following fucntion which are basic and need no change to implement locator class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class Comparable, class Compare>
void Priority_Q<Comparable, Compare>::print(){
    cout << "* * * * * * * * * "<<endl;
	for(int i=1;i<=currSize;i++)
		cout << i << " (" <<vec[i]->f << ", " << vec[i]->index << ")" << ":" <<endl;
    cout <<"done printing" <<endl;
}

template <class Comparable, class Compare>
Comparable Priority_Q<Comparable, Compare>::top(){
	Comparable x;
	if(empty()){cout<<"  ERROR !! empty priority q\n"; return x;}
	else return vec[1];
}

template <class Comparable, class Compare>
bool Priority_Q<Comparable, Compare>::empty(){
	return currSize==0;
}

template <class Comparable, class Compare>
int Priority_Q<Comparable, Compare>::size(){
	return currSize;
}

#endif 
