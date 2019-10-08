#ifndef COSINESIMILARITY_H
#define COSINESIMILARITY_H


#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream> //DELETE LATER (FOR TESTING)
#include <iomanip>

using namespace std;



double CalculateCosineSimilarity(vector< vector<string>> documentwords, vector<string> querywords, vector< vector<float>> tfidfs, vector<float> query, int position);

#endif
