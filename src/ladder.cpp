#include "ladder.h"
#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

void error(string word1, string word2, string msg){
    cout << "ERROR!!! - " << word1 << " " << word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){

}

bool is_adjacent(const string& word1, const string& word2){

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;    
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
}

void load_words(set<string> & word_list, const string& file_name){

}

void print_word_ladder(const vector<string>& ladder){

}

void verify_word_ladder(){

}