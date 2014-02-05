#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <fstream>
using namespace std;

vector<string> store;


string file1="TweetsCorpus/twitter_positive";
string file2="TweetsCorpus/twitter_negative";
string file3="TweetsCorpus/twitter_objective";
string truthtable ="TweetsCorpus/truthtable";

//function declarations
vector<string> removeDelimiter(string str1);


/*
* fuction to read words & store them in a vector from file
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


/*
*	create a  boolean vector of given sentence
*/
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

/*
* create a truthtable
*/
void crateTruthtable(string filepath, int fileno)
{
	string segment;
	ifstream file (filepath.c_str());
	fstream writefile;
  writefile.open(truthtable.c_str(), fstream::out | fstream::app);

	
  	if (file.is_open())
  	{
    	while ( getline (file,segment) )
    	{
    	  	vector<bool> v= createVector(segment);

    	  	if(fileno == 1)
    	  	{
    	  		writefile<<1<<" "<<0<<" "<<0<<" ";
    	  	}
    	  	else if(fileno==2)
    	  	{
    	  		writefile<<0<<" "<<1<<" "<<0<<" ";
    	  	}
    	  	else if(fileno==3)
    	  	{
    	  		writefile<<0<<" "<<0<<" "<<1<<" ";
    	  	}
    	  	else
    	  	{
    	  		cout<<"fileno/output not specified in file"<<endl;
    	  	}
          cout<<"store : "<<store.size()<<endl;
          cout<<"vector : "<<v.size()<<endl;
    	  	for(int i=0; i< v.size();i++)
    	  	{
    	  		writefile<<v[i]<<" ";
    	  	}
    	  	writefile<<endl;

    	}
    
   	 file.close();
  	
	writefile.close();  
	}
}

int main()
{
	//reading all words from files and storing in a global vector
	fileReading(file1);
	fileReading(file2);
	fileReading(file3);

	//sorting the vector
	sort (store.begin(), store.end());

	//removing the duplicates
	store.erase( unique( store.begin(), store.end() ), store.end() );

	//creating truthtable
	crateTruthtable(file1, 1);
	crateTruthtable(file2, 2);
	crateTruthtable(file3, 3);
	


	return 0;
}