#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
using namespace std;

int N;	//dimension
//input form <y, x1,x2,.....,xN>
vector<vector<int> > Vectors;
vector<vector<int> > History;

void printvec(vector<int> v){
	for(int j=0;j<v.size();j++){
		cout<<v[j]<<" ";
	}
	cout<<endl;
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

void take_input(){
	cin >>N;
	int num = pow(2,N);
	int y,x;
	for(int i=0;i<num;i++){
		vector<int> temp;
		int factor = 1;
		cin>>y;
		if(y==0){
			factor =-1;
			temp.push_back(1);
		}
		else{
			temp.push_back(-1);
		}
		for(int j=0;j<N;j++){
			cin>>x;
			temp.push_back(factor*x);
		}
		Vectors.push_back(temp);
	}
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

//v1=v1+v2
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
		
void RunPTA(){
	vector<int> ThetaW(N+1,0);
	bool converge=false;
	int i=0;
	while(!converge){
		for(i=0;i<Vectors.size();i++){
			if(!(dotproduct(ThetaW,Vectors[i]) > 0)){
				History.push_back(ThetaW);
				ThetaW=addition(ThetaW,Vectors[i]);
				printvec(ThetaW);
				if(cycleCheck(History,ThetaW)){
					exit(1);
				}
				break;
			}
		}
		if(i==Vectors.size()){
			converge=true;
		}
	}
	cout << "done \n\n";
	cout<<"Theta is: "<<ThetaW[0]<<endl;
	cout<<"Weights are: ";
	for(int i=1;i<ThetaW.size();i++){
		cout<<ThetaW[i]<<" ";
	}
	cout<<endl;
}



int main(){
	take_input();
	int size =Vectors.size();
	cout<<N<<" "<<size<<endl;
	for(int i=0;i<size;i++){
		printvec(Vectors[i]);
	}
	cout<<"---------------------------------------";
		cout<<endl<<"---------------------------------------"<<endl;
	//printvec(addition(Vectors[2],Vectors[3]));
	RunPTA();
	return 0;
}
