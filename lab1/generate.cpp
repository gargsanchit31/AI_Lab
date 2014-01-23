#include <iostream>
#include <bitset>
#include <cmath>
#define _N 6
using namespace std;

void gen6bitevenParity(){
	bitset<_N> vec;
	int size=pow(2,_N);
	cout<<_N<<endl; 
	for(int i=0;i<size;i++){
		vec =i;
		if(vec.count()%2==0){
			cout<<1<<" ";
		}
		else{
			cout<<0<<" ";
		}
		for(int j=_N-1;j>=0;j--){
			cout<<vec[j]<<" ";
		}
		cout<<endl;
	}
}

int main(){
	gen6bitevenParity();
	return 0;
}
