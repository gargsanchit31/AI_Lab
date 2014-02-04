#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <fstream>
using namespace std;

vector<string> store;

//function declarations
vector<string> removeDelimiter(string str1);


/*
*fuction to read words & store them in a vector from file
*/
void fileReading(string filepath)
{
	string segment;
	ifstream file (filepath.c_str());
  	if (file.is_open())
  	{
    	while ( getline (file,segment) )
    	{
    	  	vector<string> v = removeDelimiter(segment);

    	  	for(int i=0; i<v.size() ;i++)
    	  	{
    	  		store.push_back(v[i]);
    	  	}

    	}
   	 file.close();
  	}
}


/*
* removes delimiters from string 
*/
vector<string> removeDelimiter(string str1)
{
	vector<string> v;
	char * s = new char[str1.length() + 1];	
	strcpy(s,str1.c_str());
	
	//cout<<": "<<str1<<endl;

 	char* pch=NULL;
  	pch = strtok (s,"@~`!#$%^&*()_+=\\|\t\n\v\f\r[{}]| ,.-:;?/><\"");
  	while (pch != NULL)
  	{
  		string input=pch;
  		transform(input.begin(), input.end(), input.begin(), (int(*)(int))tolower);


  		//special case handling : ignore one length string, first character should not be ' & any number
  		if(input[0] !='\''  && input.length()!=1   && !(input[0]<58 && input[0]>47))
  		{
  			v.push_back(input);	
  		}
  			
 	  pch = strtok (NULL, "@~`!#$%^&*()_+=\\|\t\n\v\f\r[{}]| ,.-:;?/><\"");
  	}
  	return v;

  }


//given a sentence return an input boolean vector
vector<bool> createVector(string s)
{
	vector<string> v = removeDelimiter(s);
	vector<bool>  output(store.size(), 0);
	vector<string>::iterator it;

	for(int i=0; i<v.size();i++)
	{
		for(int j=0;j<store.size();j++)
		{
			if(store[j]==v[i])
			{
				output[j]=1;
				break;
			}
		}

	}

	return output;
}



int main()
{
	//reading all words from files and storing in a global vector
	fileReading("TweetsCorpus/twitter_positive");
	fileReading("TweetsCorpus/twitter_negative");
	fileReading("TweetsCorpus/twitter_objective");

	//sorting the vector
	sort (store.begin(), store.end());

	//removing the duplicates
	store.erase( unique( store.begin(), store.end() ), store.end() );


	string p = "yummmmmy yeah%above"; 

	vector<bool> v= createVector(p);
	for(int i=0;i<v.size();i++)
	{
		cout<<v[i]<<endl;
	}


	return 0;
}