// Created by: Andrew Steven Michel
// Date Created: May 2018

//  Course: CS 151         Days & Time:  Tuesday and Thursdays 3:30-5:20 PM
//  Project Number: Final Project
//  Programmer(s):  Andrew Michel
//  Date Created or Last Modified: 5/21/2018
//-----------------------------------------------------------------------------
//  Program Title:  Word Searcher
//  Program Description:
//  This program receives a two dimensional grid of letters and a list of
//	search targets, then scans the grid to locate the search targets.
//	In addition, the grid and search words are graphically display.
//	Clicking on a search word will cause an orb to highlight itself where it
//	is located in the grid.
//-----------------------------------------------------------------------------
// ALGORITHM:
// 1. Greet user and provide instructions
// 2. Prompt user to enter grid and search target file paths
// 3. Open input file streams to both file paths
// 4. If either paths are invalid, throw exception, close streams, and 
//		attempt to use default files
// 5. Open input file streams to default file paths
// 6. If either paths are invalid throw exception, close streams, and
//		terminate program
// 7. Otherwise file streams are valid
// 8. Read in grid and search target data from files to vectors
// 9. Close streams
// 10. Launch SFML window by creating Game object and pass vectors
// 11. Display splash screen state before moving to main menu
// 12. Display main menu state until user hits play button
// 13. Display game state
// 14. Programmatically traverse grid by generating strings horizontally,
//		vertically, diagonally up, and diagonally down. Use the string to index
//		into unordered_maps to determine if a search word has been located.
// 15.		Whenever a search target is located, add a search orb with its
//			x and y coordinates based on starting and ending points inside grid
// 16. Allow user to graphically click search targets
// 17.		If a search target hasn't been clicked, highlight it and allow its
//			search orb to be displayed
// 18.		If a search target has been clicked, remove its highlight and
//			do not display its search orb
//_____________________________________________________________________________
// See README.txt for building

/*
	TRAVERSAL ALGORITHM
		Grid stored in vector<string> -- GOOD
		original search stored in unordered_map<string (RAW), SearchWord>

		parsing search stored in unordered_map<string (sanitized), string (RAW)>
		reversed search stored in same unordered_map<string (sanitized & reversed), string (RAW)>

		if a RAW is found, use it to index into original search storage

		iterate through unordered_map and display found search words with coords (x, y. start), (x, y. end)

	TRAVERSAL IMPLEMENTATION
		Read in grid file into vector<string>
		Read in search file into unordered_map<string (RAW), SearchWord>

		use same read in to create unordered_map<string(sanitized), string (RAW)>
		use same read in to add reverses to unordered_map<string (sanitized), string (RAW)>

		parse grid vector<string> using unordered_map<string (sanitized), string (RAW)>
		if indexed, use string (RAW) to index into unordered_map<string (RAW), SearchWord>
		to set x1, y1, x2, y2, coordinates and set wasFound = true

		Since reversed duplicate strings have been added to unordered_map<string (sanitized, string (raw)>,
		the grid only needs to be checked horizontally, vertically, diagonally down, and diagonally up
		once each. As opposed to twice in each direction (I.E horizontally left & right, vertically up & down)
*/

/*
Requirements for the Final Project include :

1.	Use the class Style Sheet as usual -- DONE
2.	Give your variables descriptive names that are appropriate for your program -- DONE
3.	Comment your classes to make them readable for the novice programmer -- DONE
4.	Create at least 3 Classes including a TestDriver -- DONE
5.	Use Constructors in your classes -- DONE, SearchOrb, Game, etc...
6.	Use at least one Data Structure in your classes - ArrayList, Vector, LinkedList -- DONE, Grid data stored inside vector
7.	Error Checking and Exception Handling are mandatory in your program -- DONE, FileOperationException used during grid and search word file opening in main function
8.	Include at least four of the following in your program : -- DONE, b, c, e, g
	a. Advanced File Handling(Binary) -- DENIED
	b. String Processing(C - string and/or string class) -- DONE, Grid data sanitized, traversed, etc...
	c. Pointers -- DONE, Game data stored in shared_ptr, MainMenuState draws its background with sf::Uint8 *pixels
	d. Recursion -- NEGATIVE
	e. Generic Data Structure -- DONE, unordered_maps, vectors, arrays, etc...
	f. Function Templates -- NEGATIVE
	g. Polymorphism and Virtual Functions -- DONE, all State classes derive from State and overrride at minimum its pure virtual functions
9.	Your program should be a minimum of 5 - 6 pages of code including the Style Sheet information and comments. -- DONE
10. Be sure to include a PrintScreen(s) to demonstrate how your program works. -- DONE
*/

// IMPORTED PACKAGES:
#include <iostream>
#include "Definitions.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>
#include "WordSanitizer.h"
#include "FileOperationException.h"

// Namespace usage which allows the direct use of declarations
using namespace std;

// Function prototype
bool openInputStream(fstream& inputStream, const string& filePath) throw(Drewski::FileOperationException);

// Main function entry point
int main(int argc, char **argv)
{
	// Declares variables
	string gridPath, searchPath;
	string gridLine, searchLine;
	vector<string> grid, search;
	fstream gridStream, searchStream;

	// Greets user and provides instructions
	cout << "Greetings user, I will solve a word search puzzle." << endl;

	// Prompts user to enter the file path for the word grid
	cout << "Enter filepath containing word grid: ";
	getline(cin, gridPath);

	// Prompts user to enter the file path for the search targets
	cout << "Enter filepath containing search words: ";
	getline(cin, searchPath);

	// Opens grid and search input streams
	try
	{
		openInputStream(gridStream, gridPath);
		openInputStream(searchStream, searchPath);
	}
	catch (Drewski::FileOperationException ex)
	{
		gridStream.close();
		searchStream.close();
		cout << ex.what() << endl;
	}

	// If streams are invalid, attempts to open default grid and search word files
	if (!gridStream || !searchStream)
	{
		// Closes streams
		cout << "Launching with default parameters" << endl;
		
		try
		{
			openInputStream(gridStream, DEFAULT_GRID_FILEPATH);
			openInputStream(searchStream, DEFAULT_SEARCH_FILEPATH);
		}
		catch (Drewski::FileOperationException ex)
		{
			gridStream.close();
			searchStream.close();

			cout << "Failure to launch program" << endl;

			// Allows program to end
			cout << "Press enter to continue..." << endl;
			cin.ignore();
			return EXIT_FAILURE;
		}
	}

	// Loops while grid stream is valid
	while (gridStream && !gridStream.fail() && !gridStream.bad() && !gridStream.eof() && gridStream.good())
	{
		// Gets a line from the grid stream and assigns it to grid line
		getline(gridStream, gridLine);

		// Cleans unwanted content from the grid line
		gridLine = WordSanitizer::sanitize(gridLine);
		gridLine = WordSanitizer::capitalize(gridLine);

		// Pushes the grid line onto the grid vector
		grid.push_back(gridLine);
		cout << "GRID WORD: " << gridLine << endl;
	}

	// Loops while search stream is valid
	while (searchStream && !searchStream.fail() && !searchStream.bad() && !searchStream.eof() && searchStream.good())
	{
		// Gets a line from the search stream and assigns it to the search line
		getline(searchStream, searchLine);

		// Cleans unwanted content from the search line
		searchLine = WordSanitizer::clean(searchLine);
		searchLine = WordSanitizer::capitalize(searchLine);

		// Pushes the search line onto the search vector
		search.push_back(searchLine);
		cout << "SEARCH WORD: " << searchLine << endl;
	}

	// Closes streams
	gridStream.close();
	searchStream.close();

	// Creates Game object which launches a SFML generated window
	Drewski::Game game(SCREEN_WIDTH, SCREEN_HEIGHT, DEFAULT_GAME_TITLE, grid, search);

	return EXIT_SUCCESS;
}

bool openInputStream(fstream& inputStream, const string& filePath) throw (Drewski::FileOperationException)
{
	inputStream.open(filePath, ios::in);

	if (!inputStream)
	{
		throw Drewski::FileOperationException("FAILED TO OPEN STREAM TO PATH: " + filePath);
	}

	return true;
}