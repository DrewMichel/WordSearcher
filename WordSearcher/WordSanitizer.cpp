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

// 
string WordSanitizer::clean(const string& incoming)
{
    string output;
    bool alphaDetected = false;
    char current;
    
    for(int i = 0; i < incoming.length(); i++)
    {
        current = incoming.at(i);
        
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

string WordSanitizer::sanitize(const string& incoming)
{
    string output;
    char current;
    
    for(int i = 0; i < incoming.length(); i++)
    {
        current = incoming.at(i);
        
        if(isalpha(current))
        {
            output.push_back(current);
        }
    }
    
    return output;
}

string WordSanitizer::capitalize(const string& incoming)
{
    string output;
    char current;
    
    for(int i = 0; i < incoming.length(); i++)
    {
        current = incoming.at(i);

        if(isalpha(current))
        {
			current = toupper(current);
        }

		output.push_back(current);
    }
    
    return output;
}

string WordSanitizer::reverse(const string& incoming)
{
	string output;
	char current;

	for (int i = incoming.size() - 1; i >= 0; i--)
	{
		current = incoming.at(i);

		output.push_back(current);
	}

	return output;
}

string WordSanitizer::smudge(const string& incoming)
{
	string output;
	char current;

	for (int i = 0; i < incoming.size(); i++)
	{
		current = incoming.at(i);

		output.push_back(current);

		if (i != incoming.size() - 1)
		{
			output.push_back(' ');
		}
	}

	return output;
}