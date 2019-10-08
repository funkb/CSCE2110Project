#include"readin.h"


using namespace std;
//constructors
Read::Read()
{

}
Read::Read(string newAuthor,string newTitle, string newID, string newAbstract, int newCount)
{
	id = newID;
	title = newTitle;
	author = newAuthor;
	abstract = newAbstract;
	count = newCount;
}
//deconstructor
Read::~Read()
{

}
//gets variables
string Read::getID()const
{
	return id;
}
string Read::getAuthor() const
{
	return author;
}
string Read::getTitle()const
{
	return title;
}
string Read::getAbstract()const
{
	return abstract;
}
int Read::getCount() const
{
	return count;
}

//sets variables
void Read::setID(string newID)
{
	id = newID;
}
void Read::setTitle(string newTitle)
{
	title = newTitle;
}
void Read::setAuthor(string newAuthor)
{
	author = newAuthor;
}
void Read::setAbstract(string newAbstract)
{
	abstract = newAbstract;
}
void Read::setCount(int newCount)
{
	count = newCount;
}

//parse in and store data
void Read::parseData()
{
         ifstream fin; //ifstream for file

        string filename,word,w,x,y,z,temp; //variables


        cout <<"Which file would you like to read from:";
        getline(cin,filename); //gets filename in string

        fin.open(filename); //open file

        //check if file exists

        if(fin.fail())
        {
                cerr << "COULD NOT OPEN FILE" << endl;
                exit(1); // exits if can't open file
        }

        getline(fin,word);

        while(!fin.eof())//program runs until end of file
        {
                //find ID and stores it
                if(word.find(".I") != string::npos)
                {
                        w = "";//initalizes string to zero
                        w += word.substr(3,word.size()-1);//concatenates string

                        setID(w);
                        idNumvec.push_back(getID());


                }

        getline(fin,word);
                //finds title and stores it
                if(word == ".T")
                {

        				getline(fin,word);
								x = "";//sets stringto zero
                        while(word.find(".A") == string::npos)
                        {
                               // x = "";
                                x+=word + " ";//concatenates string
        										getline(fin,word);

                         }


				setTitle(x);

                                titlevec.push_back(getTitle());

                }
        getline(fin,word);
        //finds author then stores it
        y = "";//sests string equal to zero
        y+=word;//concatenates
        setAuthor(y);
        authorvec.push_back(getAuthor());
        getline(fin,word);
                //finds abstract and then stores it
                if(word == ".W")
                {       z = "";// sets string equal to zero
        getline(fin,word);
			//runs while string finds .I and isn't end of file
			/*
                        while(word.find(".I") == string::npos && !fin.eof())
                        {
                                z += word;// concatenates

                                 getline(fin,word);

                        }
                                setAbstract(z);
                                abstractvec.push_back(getAbstract());
				*/
			 while(word.find(".I") == string::npos && !fin.eof())
				{
					//string temp;
					z+= word + " ";

					getline(fin,word);
				}
			 		setAbstract(z);
					 abstractvec.push_back(getAbstract());

                }
        }
        fin.close(); // close file;


}
//print only one of the vectors (id vec, title vec, author vec, abstract vec
void Read::printOnePart_firstdoc(vector<string> &a)
{
		for(unsigned int i = 0; i < 1; i++)
		{
			cout << a[i] << endl;
		}
}
//prints first documen
void Read::printFirstDoc(vector<string> &a,vector<string> &b,vector<string> &c, vector<string> &d)
{
		/* Can technically use int i in all loops, since declared in a different scope 10/1/19-Brandon*/
        for(unsigned int i = 0; i < 1; i++)  /* changed var<1 to var<vec.size() so it will print all of the vector instead of just first term 10/1/19-Brandon */ //changed back to 1 10/2/19-Darrin
        {
                cout << "ID:" << endl << a[i] << endl;
        }
        for(unsigned int j = 0; j < 1; j++)
        {
                cout << "Title:" << endl << b[j] << endl;
        }
        for(unsigned int k = 0; k < 1;k++)
        {
                cout << "Author:" << endl << c[k] << endl;
        }
        for(unsigned int l = 0; l < 1;l++)
        {
                cout << "Abstract:" << endl << d[l] << " " << endl;
        }


}
//print all
void Read::print(vector<string> &a, vector<string> &b, vector<string> &c, vector<string> &d)
{


        for(unsigned int i = 0; i < a.size(); i++)
        {
                cout << "ID#" << i+1 << endl << a[i] << endl;
        }
        for(unsigned int j = 0; j < b.size(); j++)
        {
                cout << "Title#" << j+1 << endl << b[j] << endl;
        }
        for(unsigned int k = 0; k < c.size();k++)
        {
                cout << "Author#" << k+1 << endl <<  c[k] << endl;
        }
        for(unsigned int l = 0; l < d.size();l++)
        {
                cout << "Abstract#" << l+1 << endl << d[l] << " " << endl;
        }
}
//stores stopwords
vector<string> Read::parseStopwords()
{
	vector<string> a;
	string stop,stopfile;
  	ifstream din;

	cout <<"Enter stopword file:";
    getline(cin,stopfile);

    din.open(stopfile);
	//checks if file exists
    if(din.fail())
    {
            cerr << "COULD NOT FIND FILE" << endl;
            exit(1);
    }
    getline(din,stop);
    count=0;//initializes count to zero
	//populates stopwords vector
    while(!din.eof())
    {
	       getline(din,stop);
           a.push_back(stop);
           count++;//adds 1 everytime it comes across stopword
    }

	return a;

}
//cleans up vector
void Read::erase(vector<string> &a,vector<string> &b, vector<string> &c)
{
	/*
	Brandon's edit for string cleansing
	*/

	/*   Replaces lines 260-724

								//^ matches inverse of a-z and A-Z
	//Could potentially use reg("[^a-zA-Z]") but it removes whitespace as well, which we don't want yet.


	regex reg ("[0-9!@#$^&*()_+-=/.,?><';:}{\|}\']");
	for(auto it = a.begin(); it != a.end(); ++it)
		*it = regex_replace(*it,reg,"");
			//regex_replace(string startingStr,std::regex whatToFilter,string setTo)



	*/
	string del8 = "."; // stores . in del
	string del2 = ",";//stores , in del2
		//delete period

		for_each(a.begin(),a.end(), [&](string &period)
			{
				while(period.find(del8) != string::npos)
				{
				#ifdef REPLACE_PERIOD
				if(period.find(del8) != string::npos)
				{
					period.replace(0,period.length(),period.length(),' ');
				}
				#else
				if(period.find(del8) != string::npos)
				{
					period.replace(period.find(del8),del8.length(),del8.length(),' ');
				}
				#endif
				}
			}

			);
		// delete commas
		 for_each(a.begin(),a.end(), [&](string &comma)
                        {
                                while(comma.find(del2) != string::npos)
                                {
                                #ifdef REPLACE_COMMA
                                if(comma.find(del2) != string::npos)
                                {
                                        comma.replace(0,comma.length(),comma.length(),' ');
                             *it   }
                                #else
                                if(comma.find(del2) != string::npos)
                                {
                                        comma.replace(comma.find(del2),del2.length(),del2.length(),' ');
                                }
                                #endif
                                }
                        }

                        );
		 //delete 's
		 string del3 = "'s"; // stores 's in del3
		  for_each(a.begin(),a.end(), [&](string &help)
                        {
                                while(help.find(del3) != string::npos)
                                {
                                #ifdef REPLACE_HELP
                                if(help.find(del3) != string::npos)
                                {
                                        help.replace(0,help.length(),help.length(),' ');
                                }
                                #else
                                if(help.find(del3) != string::npos)
                                {
                                        help.replace(help.find(del3),del3.length(),del3.length(),' ');
                                }
                                #endif
                                }
                        }

                        );
		  //deletes question marks
		  string del4 = "?"; // sets del4 = to question mark

		   for_each(a.begin(),a.end(), [&](string &question)
                        {
                                while(question.find(del4) != string::npos)
                                {
                                #ifdef REPLACE_QUESTION
                                if(question.find(del4) != string::npos)
                                {
                                        question.replace(0,question.length(),question.length(),' ');
                                }
                                #else
                                if(question.find(del4) != string::npos)
                                {
                                        question.replace(question.find(del4),del4.length(),del4.length(),' ');
                                }
                                #endif
                                }
                        }

                        );

		//deletes dashes
		   string del5 = "-";
		    for_each(a.begin(),a.end(), [&](string &dash)
                        {
                                while(dash.find(del5) != string::npos)
                                {
                                #ifdef REPLACE_DASH
                                if(dash.find(del5) != string::npos)
                                {
                                        dash.replace(0,dash.length(),dash.length(),' ');
                                }
                                #else
                                if(dash.find(del5) != string::npos)
                                {
                                        dash.replace(dash.find(del5),del5.length(),del5.length(),' ');
                                }
                                #endif
                                }
                        }

                        );
		    //deletes foward slashes
		    string del6 = "/";
		     for_each(a.begin(),a.end(), [&](string &foward)
                        {
                                while(foward.find(del6) != string::npos)
                                {
                                #ifdef REPLACE__FOWARD
                                if(foward.find(del6) != string::npos)
                                {
                                        foward.replace(0,foward.length(),foward.length(),' ');
                                }
                                #else
                                if(foward.find(del6) != string::npos)
                                {
                                        foward.replace(foward.find(del6),del6.length(),del6.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes zeros
		       string a0 = "0";
                     for_each(a.begin(),a.end(), [&](string &zero)
                        {
                                while(zero.find(a0) != string::npos)
                                {
                                #ifdef REPLACE__ZERO
                                if(zero.find(a0) != string::npos)
                                {
                                        zero.replace(0,zero.length(),zero.length(),' ');
                                }
                                #else
                                if(zero.find(a0) != string::npos)
                                {
                                        zero.replace(zero.find(a0),a0.length(),a0.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
			//deletes ones
		      string a1 = "1";
                     for_each(a.begin(),a.end(), [&](string &one)
                        {
                                while(one.find(a1) != string::npos)
                                {
                                #ifdef REPLACE__ONE
                                if(one.find(a1) != string::npos)
                                {
                                        one.replace(0,one.length(),one.length(),' ');
                                }
                                #else
                                if(one.find(a1) != string::npos)
                                {
                                        one.replace(one.find(a1),a1.length(),a1.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes twos
		      string a2 = "2";
                     for_each(a.begin(),a.end(), [&](string &two)
                        {
                                while(two.find(a2) != string::npos)
                                {
                                #ifdef REPLACE__TWO
                                if(two.find(a2) != string::npos)
                                {
                                        two.replace(0,two.length(),two.length(),' ');
                                }
                                #else
                                if(two.find(a2) != string::npos)
                                {
                                        two.replace(two.find(a2),a2.length(),a2.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes threes
		      string a3 = "3";
                     for_each(a.begin(),a.end(), [&](string &three)
                        {
                                while(three.find(a3) != string::npos)
                                {
                                #ifdef REPLACE__THREE
                                if(three.find(a3) != string::npos)
                                {
                                        three.replace(0,three.length(),three.length(),' ');
                                }
                                #else
                                if(three.find(a3) != string::npos)
                                {
                                        three.replace(three.find(a3),a3.length(),a3.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes fours
		      string a4 = "4";
                     for_each(a.begin(),a.end(), [&](string &four)
                        {
                                while(four.find(a4) != string::npos)
                                {
                                #ifdef REPLACE__FOUR
                                if(four.find(a4) != string::npos)
                                {
                                        four.replace(0,four.length(),four.length(),' ');
                                }
                                #else
                                if(four.find(a4) != string::npos)
                                {
                                        four.replace(four.find(a4),a4.length(),a4.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes fives
			 string a5 = "5";
                     for_each(a.begin(),a.end(), [&](string &five)
                        {
                                while(five.find(a5) != string::npos)
                                {
                                #ifdef REPLACE__FIVE
                                if(five.find(a5) != string::npos)
                                {
                                        five.replace(0,five.length(),five.length(),' ');
                                }
                                #else
                                if(five.find(a5) != string::npos)
                                {
                                        five.replace(five.find(a5),a5.length(),a5.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes sixes
		      string a6 = "6";
                     for_each(a.begin(),a.end(), [&](string &six)
                        {
                                while(six.find(a6) != string::npos)
                                {
                                #ifdef REPLACE__SIX
                                if(six.find(a6) != string::npos)
                                {
                                        six.replace(0,six.length(),six.length(),' ');
                                }
                                #else
                                if(six.find(a6) != string::npos)
                                {
                                       	six.replace(six.find(a6),a6.length(),a6.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes sevens
		      string a7 = "7";
                     for_each(a.begin(),a.end(), [&](string &seven)
                        {
                                while(seven.find(a7) != string::npos)
                                {
                                #ifdef REPLACE__SEVEN
                                if(seven.find(a7) != string::npos)
                                {
                                        seven.replace(0,seven.length(),seven.length(),' ');
                                }
                                #else
                                if(seven.find(a7) != string::npos)
                                {
                                        seven.replace(seven.find(a7),a7.length(),a7.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes eights
		      string a8 = "8";
                     for_each(a.begin(),a.end(), [&](string &eight)
                        {
                                while(eight.find(a8) != string::npos)
                                {
                                #ifdef REPLACE__EIGHT
                                if(eight.find(a8) != string::npos)
                                {
                                        eight.replace(0,eight.length(),eight.length(),' ');
                                }
                                #else
                                if(eight.find(a8) != string::npos)
                                {
                                        eight.replace(eight.find(a8),a8.length(),a8.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     //deletes nines
		      string a9 = "9";
                     for_each(a.begin(),a.end(), [&](string &nine)
                        {
                                while(nine.find(a9) != string::npos)
                                {
                                #ifdef REPLACE__NINE
                                if(nine.find(a9) != string::npos)
                                {
                                        nine.replace(0,nine.length(),nine.length(),' ');
                                }
                                #else
                                if(nine.find(a9) != string::npos)
                                {
                                       	nine.replace(nine.find(a9),a9.length(),a9.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     // deletes (
		      string a10 = "(";
                     for_each(a.begin(),a.end(), [&](string &p)
                        {
                                while(p.find(a10) != string::npos)
                                {
                                #ifdef REPLACE__P
                                if(p.find(a10) != string::npos)
                                {
                                        p.replace(0,p.length(),p.length(),' ');
                                }
                                #else
                                if(p.find(a10) != string::npos)
                                {
                                        p.replace(p.find(a10),a10.length(),a10.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		     // deletes )
		      string a11 = ")";
                     for_each(a.begin(),a.end(), [&](string &pd)
                        {
                                while(pd.find(a11) != string::npos)
                                {
                                #ifdef REPLACE__PD
                                if(pd.find(a11) != string::npos)
                                {
                                        pd.replace(0,pd.length(),pd.length(),' ');
                                }
                                #else
                                if(pd.find(a11) != string::npos)
                                {
                                        pd.replace(pd.find(a11),a11.length(),a11.length(),' ');
                                }
                                #endif
                                }
                        }

                       );
		 //deletes =
		 string a12 = "=";
     for_each(a.begin(),a.end(), [&](string &equal)
        {
                while(equal.find(a12) != string::npos)
                {
                #ifdef REPLACE__EQUAL
                if(equal.find(a12) != string::npos)
                {
                        equal.replace(0,equal.length(),equal.length(),' ');
                }
                #else
                if(equal.find(a12) != string::npos)
                {
                        equal.replace(equal.find(a12),a12.length(),a12.length(),' ');
                }
                #endif
                }
        }

       );
		     //deletes +
			 string a13 = "+";
       for_each(a.begin(),a.end(), [&](string &plus)
          {
                  while(plus.find(a13) != string::npos)
                  {
                  #ifdef REPLACE__PLUS
									if(plus.find(a13) != string::npos)
                  {
                          plus.replace(0,plus.length(),plus.length(),' ');
                  }
                  #else
                  if(plus.find(a13) != string::npos)
                  {
                          plus.replace(plus.find(a13),a13.length(),a13.length(),' ');
                  }
                  #endif
                  }
          }

         );
		     //deletes -
			 string a14 = "-";
       for_each(a.begin(),a.end(), [&](string &sub)
          {
                  while(sub.find(a14) != string::npos)
                  {
                  #ifdef REPLACE__SUB
                  if(sub.find(a14) != string::npos)
                  {
                          sub.replace(0,sub.length(),sub.length(),' ');
                  }
                  #else
                  if(sub.find(a14) != string::npos)
                  {
                          sub.replace(sub.find(a14),a14.length(),a14.length(),' ');
                  }
                  #endif
                  }
          }

         );
		     // deletes *
			 string a15 = "*";
       for_each(a.begin(),a.end(), [&](string &mult)
          {
                  while(mult.find(a15) != string::npos)
                  {
                  #ifdef REPLACE__MULT
                  if(mult.find(a15) != string::npos)
                  {
                          mult.replace(0,mult.length(),mult.length(),' ');
                  }
                  #else
                  if(mult.find(a15) != string::npos)
                  {
                          mult.replace(mult.find(a15),a15.length(),a15.length(),' ');
                  }
                  #endif
                  }
          }

         );
			
		c = a;	// set c (new vector) = to modified old vector
		vector<string> temp; // temp vector for inner loop of vector of vector
		vector<vector<string> > tokAb; // vector to hold vector of vector
		// use string stream to tokenize abstract ot read in word by word
		for(unsigned int d = 0; d < c.size();d++)
		{
		stringstream ss(c.at(d)); // declare string stream
		string tok; //string to hold each word
		//while loop to get each line until space
		while(getline(ss,tok,' '))
		{
			// deletes string if found in stopword vector
		 	bool found = false;
			if(tok == "a")
			{
				continue;
			}
			for(unsigned int i = 0; i < b.size(); i++)
			{
				if(tok == b.at(i))
				{
					//breaks out of loop if found equals true
					found = true;
					break;

				}
			}

			if(found == false)
			{
				//if found equals false it pushes tok into temperorary vec
				temp.push_back(tok);

			}
		}

		tokAb.push_back(temp); // pushes temp vector into vector of vector
		temp.clear();//clears temp vec
		}
		vector<string> tempvec2;//temp vec to turn vector of vector back into vector of strings
		//nested loop to concatenate inner loop into a big string
		for(unsigned int i = 0; i < tokAb.size();i++)
		{
			string temp = ""; //set temp string to zero
			for(unsigned int j = 0; j < tokAb.at(i).size();j++)
			{
				temp = temp + tokAb.at(i).at(j) + " "; //adds each word to temp string
			}
			tempvec2.push_back(temp); //pushes temp string back into vector of strings

		}


		c = tempvec2; // initializes temp vec to newAbstract
		/*
		vector<string>tempvec3;
		for(unsigned int i = 0; i < c.size(); i++)
		{
			stringstream dp(c.at(i));
			string temp_word;

			while(getline(dp,temp_word, ' '))
			{
				tempvec3.push_back(temp_word);
			}
		}*/

		for(unsigned int i = 0; i < 1; i++)
		{
			cout << c[i] << endl;
		}


}
