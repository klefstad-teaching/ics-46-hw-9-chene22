#include "ladder.h"
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

int my_abs(int l1){
    if(l1 < 0){
        l1 *= -1;
    }
    return l1;
}

void error(string word1, string word2, string msg){
    cout << "ERROR!!! - " << word1 << " " << word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int first_length = str1.size();
    int second_length = str2.size();
    int length_diff = my_abs(first_length - second_length);
    if(length_diff > d){ // length is more than allowed diff so false right away
        //cout << "length diff " << length_diff << " is greater than d, returning false" << endl;
        return false;
    }
    else if(length_diff > 0){ // length differs but within d threshold, so check how many differences there are
        int first_index = 0;
        int second_index = 0;
        int total_diff = 0;

        const string& shorter = (first_length < second_length) ? str1 : str2;
        const string& longer = (first_length < second_length) ? str2 : str1;

        while(first_index < shorter.size() && second_index < longer.size()){
            char first_char = tolower(shorter[first_index]);
            char second_char = tolower(longer[second_index]);

            //cout << "first index: " << first_index << "; second index: " << second_index << "; chars: " << first_char << " " << second_char << endl;
            if(first_char == second_char){
                first_index++;
                second_index++;
            }
            else{
                ++total_diff;
                //cout << first_char << " is different than " << second_char << " so total_diff is now " << total_diff << endl;
                if(total_diff > d){
                    //cout << "total diff " << total_diff << " is greater than d, returning false" << endl;
                    return false;
                }
                ++second_index;
            }
        }

        // reaching here, it's possible the difference is extra letters at the end of the longer string
        // but the while loop kicks us out once we reach the end of the shorter string
        // so we add the difference between the last second_index and the size of the longer string
        //cout << "total_diff before accounting for final my_abs is " << total_diff << endl;
        //cout << "taking the abs of longer.size(): " << longer.size() << " minus 1 minus index " << second_index << endl;
        int trailing_offset = my_abs(longer.size() - second_index);
        //cout << "trailing offset is " << trailing_offset << endl;
        total_diff += trailing_offset;
        //cout << "total_diff at the end is now " << total_diff << ". returning total_diff less or equal to d" << endl;
        return total_diff <= d;
    }
    else{ // reaching this means the lengths are the same
        int char_diff = 0;
        for(int i = 0; i < first_length; ++i){
            char first_char = tolower(str1[i]);
            char second_char = tolower(str2[i]);

            if(first_char != second_char){
                char_diff++;
                if(char_diff > d){
                    //cout << "char_diff " << char_diff << " is greater than d, returning false" << endl;
                    return false;
                }
            }
        }
        //cout << "char diff is now " << char_diff << " at the end. returning char_diff less or equal to d" << endl;
        return char_diff <= d;
    }
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;    
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(const string& word : word_list){
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end()){
                visited.insert(word);
                vector<string> new_ladder{ladder};
                new_ladder.push_back(word);
                if(word == end_word){
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }

    // at this point, no ladder found
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    string word;
    while(in>> word){
        for(auto &c : word){
            c = tolower(c);
        }
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.size() <= 0){
        cout << "No word ladder found.";
    }
    else{
        cout << "Word ladder found: ";
        for(size_t i = 0; i < ladder.size(); ++i){
        cout << ladder[i] << " ";
        }
    }


    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

