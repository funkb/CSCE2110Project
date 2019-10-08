
#ifndef PORTER_STEM_H
#define PORTER_STEM_H


#include <iostream>
#include <vector>
#include <string>
#include <locale> /* Required to make words lowercase */

using namespace std;

class PorterStemmer{
	private:
		string b; /* Current Buffer */

		/*
		 * Building block functions, will help complete steps 1-5
		 */

		/* bool isConst (int)
		 * @param: int - index of character to check
		 * @return: returns if char is constanent
		 */
		bool isConst(int);

		/* bool endsWith (string)
		 * @param: string - string to check
		 * @return: returns if string matches end of current buffer
		 */
		bool endsWith(string);

		/* bool vowelInStem (int)
		 * @param: int - offset of #chars from back
		 * @return: return if there is a vowel between index 0 and offset(param)
		 */
		bool vowelInStem(int);

		/* bool constDouble (int)
		 * @param: int - index to check (int and int-1)
		 * @return: return if 2 constanents that are the same next to each other
		 */
		bool constDouble(int);

		/* bool cvc (int)
		 * @param: int - index to check (int, -1, -2)
		 * @return: return if chars match cvc pattern
		 */
		bool cvc(int);

		/* int calc_m ()
		 * @param:
		 * @return: returns int value (m) of a word.
		 */
		int calc_m();

		/* int calc_m (int)
		 * @param: int - offset from back (stem)
		 * @return: returns int value (m) of a word stem
		 */
		int calc_m(int);

		/* void setToString (string, int)
		 * @param: string - string to set buffer to
		 * 		   int - how far back from end of string to start the override
		 * @return: void
		 */
		void setToString(string,int);

		/* void replace (string, int)
		 * Same as setToString, only runs if m>0
		 * @return: void
		 */
		void replace(string,int);

		/* void cutBack (int)
		 * @param: int - where to start removing letters (from back)
		 * @return: void
		 */
		void cutBack(int);

		/* string getCurrentBuffer ()
		 * @return: returns current buffer
		 */
		string getCurrentBuffer();

		/* Step Functions */
		void step1ab();
		void step1c();
		void step2();
		void step3();
		void step4();
		void step5();


	public:
		PorterStemmer();

		/* string stemWord (string)
		 * @param: string - word to stem, gets moved into buffer
		 * @return: string - returns stemmed word.
		 */
		string stemWord(string);

		/* void printVector (vector<string>)
		 * @param: vector<string> - vector to print
		 * @return: void
		 */
		void printVector(vector<string>);

		/* void printVector (vector<vector<string>>, int)
		 * @param: vector<vector<string>> - a vector of all abstract vectors
		 * 				 int - the index of the abstract to print
		 * @return: void
		 */
		void printVector(vector<vector<string>>,int);



};

#endif
