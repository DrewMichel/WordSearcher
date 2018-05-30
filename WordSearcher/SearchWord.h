// Created by: Andrew Steven Michel
// Date Created: May 2018
#ifndef SEARCH_WORD_H
#define SEARCH_WORD_H

// IMPORTED PACKAGES:
#include <string>
#include "WordSanitizer.h"

// Namespace usage which allows the direct use of declarations
using namespace std;

// Class that is used to graphically display the search targets
class SearchWord
{
    private:
		// Member variables
        string original, word;
		bool found, outlining;

    public:

		int xStart, yStart, xEnd, yEnd;

        // Constructors
        SearchWord();
		SearchWord(const string& originalIn, bool foundIn = false, bool outliningIn = false);
        
        // Destructor
        ~SearchWord();
        
        // Member functions
        
        // Accessors
        string getOriginal();
        string getWord();
		bool getFound();
		bool getOutlining();

        // Mutators
        void setOriginal(const string& originalIn);
        void setWord(const string& wordIn);
        void setFound(const bool foundIn);
		void setOutlining(const bool outliningIn);
		void flipOutlining();
};

#endif