// IMPORTED PACKAGES:
#include "WordSanitizer.h"

// Private Constructor
WordSanitizer::WordSanitizer()
{
    
}

// Destructor
WordSanitizer::~WordSanitizer()
{
    
}

// Static Functions

// Function that returns a string without leading whitespace based on string parameter
string WordSanitizer::clean(const string& incoming)
{
    string output;
    bool alphaDetected = false;
    char current;
    
	// Loops over string parameter
    for(int i = 0; i < incoming.length(); i++)
    {
        current = incoming.at(i);
        
		// Appends character onto output string
        if(isalpha(current))
        {
            alphaDetected = true;
            output.push_back(current);
        }
        else if(alphaDetected == true && (isspace(current) || ispunct(current)))
        {
            output.push_back(current);
        }
    }
    
    return output;
}

// Function that returns a string with only alpha characters based on string parameter
string WordSanitizer::sanitize(const string& incoming)
{
    string output;
    char current;
    
	// Loops over string parameter
    for(int i = 0; i < incoming.length(); i++)
    {
        current = incoming.at(i);
        
		// Appends character onto output string
        if(isalpha(current))
        {
            output.push_back(current);
        }
    }
    
    return output;
}

// Function that returns an uppercased string based on string parameter
string WordSanitizer::capitalize(const string& incoming)
{
    string output;
    char current;
    
	// Loops over string string parameter
    for(int i = 0; i < incoming.length(); i++)
    {
        current = incoming.at(i);

		// Uppercases character
        if(isalpha(current))
        {
			current = toupper(current);
        }

		// Appends character onto string
		output.push_back(current);
    }
    
    return output;
}

// Function that returns a reversed string based on string parameter
string WordSanitizer::reverse(const string& incoming)
{
	string output;
	char current;

	// Loops over string parameter in reverse
	for (int i = incoming.size() - 1; i >= 0; i--)
	{
		current = incoming.at(i);

		// Appends character onto the string
		output.push_back(current);
	}

	return output;
}

// Function that returns a string with spaces between characters based on string parameter
string WordSanitizer::smudge(const string& incoming)
{
	string output;
	char current;

	// Loops over string parameter
	for (int i = 0; i < incoming.size(); i++)
	{
		current = incoming.at(i);

		// Appends character onto output string
		output.push_back(current);

		// Appends space onto output string if not at the last character
		if (i != incoming.size() - 1)
		{
			output.push_back(' ');
		}
	}

	return output;
}

// Function that returns a string without whitespace based on string parameter
string WordSanitizer::removeWhitespace(const string& incoming)
{
	string output;
	char current;

	// Loops over string parameter
	for (int i = 0; i < incoming.size(); i++)
	{
		current = incoming.at(i);

		// Appends non-whitespace characters onto output string
		if (!isspace(current))
		{
			output.push_back(current);
		}
	}

	return output;
}