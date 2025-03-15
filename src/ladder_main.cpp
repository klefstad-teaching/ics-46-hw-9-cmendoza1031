#include "ladder.h"

int main () {
    try {
        set<string> word_list;
        load_words(word_list, "words.txt");
        
        // Uncomment to run tests
        // verify_word_ladder();
        // return 0;
        
        string begin_word, end_word;
        
        cout << "Enter start word: ";
        cin >> begin_word;
        
        cout << "Enter end word: ";
        cin >> end_word;
        
        // Convert to lowercase
        transform(begin_word.begin(), begin_word.end(), begin_word.begin(), ::tolower);
        transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);
        
        vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
        
        if (!ladder.empty()) {
            cout << "Word ladder from " << begin_word << " to " << end_word << ":" << endl;
            print_word_ladder(ladder);
            cout << "Length: " << ladder.size() << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}