#ifndef WORD_SANITIZER_H
#define WORD_SANITIZER_H

#include <string>
using namespace std;

class WordSanitizer
{
    private:
        // Constructor
        WordSanitizer();
    
    public:
        // Destructor
        ~WordSanitizer();
    
        // Static Functions
        static string clean(const string& incoming);
        static string sanitize(const string& incoming);
        static string capitalize(const string& incoming);
		static string reverse(const string& incoming);
		static string smudge(const string& incoming);
};

#endif