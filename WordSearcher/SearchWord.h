#ifndef SEARCH_WORD_H
#define SEARCH_WORD_H

#include <string>
#include "WordSanitizer.h"

using namespace std;

class SearchWord
{
    private:
        string original, word;
		bool found, outlining;

    public:

		int xStart, yStart, xEnd, yEnd;

        // Constructor
        SearchWord();
		SearchWord(const string& originalIn, bool foundIn = false);
        
        // Destructor
        ~SearchWord();
        
        // Functions
        
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