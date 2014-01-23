#ifndef _PERCEPT
#define _PERCEPT
#include <iostream>
#include <vector>
#define N 7
using namespace std;

class Perceptron{
	/*Variables Declaration*/
	//int N;				/* Input Size*/
	vector<int> W;	/* Ist element is Theta and rest N elements are weights*/
	int Theta;
	public: vector<vector<int> > trainingSet;

	/*Method Declaration*/
	public: Perceptron();
	//public: Perceptron(int a);
	public: ~Perceptron();
	public: void take_Input(vector<int> inp);
	public: void train_Percept();
	bool check(vector<int> inp);
};


void printvec(vector<int>);
int dotproduct(vector<int> v1, vector<int> v2);
bool compare(vector<int> i, vector<int> j);
bool cycleCheck(vector<vector<int> > v, vector<int> w);
vector<int> addition(vector<int> v1, vector<int> v2);


#endif