#include "cosinesimilarity.h"

using namespace std;




/*
vector<string> document1words;  //vector of each word in document 1
vector<string> querywords;  //vector of each word in the query
vector<double> document1; //vector of the tf-idf values from document 1
vector<double> query; //vector of the tf-idf values from the query
*/

double CalculateCosineSimilarity(vector <vector<string>> documentwords, vector<string> querywords, vector <vector<float>> tfidfs, vector<float> query, int position)
{
  double cossim = 0;  //cosine similarity
  double numerator = 0;
  double denomA = 0;
  double denomB = 0;

  vector<double> tempdoc; //vector of the tf-idf values from document1 of the words that appear in document 1 and the query
  vector<double> tempquery; //vector of the tf-idf values from query of the words that appear in document 1 and the query

  vector<string> document1words = documentwords.at(position);  //vector of each word in document 1
  vector<float> document1 = tfidfs.at(position); //vector of the tf-idf values from document 1


  //Start Comparing the Words in the Query and the Document
  for (int i=0; i<document1words.size(); i++) //nested for loops to compare the words and get a list of words that appear in both
  {
    //cout << "working at i: " << i << endl;
    for (int j=0; j<querywords.size(); j++)
    {
      //cout << "working at j: " << j << endl;
      if (document1words.at(i)==querywords.at(j)) //if the word in the query and the document match, then put their corresponding tf-idf values into separate temporary vectors.
      {
        //cout << "Working at i: " << i << ", j: " << j << endl;
        tempdoc.push_back(document1.at(i));
        tempquery.push_back(query.at(j));
      }
    }
  }
  //Finished Comparing the Words in the Query and the Document
  //cout << "Finished Comparing the Words in the Query and the Document" << endl;

  //Start Calculating the Cosine Similarity Equation
  for (int i=0; i<tempdoc.size(); i++)
  {
    numerator += tempdoc.at(i) * tempquery.at(i); //numerator is the dot-product of A and B (the sum of the multiples of each corresponding tf-idf value)
  }
  for (int i=0; i<document1.size(); i++)
  {
    denomA += document1.at(i) * document1.at(i);  //denom A is the summation for A squared
  }
  for (int i=0; i<query.size(); i++)
  {
    denomB += query.at(i) * query.at(i);  //denom B is the summation for B squared
  }
  //cout << endl << "Numerator: " << numerator << endl;
  //cout << "denomA: " << denomA << endl;
  //cout << "denomB: " << denomB << endl << endl;

  cossim = numerator/(sqrt(denomA)*sqrt(denomB));
  //Finished Calculating the Cosine Similarity Equation

  //Start Emptying the Temporary Vectors
  while (!tempdoc.empty())
  {
    tempdoc.pop_back();
    tempquery.pop_back();
  }
  //Finished Emptying the Temporary Vectors

  return cossim; //Return the Cosine Similarity
}
