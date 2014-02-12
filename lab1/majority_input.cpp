#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

bitset<5> store;



int main()
{
	for(int i=0;i<32;i++)
	{
			store = i;
			int count=0;
			
			for(int j=0; j<5;j++)
			{
				if(store[j]==1)
				{
					count++;
				}
			}
			
			
			if(count>2)
			{
				cout<<1<<" ";
			}
			else
			{
				cout<<0<<" ";
			}
			
			for(int j=0; j<5;j++)
			{
				cout<<store[j]<<" ";
			}
			cout<<endl;
			
	}
	return 0;
}


