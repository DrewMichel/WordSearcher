#pragma once
#ifndef DREW_DEFINITIONS_H
#define DREW_DEFINITIONS_H

#include <string>

const int SCREEN_WIDTH = 1080, SCREEN_HEIGHT = 720;
const std::string DEFAULT_GAME_TITLE = "SFML Tutorial";

const float SPLASH_STATE_SHOW_TIME = 3.0f;
const std::string SPLASH_SCENE_BACKGROUND_FILEPATH = "Resources/res/sunset-1957350_1920.jpg";

const std::string MAIN_MENU_BACKGROUND_FILEPATH = "Resources/res/Main Menu Background.png";

//const std::string MAIN_MENU_TITLE_PATH = "Resources/res/Game Title.png";
const std::string MAIN_MENU_TITLE_PATH = "Resources/res/152426852944149923.png";

const std::string MAIN_MENU_PLAY_BUTTON = "Resources/res/Play Button.png";
const std::string MAIN_MENU_PLAY_BUTTON_OUTER = "Resources/res/Play Button Outer.png";

const std::string GAME_BACKGROUND_FILEPATH = "Resources/res/Main Menu Background.png";
const std::string PAUSE_BACKGROUND_FILEPATH = "Resources/res/Main Menu Background.png";
const std::string PAUSE_BUTTON = "Resources/res/Pause Button.png";
const std::string RESUME_BUTTON = "Resources/res/Resume Button.png";
const std::string HOME_BUTTON = "Resources/res/Home Button.png";
const std::string RETRY_BUTTON = "Resources/res/Retry Button.png";

const std::string X_PIECE_FILEPATH = "Resources/res/X.png";
const std::string O_PIECE_FILEPATH = "Resources/res/O.png";

const std::string X_PIECE_WON_FILEPATH = "Resources/res/X Win.png";
const std::string O_PIECE_WON_FILEPATH = "Resources/res/O Win.png";

const std::string GRID_SPRITE_FILEPATH = "Resources/res/Grid.png";

const std::string FONT_ARIAL_FILEPATH = "Resources/font/arial.ttf";

const int GRID_WIDTH = 3, GRID_HEIGHT = 3;

const int X_PIECE_VALUE = 8;
const int O_PIECE_VALUE = 0;
const int EMPTY_PIECE = -1;

const int WIN_REQUIREMENT = 3;

const int PLAYER_PIECE = X_PIECE_VALUE;
const int AI_PIECE = O_PIECE_VALUE;

const int STATE_PLAYING = 50;
const int STATE_PAUSED = 51;
const int STATE_WON = 52;
const int STATE_LOSE = 53;
const int STATE_PLACING_PIECE = 54;
const int STATE_AI_PLAYING = 55;
const int STATE_DRAW = 56;

#endif