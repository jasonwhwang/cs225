/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    vector<string> words;
    ifstream wordsFile(filename);
    string word;
    if(wordsFile.is_open()) {
        while(getline(wordsFile, word)) {
            words.push_back(word);
        }
    }

    for(auto& w: words) {
        auto lookup = dict.find(w);
        if(lookup == dict.end()) {
            vector<string> s;
            s.push_back(w);
            dict.insert(std::pair<string, vector<string>>(w, s));
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for(auto& w: words) {
        auto lookup = dict.find(w);
        if(lookup == dict.end()) {
            vector<string> s;
            s.push_back(w);
            dict.insert(std::pair<string, vector<string>>(w, s));
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    vector<string> anagrams;
    auto lookup = dict.find(word);
    if(lookup == dict.end()) {
        return vector<string>();
    }
    vector<char> chars(word.begin(), word.end());
    std::sort(chars.begin(), chars.end());

    for(auto& w: dict) {
        vector<char> temp(w.first.begin(), w.first.end());
        std::sort(temp.begin(), temp.end());
        if(chars == temp) {
            anagrams.push_back(w.first);
        }
    }
    return anagrams;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> allAnagrams;
    for(auto& allWords: dict) {
        if(get_anagrams(allWords.first).size() > 1){
            allAnagrams.push_back(get_anagrams(allWords.first));
        }
    }
    return allAnagrams;
}
