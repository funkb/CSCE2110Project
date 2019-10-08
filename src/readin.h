#ifndef READIN_H
#define READIN_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>
#include <regex>
using namespace std;

class Read
{
	 private:
        string id;
        string title;
        string author;
        string abstract;
		int count;

	public:
		//constructors
		Read();
		Read(string, string, string,string, int);
		//deconstructor
		~Read();
		//variables
		string getID()const;
		string getTitle()const;
		string getAuthor()const;
		string getAbstract()const;
		int getCount() const;

		void setID(string);
		void setTitle(string);
		void setAuthor(string);
		void setAbstract(string);
		void setCount(int);

		//class functions
		void print(vector<string> &a,
				   vector<string> &b,
				   vector<string> &c,
				   vector<string> &d);  //prints all docs

        void parseData();	//parses data
		void printFirstDoc(vector<string> &a,
						   vector<string> &b,
						   vector<string> &c,
						   vector<string> &d); // prints first document

		vector<string> parseStopwords(); // stores stopwords

		void erase(vector<string> &a,
				   vector<string> &b,
				   vector<string> &c); // deletes data needed

		void printOnePart_firstdoc(vector<string> &a);

		//vectors to store
		vector<string>newAbstract; //vector that stores new abstract
		vector<string>stopwords; //vector to store stopwords
		vector<string>idNumvec; //vector to store ids
		vector<string>titlevec; //vector to store titles
		vector<string>authorvec; //vector to store authors
		vector<string>abstractvec; //vector to store abstracts

};



#endif
