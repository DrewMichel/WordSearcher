#include <iostream>

#include "Definitions.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>
#include "WordSanitizer.h"

using namespace std;

int main(int argc, char **argv)
{
	string gridPath, searchPath;
	string gridLine, searchLine;
	vector<string> grid, search;

	cout << "Greetings user, I will solve a word search puzzle." << endl;

	cout << "Enter filepath containing word grid: ";
	getline(cin, gridPath);

	cout << "Enter filepath containing search words: ";
	getline(cin, searchPath);

	fstream gridStream, searchStream;

	gridStream.open(gridPath.c_str(), ios::in);
	searchStream.open(searchPath.c_str(), ios::in);

	if (!gridStream || !searchStream)
	{
		if (!gridStream)
		{
			cout << "Failed to open file: " << gridPath << endl;
		}
		if (!searchStream)
		{
			cout << "Failed to open file: " << searchPath << endl;
		}

		cout << "Launching with default parameters" << endl;
		gridStream.close();
		searchStream.close();
		
		gridStream.open(DEFAULT_GRID_FILEPATH.c_str(), ios::in);
		searchStream.open(DEFAULT_SEARCH_FILEPATH.c_str(), ios::in);

		if (!gridStream || !searchStream)
		{
			cout << "Failure to launch program" << endl;

			if (!gridStream)
			{
				cout << "Failed to open file: " << DEFAULT_GRID_FILEPATH << endl;
			}
			if (!searchStream)
			{
				cout << "Failed to open file: " << DEFAULT_SEARCH_FILEPATH << endl;
			}

			cout << "Press enter to continue..." << endl;
			cin.ignore();
			return EXIT_FAILURE;
		}
	}

	// streams open
	while (gridStream && !gridStream.fail() && !gridStream.bad() && !gridStream.eof() && gridStream.good())
	{
		getline(gridStream, gridLine);

		gridLine = WordSanitizer::sanitize(gridLine);
		gridLine= WordSanitizer::capitalize(gridLine);

		grid.push_back(gridLine);
		cout << "GRID WORD: " << gridLine << endl;
	}

	while (searchStream && !searchStream.fail() && !searchStream.bad() && !searchStream.eof() && searchStream.good())
	{
		getline(searchStream, searchLine);

		searchLine = WordSanitizer::clean(searchLine);
		searchLine = WordSanitizer::capitalize(searchLine);

		search.push_back(searchLine);
		cout << "SEARCH WORD: " << searchLine << endl;
	}

	gridStream.close();
	searchStream.close();

	//Drewski::Game game(SCREEN_WIDTH, SCREEN_HEIGHT, DEFAULT_GAME_TITLE);
	Drewski::Game game(SCREEN_WIDTH, SCREEN_HEIGHT, DEFAULT_GAME_TITLE, grid, search);

	return EXIT_SUCCESS;
}

/* Algorithm 1.
	Grid stored in vector<string> -- GOOD
	original search stored in unordered_map<string (RAW), SearchWord>

	parsing search stored in unordered_map<string (sanitized), string (RAW)>
	reversed search stored in same unordered_map<string (sanitized & reversed), string (RAW)>


	if a RAW is found, use it to index into original search storage

	iterate through unordered_map and display found search words with coords (x, y. start), (x, y. end)

*/
/* Implementation 1.
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