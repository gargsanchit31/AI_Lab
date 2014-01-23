#include "perceptron.h"
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <cmath>
using namespace std;

void printvec(vector<int> v){
	for(int j=0;j<v.size();j++){
		cout<<v[j]<<" ";
	}
	cout<<endl;
}

int dotproduct(vector<int> v1, vector<int> v2){
	if(v1.size()!=v2.size()){
		cout<<"In dotproduct(): Error on vector sizes\n";
		exit(1);
	}
	else{
		int prod = 0;
		for(int i=0;i<v1.size();i++){
			prod+=v1[i]*v2[i];
		}
		return prod;
	}
}

bool compare(vector<int> i, vector<int> j)
{
	for(int k=0; k<i.size() ;k++)
	{
		if(i[k]!=j[k])
		{
			return false;
		}
	}
	return true;
}

bool cycleCheck(vector<vector<int> > v, vector<int> w)
{
	int count=1;
	
	for(int i=v.size()-1; i>=0 ; i--)
	{
			if(compare(v[i],w))
			{
				cout<<"cycle size : "<<count<<endl;
				return true;
			}
	count++;
	}
	return false;
}

vector<int> addition(vector<int> v1, vector<int> v2){
	if(v1.size()!=v2.size()){
		cout<<"In addition(): Error on vector sizes\n";
		exit(1);
	}
	else{
		for(int i=0;i<v1.size();i++){
			v1[i]=v1[i]+v2[i];
		}
		return v1;
	}
}
Perceptron::Perceptron(){
	//N=7;
	//W.resize(N+1,0);
	//cout<<"Default perceptron of size 7 has been created"<<endl;
}
/*
Perceptron::Perceptron(int n){
	//N=n;
	ThetaW.resize(n+1,0);
}*/

Perceptron::~Perceptron(){

}

//input is of size N
void Perceptron::take_Input(vector<int> inp){
	bitset<N+1> vec;
	int size=pow(2,N);
	
	for(int i=0;i<size;i++){
		vector<int> temp;
		vec = i;
		temp.push_back(1);
		
		for(int j=N-1;j>=0;j--){
			temp.push_back(vec[j]*-1);
		}
		trainingSet.push_back(temp);
	}

	for(int i=N-1; i>=0;i--){
		vec[i] = inp[N-i-1];
	}

	int x = vec.to_ulong();
	trainingSet[x][0] = -1;
	
	for(int j=0;j<N;j++){
		trainingSet[x][j+1]=inp[j];
	}
}

void Perceptron::train_Percept(){
	vector<int> ThetaW(N+1,0);
	vector<vector<int> > Vectors = trainingSet;
	vector<vector<int> > History;
	bool converge=false;
	int i=0;
	while(!converge){
		for(i=0;i<Vectors.size();i++){
			if(!(dotproduct(ThetaW,Vectors[i]) > 0)){
				History.push_back(ThetaW);
				ThetaW=addition(ThetaW,Vectors[i]);
				//printvec(ThetaW);
				if(cycleCheck(History,ThetaW)){
					cout<<"Cycle Found:::"<<endl;
					exit(1);
				}
				break;
			}
		}
		if(i==Vectors.size()){
			converge=true;
		}
	}
	Theta=ThetaW[0];
	W.insert(W.end(),ThetaW.begin()+1,ThetaW.end());
	/*
	cout << "done \n\n";
	cout<<"Theta is: "<<Theta<<endl;
	cout<<"Weights are: ";
	printvec(W);
	cout<<endl;*/
}

bool Perceptron::check(vector<int> inp){
	if(dotproduct(inp,W)>Theta){
		return true;
	}
	return false;
}

