#include "SearchWord.h"

SearchWord::SearchWord() : original(" 3v3ryth.ng wr0ng "), word(original), found(false)
{
	xStart = 0;
	yStart = 0;
	xEnd = 0;
	yEnd = 0;

	word = WordSanitizer::sanitize(original);
}

SearchWord::SearchWord(const string& originalIn, bool foundIn) : found(foundIn)
{
	original = originalIn;
	xStart = 0;
	yStart = 0;
	xEnd = 0;
	yEnd = 0;

	word = WordSanitizer::sanitize(original);
}

// Destructor
SearchWord::~SearchWord()
{
    
}

// Functions

// Accessors
string SearchWord::getOriginal()
{
    return original;
}

string SearchWord::getWord()
{
    return word;
}

bool SearchWord::getFound()
{
	return found;
}

// Mutators
void SearchWord::setOriginal(const string& originalIn)
{
    original = originalIn;
}

void SearchWord::setWord(const string& wordIn)
{
    word = wordIn;
}

void SearchWord::setFound(const bool foundIn)
{
	found = foundIn;
}

void SearchWord::setOutlining(const bool outliningIn)
{
	outlining = outliningIn;
}

bool SearchWord::getOutlining()
{
	return outlining;
}

void SearchWord::flipOutlining()
{
	outlining = !outlining;
}