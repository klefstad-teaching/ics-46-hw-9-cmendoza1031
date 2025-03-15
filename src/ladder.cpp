//ladder.cpp
#include "ladder.h"

/*
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;*/

// use a set `set<int> visited_words;` to keep track of what words you've visited
// to test if the word is not in the set already:
//
   // auto it = visited_words.find(3);
    
    //if (it != visited_words.end()) cout << *it; // this means the word IS in the set, so we WOULD NOT do anything with it 
    //else cout << "Element not Found!"; // this means we have not visited the word yet, so we would continue with our ladder


// ALSO, make sure all words after the input word are valid English words in the dictionary (first word can be anything)

void error(string word1, string word2, string msg) {
    cerr << "Error parsing from " << word1 << " to " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
// Use the concept of edit distance to compare words to see if they are neighbors. https://en.wikipedia.org/wiki/Edit_distance
//(the lengths are either the same or differ by one character between neighbor words.)
    // If strings are identical, edit distance is 0, which is within any non-negative d
    if (str1 == str2) return d >= 0; // NEW

    int str1_size = str1.size();
    int str2_size = str2.size();

    // Check if word lengths differ by more than allowed distance
    if (abs(str1_size - str2_size) > d)
        return false;

    // Case 1: Same length words - check for substitution
    if (str1_size == str2_size) {
        int differences = 0;
        for (int i = 0; i < str1_size; ++i) {
            if (str1[i] != str2[i])
                differences++;
            if (differences > d)
                return false;
        }
        //return true;
        // For word ladder with d=1, we need exactly one difference
        return d == 1 ? differences == 1 : differences <= d; // NEW
    }

    // Case 2: Different length words - check for insertion/deletion
    // Ensure shorter and longer are correctly assigned
    if (d == 1) {
        const string& shorter = (str1_size < str2_size) ? str1 : str2;
        const string& longer = (str1_size < str2_size) ? str2 : str1;

        size_t longer_size = longer.size();
        size_t shorter_size = shorter.size();

        if (longer_size - shorter_size != 1)
            return false;

        // check if longer is shorter w one additional letter
        size_t i = 0, j=0;
        bool found_diff = false;

        while (i < shorter_size && j < longer_size) {
            if (shorter[i] != longer[j]) {
                if (found_diff) return false; 
                found_diff = true;
                ++j;
            } else {
                ++i;
                ++j;
            }
        }
        return true;
    }
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
// returns true if two words are neighbors
// It is legal to add or remove a single letter from your string at each hop along the way
// This rule would make it possible to generate, for example, a word ladder from car to cheat:
// car → cat → chat → cheat
// Note: so basically for char in word 1, word 2 has to be equal to: (if it's "cat") *at, c*t, ca*t, *cat, c*at, ca*t, or cat*
// hints:

   return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Begin and end word must be different.");
        return {};
    }

    if (word_list.find(end_word) == word_list.end()) {
        // this means the end_word was not found in the dictionary
        error(begin_word, end_word, "End word must be in the dictionary.");
        return {};
    }
    
    // Queue to store partial ladders
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    // FIXED: Better filtering logic that won't exclude intermediate words
    // Calculate the minimum and maximum possible word lengths in the ladder
    size_t min_len = min(begin_word.size(), end_word.size());
    size_t max_len = max(begin_word.size(), end_word.size());
    
    // The maximum length difference in a ladder can be the path length
    // For safety, we'll use a generous range
    size_t max_diff = max_len - min_len + 5; // Add buffer
    
    set<string> filtered_word_list;
    for (const string& word : word_list) {
        size_t len = word.size();
        // Include words of any reasonable length that might appear in the ladder
        if (len >= min_len - max_diff && len <= max_len + max_diff) {
            filtered_word_list.insert(word);
        }
    }

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        if (last_word == end_word)
            return ladder;

        size_t last_len = last_word.size();

        for (const string& word : filtered_word_list) {
            size_t word_len = word.size();
            if (abs((int)(word_len - last_len)) > 1)
                continue;

            // Skip already visited words
            if (visited.find(word) != visited.end())
                continue;

            if (is_adjacent(last_word, word)) {
                vector<string> new_ladder = ladder; // make copy of ladder
                new_ladder.push_back(word);
                if (word == end_word)
                    return new_ladder;
                
                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    error(begin_word, end_word, "No word ladder found.");
    return {};
}
/*
Here is a partial pseudocode description of the algorithm to solve the word-ladder problem:

function generate_word_ladder(begin_word, end_word, word_list):

    ladder_queue = queue of vector of strings
    ladder_queue.push([begin_word])
    visited = set of strings
    visited.insert(begin_word)
    while ladder_queue is not empty:
        ladder = ladder_queue.pop_front()
        last_word = last element of ladder
        for word in word_list:
            if is_adjacent(last_word, word):
                if word not in visited:
                    visited.insert(word)
                    new_ladder = copy of ladder
                    new_ladder.push_back(word)
                    if word equals end_word:
                        return new_ladder
                    ladder_queue.push(new_ladder)
    return no ladder found
end function*/


void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }
    string word;
    while (in >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    size_t ladder_size = ladder.size();
    for (size_t i = 0; i < ladder_size; ++i) {
        cout << ladder[i];
        if (i < ladder_size - 1)
            cout << " ";
    }
    cout << " " << endl;
}

void verify_word_ladder() {
/*
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}*/
    set<string> word_list;
    load_words(word_list, "words.txt");

    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6); // 7?
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6); // 5?
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6); // 7?
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8); // 9?
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
