#include "porter_stem.h"

using namespace std;

//#define DEBUG

PorterStemmer::PorterStemmer(){ }

string PorterStemmer::getCurrentBuffer(){
	return b;
}

// Calculates the m factor of the buffered word
int PorterStemmer::calc_m(){
	int m=0;
	if(b.length() > 1) {
		unsigned int counter = 0;
		int cv_switch=-1; //0 = const || 1 = vowel
		while(counter < b.length()){
			if(isConst(counter)){
				if(cv_switch != 0 && cv_switch == 1)
					m++;
				cv_switch=0;
			}else{
				cv_switch=1;
			}
			counter++;
		}
	}
	return m;
}

int PorterStemmer::calc_m(int offset){ //Allows us to calculate m value of word if we know index of stem ending.
	int m=0;
	unsigned int counter = 0;
	int cv_switch=-1; //0 = const || 1 = vowel
	while(counter < b.length()-offset){
		if(isConst(counter)){
			if(cv_switch != 0 && cv_switch == 1)
				m++;
			cv_switch=0;
		}else{
			cv_switch=1;
		}
		counter++;
	}
	return m;
}

bool PorterStemmer::isConst(int i){
	switch (b.at(i)) {
		 case 'a': case 'e': case 'i': case 'o': case 'u':
			return false;
         case 'y':
			if(i==0){
				return true;
			} else {
				return !isConst(i-1);
			}
         default:
			return true;
      }
}


bool PorterStemmer::vowelInStem(int offset){
	for (unsigned int i = 0; i <= b.length()-offset-1; i++) {
		if (!isConst(i)) {
			return true;
		}
	}
    return false;
}


bool PorterStemmer::constDouble(int k){
	if (k < 1){
		return false;
	} else if (b.at(k) != b.at(k-1)){
		return false;
	} else {
		return isConst(k);
	}
}


bool PorterStemmer::cvc(int i) {
	if ( i<2 || !isConst(i) || isConst(i-1) || !isConst(i-2) ){
		return false;
	}
	if (b.at(i) == 'w' ||
	    b.at(i) == 'x' ||
	    b.at(i) == 'y')  {
		return false;
    }
    return true;
}


bool PorterStemmer::endsWith(string s){
	unsigned int length = s.length();
	if(length > b.length()) return false;

	string tempSub = b.substr(b.length() - length);
	if(tempSub.compare(s) == 0)
		return true;
	return false;
}


void PorterStemmer::setToString(string s, int offset){  //Offset is how far from back of string
	b = b.substr(0,b.length()-offset);
	b += s;
}

void PorterStemmer::cutBack(int numChar){
	setToString("",numChar);
}

//Only replace if not a null word
void PorterStemmer::replace(string s, int offset) {
	if (calc_m(offset) > 0){
		setToString(s,offset);
	}
}

void PorterStemmer::step1ab() {
	#ifdef DEBUG
	cout << "step1ab-1" << endl;
	#endif
	if (b.at(b.length()-1) == 's') {
		//cout << "Ends with s" << endl;
		if (endsWith("sses")) {
			cutBack(2);
		}else if (endsWith("ies"))  {
			cutBack(2);
		}else if (b.at(b.length()-1-1) != 's') {
			cutBack(1);
		}
	}
	#ifdef DEBUG
	cout << "step1ab-2" << endl;
	#endif
	if (endsWith("eed")) {
		//cout << "Ends with eed" << endl;
		if (calc_m() > 0) {
			cutBack(1);
		}
	} else if ((endsWith("ed") && vowelInStem(2)) || (endsWith("ing") && vowelInStem(3)) ) {
		#ifdef DEBUG
		cout << "step1ab-3" << endl;
		#endif

		if(endsWith("ed")) cutBack(2);
		else cutBack(3);

		#ifdef DEBUG
		cout << "step1ab-4" << endl;
		#endif

		char ch = b.at(b.length()-1);
		if (endsWith("at") || endsWith("bl") || endsWith("iz")) {
			b += "e";
		} else if (constDouble(b.length()-1) && !(ch == 'l' || ch == 's' || ch == 'z') ) {
			cutBack(1);
		}

		#ifdef DEBUG
		cout << "step1ab-5" << endl;
		#endif
		if(b.length() > 2){
			if (calc_m() == 1 && cvc(b.length()-1)) {
				b += "e";
			}
		}
  }
	#ifdef DEBUG
	cout << "step1ab-6" << endl;
	#endif
}


void PorterStemmer::step1c() {
	if (endsWith("y") && vowelInStem(1)) {
		setToString("i",1);
	}
}

void PorterStemmer::step2() {
    switch (b.at(b.length()-2)) {
		//cout << b.at(b.length()-2) << endl;
    case 'a':
      if (endsWith("ational")) {
        replace("ate",7);
        break;
      }
      if (endsWith("tional")) {
        replace("tion",6);
        break;
      }
      break;
    case 'c':
      if (endsWith("enci")) {
        replace("ence",4);
        break;
      }
      if (endsWith("anci")) {
        replace("ance",4);
        break;
      }
      break;
    case 'e':
      if (endsWith("izer")) {
        replace("ize",4);
        break;
      }
      break;
    case 'l':
      if (endsWith("abli")) {
        replace("able",4);
        break;
      }
      if (endsWith("alli")) {
        replace("al", 4);
        break;
      }
      if (endsWith("entli")) {
        replace("ent", 5);
        break;
      }
      if (endsWith("eli")) {
        replace("e", 3);
        break;
      }
      if (endsWith("ousli")) {
        replace("ous", 5);
        break;
      }
      break;
    case 'o':
      if (endsWith("ization")) {
        replace("ize",7);
        break;
      }
      if (endsWith("ation")) {
        replace("ate",5);
        break;
      }
      if (endsWith("ator")) {
        replace("ate", 4);
        break;
      }
      break;
    case 's':
      if (endsWith("alism")) {
        replace("al",5);
        break;
      }
      if (endsWith("iveness")) {
        replace("ive", 7);
        break;
      }
      if (endsWith("fulness")) {
        replace("ful", 7);
        break;
      }
      if (endsWith("ousness")) {
        replace("ous", 7);
        break;
      }
      break;
    case 't':
      if (endsWith("aliti")) {
        replace("al", 5);
        break;
      }
      if (endsWith("iviti")) {
        replace("ive", 3);
        break;
      }
      if (endsWith("biliti")) {
        replace("ble", 6);
        break;
      }
      break;
      }
}



void PorterStemmer::step3() {
  switch (b.at(b.length()-1)) {
  case 'e':
    if (endsWith("icate")) {
      replace("ic",5);
      break;
    }
    if (endsWith("ative")) {
      cutBack(5);
      break;
    }
    if (endsWith("alize")) {
      replace("al",5);
      break;
    }
    break;
  case 'i':
    if (endsWith("iciti")) {
      replace("ic",5);
      break;
    }
    break;
  case 'l':
    if (endsWith("ical")) {
      replace("ic",4);
      break;
    }
    if (endsWith("ful")) {
      cutBack(3);
      break;
    }
    break;
  case 's':
    if (endsWith("ness")) {
      cutBack(4);
      break;
    }
    break;
  }
}

void PorterStemmer::step4() {

	if(calc_m() > 1){
	switch (b.at(b.length()-2)) {
		case 'a':
			if (endsWith("al")){
				cutBack(2);
				break;
			}
			break;
		case 'c':
			if (endsWith("ance")) {
				cutBack(4);
				break;
			}
			if (endsWith("ence")) {
				cutBack(4);
				break;
			}
			break;
		case 'e':
			if (endsWith("er")) {
				cutBack(2);
				break;
			}
			break;
		case 'i':
			if (endsWith("ic")) {
				cutBack(2);
				break;
			}
			break;
		case 'l':
			if (endsWith("able")) {
				cutBack(4);
				break;
			}
			if (endsWith("ible")) {
				cutBack(4);
				break;
			}
			break;
		case 'n':
			if (endsWith("ant")) {
				cutBack(3);
				break;
			}
			if (endsWith("ement")) {
				cutBack(5);
				break;
			}
			if (endsWith("ment")) {
				cutBack(4);
				break;
			}
			if (endsWith("ent")) {
				cutBack(3);
				break;
			}
			break;
		case 'o':
			if (endsWith("ion") && (b.at(b.length()-4) == 's' || b.at(b.length()-4) == 't')) {
				cutBack(3);
				break;
			}
			if (endsWith("ou")) {
				cutBack(2);
				break;
			}
			break;
		case 's':
			if (endsWith("ism")) {
				cutBack(3);
				break;
			}
			break;
		case 't':
			if (endsWith("ate")) {
				cutBack(3);
				break;
			}
			if (endsWith("iti")) {
				cutBack(3);
				break;
			}
			break;
		case 'u':
			if (endsWith("ous")) {
				cutBack(3);
				break;
			}
			break;
		case 'v':
			if (endsWith("ive")) {
				cutBack(3);
				break;
			}
			break;
		case 'z':
			if (endsWith("ize")) {
				cutBack(3);
				break;
			}
			break;
		default:
			break;
		}
	}
}

void PorterStemmer::step5() {
	#ifdef DEBUG
		cout << "Step5-1" << endl;
	#endif
	if (b.at(b.length()-1) == 'e') {
		int m = calc_m(1);
		if (m > 1 || (m == 1 && !cvc(b.length() - 2) ) )
			cutBack(1);
	}
	#ifdef DEBUG
		cout << "Step5-2" << endl;
	#endif
	if (b.at(b.length()-1) == 'l' && constDouble(b.length()-1) && calc_m() > 1)
		cutBack(1);
}

string PorterStemmer::stemWord(string word){
	locale loc;

	for(int s = 0; s < word.length(); s++){
		word[s] = tolower(word[s],loc);
	}

	string newWord;
	for (int i = 0; i < word.length(); i++) {
		if (word[i] != ' ') {
			newWord += word[i];
		}
	}

	if(newWord.length() > 3)
		b = newWord;
	else
		return newWord;

	#ifdef DEBUG
		cout << "Step 1ab" << endl;
		step1ab();
		cout << "Step 1c" << endl;
		step1c();
		cout << "Step 2" << endl;
		step2();
		cout << "Step 3" << endl;
		step3();
		cout << "Step 4" << endl;
		step4();
		cout << "Step 5" << endl;
		step5();
	#endif
	#ifndef DEBUG
		step1ab();
		step1c();
		step2();
		step3();
		step4();
		step5();
	#endif
	return b;
}

void PorterStemmer::printVector(vector<string> vec){
	for(auto it = vec.begin(); it != vec.end(); ++it){
		cout << *it << " ";
	}
	cout << endl;
}

void PorterStemmer::printVector(vector<vector<string>> vec,int index){
	for(auto it = vec[index].begin(); it != vec[index].end(); ++it){
		cout << *it << " ";
	}
	cout << endl;

}
