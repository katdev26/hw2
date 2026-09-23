#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> keyWords; //empty set that can hold strings *in this case the keywords
    string currentWord; //creates empty string to hold the current word being checked

    for(size_t i = 0; i < rawWords.size(); i++){
        char letter = rawWords[i];

        if(isalnum(letter)){ //checks if the current char is a letter or digit
            currentWord += letter;
        }
        else{
            if(currentWord.size() >= 2){ //length check
                keyWords.insert(convToLower(currentWord));//save the word
            }
            currentWord = ""; //reset current word to empty
        }
    }

    //checks the current word and saves it if valid to make sure all keywords are saved 
    if(currentWord.size() >= 2){ //length check
                keyWords.insert(convToLower(currentWord));//save the word
    }

    return keyWords; //return the set of keywords

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
