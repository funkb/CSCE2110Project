#include <iostream>
#include <string>
#include <algorithm>

#include "porter_stem.h"
#include "readin.h"
#include "tfidf.h"
#include "cosinesimilarity.h"


using namespace std;

int main(){

	/*
	 * Darrin Pennington
	 * Reading and parsing in document
	 * Deleting punctuation and removing stopwords
	 */
	vector<string> stop;
	Read d;

	//parses in data and stopwords then erases words characters,symbols not needed for the rest of the program
	d.parseData();
	stop = d.parseStopwords();
	d.printFirstDoc(d.idNumvec, d.titlevec, d.authorvec, d.abstractvec);
	cout << endl;

/*`
	//Started Removing Titles from Abstracts (Avery)
	int DNCtitle = 0;	//Contains Title when DNCtitle = 0; Does Not Contain Title when DNCtitle = 1;
	for (int i=0; i<d.abstractvec.size(); i++)
	{
		DNCtitle = 0;
		for (int j=0; j<d.titlevec[i].length(); j++)
		{
			if (d.titlevec[i].at(j) != d.abstractvec[i].at(j)) //if it doesn't contain the title
			{
				//cout << d.titlevec[i].at(j) << " " << d.newAbstract[i].at(j) << endl;
				//cout << "Abstract Doesnt Contain Title" << endl;
				DNCtitle = 1;
			}
		}
		if (DNCtitle == 0) //if it does contain the tile
		{
			//cout << endl << "Abstract " << i << " Contains the Title" << endl;
			d.abstractvec[i].erase(0, d.titlevec[i].length()); //erases the tile from the abstract
		}
	}
	//Finished Removing Titles from Abstracts (Avery)
*/

	cout << "There are currently " << d.getCount() << " known stopwords." << endl;
	cout << endl;
	d.erase(d.abstractvec, stop, d.newAbstract);
	cout << endl << endl;



	/*
	 * Porter Stemming
	 * Brandon Funk
	 */

	PorterStemmer ps;
	vector<string> tokenized;
	vector<vector<string>> allVectors;

	int stemWordCount = 0;

	for(auto it=d.newAbstract.begin(); it != d.newAbstract.end(); ++it)
	{
		//cout << "\n=========================\nit*: " << *it << "\n===============================\n";
		stringstream sstream1(*it);
		string token;
		while(sstream1 >> token)
		{
			//cout << token << endl;
			tokenized.push_back(token);
		}
		//ps.printVector(tokenized);
		for(auto it2 = tokenized.begin(); it2 != tokenized.end(); ++it2)
		{

			string oldWord = *it2; //Track oldWord to compare with stemmed version, and update counter
			*it2 = ps.stemWord(*it2); //Stem word and overwrite current word in vector with result.

			//cout << oldWord << " > " << *it2 << endl;

		}
		allVectors.push_back(tokenized);
		tokenized.clear();
	}
	ps.printVector(allVectors, 0); //Print only first abstract

	/* Calculate # of uniquely stemmmed words */
	tokenized = allVectors.at(0); 	//Reset tokenized to first abstract vector
	sort(tokenized.begin(), tokenized.end());
	auto ind = unique (tokenized.begin(), tokenized.end()); //Create an iterator to the end of the 'unique' words vector.
	tokenized.resize( distance(tokenized.begin(), ind)); //Cut off the non unique words.
	cout << "Number of uniquely stemmed words: " << tokenized.size() << endl;

	tokenized.clear();




	/*
	 * Input Query from user.
	 * Brandon Funk
	*/
	string search;
	vector<string> newSearch;  //Stores cleansed and stemmed output when complete

	cout << "\nPlease input query of search terms seperated by a space: ";
	getline(cin, search);

	//Remove all whitespace and tokenize terms
	stringstream sstream1(search);
	string token;
	while(sstream1 >> token){
		newSearch.push_back(token);
	}

	/* Porter Stemming the search terms */
	for(auto it=newSearch.begin(); it != newSearch.end(); ++it){
		*it = ps.stemWord(*it);
	}
	/* newSearch is now a vector of porter stemmed search terms. */

	/*
	 * Calculating Cosine Similarity.
	 * Avery Berg
	*/

	vector<double> similarities {3, 5, 4, 1, 2}; //Vector of Cosine Similarities
	vector<double> sortedsimilarities;	//Vector of Cosine Similarities sorted in Descending Order

	//Placeholder until tf-idfs is complete
	vector<vector<float>> Placeholder_TFIDFs_Documents; //Placeholder for tf-idfs for Documents
	vector<float> Placeholder_TFIDFs_Query; //Placeholder for tf-idfs for query
	vector<vector<string>> Placeholder_Document_Words; //Placeholder Vector of Porter Stemmed Words from the Documents (NO REPEATS), Corresponding with tf-idf values vector
	vector<string> Placeholder_Query_Words; //Placeholder Vector of Porter Stemmed Words from the Query (NO REPEATS), Corresponding with tf-idf values vector

	for (int i=0; i<Placeholder_Document_Words.size(); i++) //Creating a Vector of Cosine Similarities for Each Document
	{
		//similarities.push_back(CalculateCosineSimilarity(Placeholder_Document_Words, Placeholder_Query_Words, Placeholder_TFIDFs_Documents, Placeholder_TFIDFs_Query, i));
	}

	sortedsimilarities = similarities;

	sort(sortedsimilarities.begin(), sortedsimilarities.end(), greater<double>());

	cout << "The top most similar documents are: " << endl;
	for (int i=0; i<Placeholder_Document_Words.size(); i++)
	{
		for (int j=0; j<Placeholder_Document_Words.size(); j++)
		{
			if (sortedsimilarities.at(i)==similarities.at(j))
			{
				cout << "   " << d.idNumvec.at(j) << fixed << setprecision(5) << sortedsimilarities.at(i) << endl;
			}
		}
	}

	return 0;
}
