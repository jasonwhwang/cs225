/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<StringTriple> v;
    vector<string> words;

    ifstream wordsFile(word_list_fname);
    string word;
    if(wordsFile.is_open()) {
        while(getline(wordsFile, word)) {
            if(word.length() == 5) {
                words.push_back(word);
            }
        }
    }

    for(auto& str: words) {
        std::string strRemC1 = str.substr(1);
        std::string strRemC2 = str.substr(0,1) + str.substr(2);

        if(d.homophones(str, strRemC1) && d.homophones(str, strRemC2) && d.homophones(strRemC1, strRemC2)) {
            StringTriple tri;
            std::get<0>(tri) = str;
            std::get<1>(tri) = strRemC1;
            std::get<2>(tri) = strRemC2;
            v.push_back(tri);
        }
    }
    return v;
}
