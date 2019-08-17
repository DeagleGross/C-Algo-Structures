#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw


#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);

// added by myself
bool removalOfEachLetter(string& s, Dictionary& dict, set<string>& correctWords);
bool replacementOfEachLetter(string& s, Dictionary& dict, char* alphabet, set<string>& correctWords);
bool insertAnyLetterInWord(string& s, Dictionary& dict, char* alphabet, set<string>& correctWords);
bool transposeLetters(string razbor, Dictionary& dict, string nakop, set<string>& correctWords);
void showFoundWords(set<string>& correctWords);

// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
// my args: ../../res/myWords.txt ../../res/my_text.txt
// args - only mistakes: ../../res/wordlist.txt ../../res/onlyMistakes.txt

int main(int argc, char* argv[]) {
	
	// Output usage message if improper command line args were given.
	if (argc != 3)
    {
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}
	
	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);

	checkSpelling(inf, d);

	inf.close();

	return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict) {

	// for output
	unsigned long line_number = 0;

	// ADDED GENERATION OF ALPHABET
	char* alphabet  = new char[26];

	// ADDED Set that contains words for each "checked"
	// using set to have unique values every time
	set<string> correctWords;

	for(int i = 0; i < 26; ++i){
		alphabet[i] = (char)('a' + i);
	}

	while (in) 
    {
		line_number++;
		set<string> totest;
		string line;
		getline(in, line);

  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;
		
		string word;
		while (ss >> word) 
        {
		    // TODO spellchecking under the WORD

		    // using written methods to get lowerCase and no .,\][\'
		    lower(word);
		    word = stripPunct(word);

			//cout << "checking word " << word << endl;

		    // found the word - it is in dictionary - nothing to do
		    if (dict.search(word))
		    	continue;

		    // new set to contain all strings to show
		    correctWords = set<string>();

		    cout << "line " << line_number++ << ": '" << word << "'" << endl;
		    cout << "\tsuggestions: " << endl;
			bool suggFound = false;

			// -------------------------------------------------------
			// 			METHODS DOWN HERE

		    // removal of each letter
            suggFound = removalOfEachLetter(word, dict, correctWords);

            // replacement of all letters
			if (replacementOfEachLetter(word, dict, alphabet, correctWords))
				suggFound = true;

			// adding a letter to each position
			if (insertAnyLetterInWord(word, dict, alphabet, correctWords))
				suggFound = true;

			// transposing words
			if (transposeLetters(word, dict, "", correctWords))
				suggFound = true;

			// 			METHODS UP THERE
			// -------------------------------------------------------

            // if no suggestions were found
            // reporting a message
            if (!suggFound)
				cout << "\t\tnothing found" << endl;
			else
				showFoundWords(correctWords);

            cout << endl;
        }
	}
}

void lower(string& s) {

    // Ensures that a word is lowercase
	for (int i = 0; i < s.length(); i++)
    {
		s[i] = tolower(s[i]);
	}
}

string stripPunct(const string& s) {

	// Remove any single trailing
	// punctuation character from a word.  
	if (ispunct(s[s.length() - 1]) ) 
    {
		return s.substr (0, s.length() - 1);
	}
	else 
    {
		return s;
	}
}

// HERE ARE MY FUNCTIONS TO DO EVERYTHING
// HERE ARE MY FUNCTIONS TO DO EVERYTHING
// HERE ARE MY FUNCTIONS TO DO EVERYTHING
// HERE ARE MY FUNCTIONS TO DO EVERYTHING
// HERE ARE MY FUNCTIONS TO DO EVERYTHING
// HERE ARE MY FUNCTIONS TO DO EVERYTHING
// HERE ARE MY FUNCTIONS TO DO EVERYTHING
// HERE ARE MY FUNCTIONS TO DO EVERYTHING

/* Removes each of letter of word and checks whether is there such a word in dictionary
 * return true if found smth
 */
bool removalOfEachLetter(string& s, Dictionary& dict, set<string>& correctWords)
{
	bool _found = false;

    for (int i = 0; i < s.length(); ++i)
    {
        // every another string without 1 letter
        string str;
        if (i == s.length()-1)
            str = s.substr(0, i);
        else
            str = s.substr(0, i) + s.substr(i+1);

        if (dict.search(str))
        {
			correctWords.insert(str);
			_found = true;
        }
    }

	return _found;
}

/* Replaces each letter of word with any other in english alphabet
 * and checks whether is there such a word in dictionary
 * return true if found smth
 */
bool replacementOfEachLetter(string& s, Dictionary& dict, char* alphabet, set<string>& correctWords)
{
	bool _found = false;

	for (int i = 0; i < s.length(); ++i)
	{
		// every letter is replaced
		string str;

		// with every alphabet letter
		for (int j = 0; j < 26; ++j)
		{
			// creating tmp object to check
			str = string(s);
			str[i] = alphabet[j];

			if (dict.search(str))
			{
				correctWords.insert(str);
				_found = true;
			}
		}
	}

	return _found;
}

/* Inserts any letter of english alphabet to any position in the word
 * and checks whether is there such a word in dictionary
 * return true if found smth
 */
bool insertAnyLetterInWord(string& s, Dictionary& dict, char* alphabet, set<string>& correctWords)
{
	bool _found = false;

	// going through all string letters
	for (int i = 0; i < s.length()+1; ++i)
	{
		string str;

		// going through all letters in alphabet
		for (int j = 0; j < 26; ++j)
		{
			str = string(s);
			str.insert(i, string(1,alphabet[j]));

			if (dict.search(str))
			{
				correctWords.insert(str);
				_found = true;
			}
		}
	}

	return _found;
}

/* Transposes every 2 close to each other letters in the word
 * and checks whether is there such a word in dictionary
 * return true if found smth
 */
bool transposeLetters(string razbor, Dictionary& dict, string nakop, set<string>& correctWords)
{
	bool _found = false;

	// going out from recursion
	if (razbor.length() <= 1)
	{
		nakop += razbor;

		// doing search
		if (dict.search(nakop))
		{
			correctWords.insert(nakop);
			_found = true;
		}

		return _found;
	}

	// also going out from recursion
	if (razbor.length() == 2)
	{
		// without swapping 2 last letters
		string noSwap = nakop + razbor[0] + razbor[1];

		// doing search
		if (dict.search(noSwap))
		{
			correctWords.insert(noSwap);
			_found = true;
		}

		// with swapping 2 last letters
		string withSwap = nakop + razbor[1] + razbor[0];

		// doing search
		if (dict.search(withSwap))
		{
			correctWords.insert(withSwap);
			_found = true;
		}
	}

	// going to recursion
	// for example word "alphabet"
	/* case1: al + transpose(phabet)
	 * case2: la + transpose(phabet)
	 * case3: a + transpose(lphabet)
	 */
	if (razbor.length() > 2)
	{
		// 1 case
		string subCase1 = razbor.substr(2);
		//cout << "ostalos: " << subCase1 << ";;; nakop: " << nakop << endl;
		if (transposeLetters(subCase1, dict, nakop + razbor[0] + razbor[1], correctWords))
			_found = true;

		// 2 case
		string subCase2 = razbor.substr(2);
		//cout << "ostalos: " << subCase2 << ";;; nakop: " << nakop << endl;
		if (transposeLetters(subCase2, dict, nakop + razbor[1] + razbor[0], correctWords))
			_found = true;

		// 3 case
		string subCase3 = razbor.substr(1);
		//cout << "ostalos: " << subCase3 << ";;; nakop: " << nakop << endl;
		if (transposeLetters(subCase3, dict, nakop + razbor[0], correctWords))
			_found = true;
	}

	return _found;
}

/* Outputs values that were found
 */
void showFoundWords(set<string>& correctWords)
{
	for (string str : correctWords)
		cout << "\t\t" << str << endl;
}