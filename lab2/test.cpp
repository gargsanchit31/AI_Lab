#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include "perceptron.h"
using namespace std;

int main(){
	Perceptron p[10];
	vector<vector<int> > input;
	input.push_back({1,1,1,1,1,1,0});
	input.push_back({0,1,1,0,0,0,0});
	input.push_back({1,1,0,1,1,0,1});
	input.push_back({1,1,1,1,0,0,1});
	input.push_back({0,1,1,0,0,1,1});
	input.push_back({1,0,1,1,0,1,1});
	input.push_back({1,0,1,1,1,1,1});
	input.push_back({1,1,1,0,0,0,0});
	input.push_back({1,1,1,1,1,1,1});
	input.push_back({1,1,1,1,0,1,1});

	for(int i=0;i<10;i++){
		p[i].take_Input(input[i]);
		p[i].train_Percept();
	}
	vector<int> test_case = {1,1,1,1,1,1,0};

	for(int i=0;i<10;i++){
		if(p[i].check(test_case)){
			cout<<"detected digit: "<<i<<endl;
			return 0;
		}
	}

	cout<<"Could not detect any digit :) \n";
	return 0;
}