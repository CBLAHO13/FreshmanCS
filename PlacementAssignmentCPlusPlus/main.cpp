/* This program will calculate readability scores for a given text file.
  Place the text file in the working directory.
  Run the program.
  Get results. 
  
  First version written in Java. This version in C++. 

  ****CHANGE LOG***
  - Different language. 
  - Fix errors caught by J.Popyack:
		" You aren't doing your rounding to 2 decimal places correctly - 
		First of all, it doesn't round, it truncates.  Next, because of 
		integer division, you're losing the last 2 decimal places."
 - Fixed the error I was "seeing" when my code didn't support more than two 
	vowels in a row. 
- Refined the algorithm for character replacement. 

  Copyright Colleen Blaho 2013. Copyleft also Colleen Blaho 2013. 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#include <vector>
#include <cctype>
#include <regex>

using namespace std;

//PROTOYPE
void lineReader(vector<string> &linesInFile, string filename, ifstream &myFile); 
void lineAnalyzer(vector<string> contents, string input);
double vowelCounter (vector<string> contents, double vowelCount);
double sentenceCounter(vector<string> contents, double sentenceCount, double &wordCount);
void FlechReadingEasePrint(double rawScore, string filename);
void FlechKincaidPrint(double rawScore);

int main()
{
	string filename;
	ifstream myFile; //opening the "scanner"
	cout << "Enter a file name or QUIT to quit." << endl;
	cin >> filename;
	string sentinel = "QUIT";
	vector<string> linesInFile; 
	while (filename != sentinel && filename.size() !=0)
		if(filename.compare(sentinel) != 0 && filename.size() != 0){
			lineReader(linesInFile, filename, myFile);
			lineAnalyzer(linesInFile, filename);
			cout << "Analysis finished. Type a new filename or QUIT." << endl;
			linesInFile.clear();
			cout << "Enter file name." << endl;
			cin >> filename;
		}
		
			if (myFile.is_open()){ //just to make sure it's closed
				myFile.close();}
			cout << "QUITTING PROGRAM" << endl;
			return 0;

}

void lineReader(vector<string> &linesInFile, string filename, ifstream &myFile) 
{
	string line;
	string word;
	myFile.open(filename);

	if (myFile.is_open())
	{
		//while(! myFile.eof())
		//{ 
		
			//cout << endl << "FILE OPEN" << endl;
			stringstream lineStream;
			//cout << endl << "linestream" << endl;
			while(getline(myFile, line))
			{
				lineStream << line; 
				//cout << endl << "line in linestream" << endl;
				while(getline(lineStream,word, ' '))
				{ 
					linesInFile.push_back(word);
					//cout << word << endl << "WORD ADDED" << endl;
				}
				lineStream.clear();
			}
	}
	else 
	{
		cout << "Your File could not be found!" << endl;
		int index = filename.find(".");
			if (index < 0)
				index = filename.length();
		string fileExtension = filename.substr(index);
		string correctExtension = ".txt";
		if (fileExtension.compare(correctExtension) != 0)
		{
			cout<< endl << "You have the wrong file extension on this file. Try again!"<< endl;
		}
		else { //file is in wrong place
			cout << "Ensure the file name is in this directory, and its name is spelled correctly." << endl;
		}
	}
	myFile.close();
}
void lineAnalyzer(vector<string> contents, string input)
{ 
	//cout << "BEFORE SIZE CHECKER" << endl;
	//cout << contents.size();
	
	if (contents.size() != 0)
	{
		cout << endl << "File Found.\nAnalyzing..." << endl;
		double wordCount = contents.size();
		for (unsigned int i =0; i<= contents.size() -1; i++) {
				transform(contents[i].begin(), contents[i].end(), contents[i].begin(), tolower) ;//make sure capitalized vowels are grabbed too. from http://www.cplusplus.com/forum/general/837 
				contents[i] = regex_replace(contents[i], regex("[^a-z\\.!\\?;:/]+"), ""); //remove special characters because they're stupid
				contents[i] = regex_replace(contents[i], regex("e$"), " ");//scrub out ending e chars
				contents[i] = regex_replace(contents[i], regex("e\\.$"), "."); //max mattes made this. he wants credit.
				contents[i] = regex_replace(contents[i], regex("[aeiouy]+"), "a"); //scrub out "independent vowels" to count them better, replace with model syllable
				contents[i] = regex_replace(contents[i], regex("[ -]+"), ""); //are there multiple spaces and dashes that will confuse the counter?
				contents[i] = regex_replace(contents[i], regex("^[^aeiouy]+$"), "a"); //scrub out words with no vowels, replace with model syllable
				
				//cout << contents[i] << endl;
			}
		double vowelCount = 0;
		vowelCount = vowelCounter(contents, vowelCount);
		//cout << vowelCount;
		double sentenceCount = 0;
		sentenceCount = sentenceCounter(contents, sentenceCount, wordCount);
		//cout << "Words " << wordCount << endl <<"Sentences " << sentenceCount << endl << "Vowels " << vowelCount << endl;
		double FRES = 206.835 - 84.6 * (vowelCount) / (wordCount) - 1.015 * (wordCount) / (sentenceCount);
		double FKRA = 11.8* (vowelCount) / (wordCount) + 0.39 * (wordCount) / (sentenceCount) - 15.59;
		FlechReadingEasePrint(FRES, input); 
		FlechKincaidPrint(FKRA);
		}
	
	else { 
		cout << "File must contain valid text.\n";
	}
}

double vowelCounter (vector<string> contents, double vowelCount) {
	string s;
	for (unsigned int i = 0; i <= contents.size() - 1; i++){ 
		 s = contents[i];
			for (unsigned int j = 0; j < s.size(); j++) { //count important vowels by iterating through each string
				char c = s[j];
				//cout << c;
			    if (c=='a') // a is the only vowel we have now!
			    	vowelCount++;    
			}	
		}
		 return vowelCount;	
}

double sentenceCounter(vector<string> contents, double sentenceCount, double &wordCount) { //also does sanity checks for word count 
	string s;
	for (unsigned int i = 0; i <= contents.size() - 1; i++){ 
		 s = contents[i];
		 if(contents[i].size() == 0)
			 wordCount--;
			for (unsigned int j = 0; j < s.size(); j++) { //count important vowels by iterating through each string
				char c = s[j];
				//cout << c;
			     if (c=='.')
			    	sentenceCount++; 
			    else if( c==':')
			    	sentenceCount++;
			    else if(c==';')
			    	sentenceCount++;
			    else if(c=='?')
			    	sentenceCount++;
			    else if (c=='!')
			    	sentenceCount++;    
				else if (c == '/') //did someone stick two words together with a slash to fool us?
					wordCount++;
				else if (c == ' ') //did a space word sneak through?
					wordCount--;
			}	
		}
	if (sentenceCount == 0)//prevent a 0/0 occurrence. by default, it is one sentence since the text file is not blank.
	{
		sentenceCount = 1;
	}
		 return sentenceCount;
}

void FlechReadingEasePrint(double rawScore, string filename){
		string gradeLevel = "";
		//table given to us in the assignment
		if (rawScore > 91)
			gradeLevel = "a fifth grade or less";
		else if (rawScore > 81)
			gradeLevel = "a sixth grade";
		else if (rawScore > 71)
			gradeLevel = "a seventh grade";
		else if (rawScore > 66)
			gradeLevel = "an eighth grade";
		else if (rawScore > 61)
			gradeLevel = "a ninth grade";
		else if (rawScore > 51)
			gradeLevel = "a high school student";
		else if (rawScore > 31)
			gradeLevel = "a college student";
		else if (rawScore > 0)
			gradeLevel = "a college graduate";
		else
			gradeLevel = "a law school graduate";
		
		//rawScore = ((int)((rawScore + .5) *100)) / 100; //rounding with typecasts!
		cout << "\nThe file \"" << filename << "\" has Flesch Reading Ease Score index of " << rawScore << ".\n"
					 << " It requires " << gradeLevel << " education to read."<<endl;
}
	
void FlechKincaidPrint(double rawScore){
		int rawScoreInt = (int)rawScore;
		string gradeLevel;
		//table given to us in the assignment
		if (rawScoreInt > 13 || rawScoreInt == 13)
			gradeLevel = "a higher education";
		else if (rawScoreInt == 12)
			gradeLevel = "a senior";
		else if (rawScoreInt == 11)
			gradeLevel = "a junior";
		else if (rawScoreInt == 10)
			gradeLevel = "a sophmore";
		else if (rawScoreInt == 9)
			gradeLevel = "a freshman";
		else if (rawScoreInt == 8)
			gradeLevel = "an eighth grade";
		else if (rawScoreInt == 7)
			gradeLevel = "a seventh grade";
		else if (rawScoreInt == 6)
			gradeLevel = "a sixth grade";
		else if (rawScoreInt == 5)
			gradeLevel = "a fifth grade";
		else if (rawScoreInt == 4)
			gradeLevel = "a fourth grade";
		else if (rawScoreInt == 3)
			gradeLevel = "a third grade";
		else if (rawScoreInt == 2)
			gradeLevel = "a second grade";
		else if (rawScoreInt == 1)
			gradeLevel = "a first grade";
		else
			gradeLevel = "a kindergarten"; // this shouldn't print at all, mostly for error handling purposes.
		
		//double rawScoreTruncated = ((int)((rawScore + .5) *100)) / 100; //round to two decimal places
		cout << "Its Flesch-Kincaid Grade Level Formula value is " << rawScore <<  ", indicating\n it is at " << gradeLevel << " level."<<endl;
	}