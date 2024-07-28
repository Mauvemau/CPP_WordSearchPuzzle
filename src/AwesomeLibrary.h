#ifndef AWESOME_LIBRARY_H
#define AWESOME_LIBRARY_H

#include <iostream>

#ifdef _WIN32
	#include <windows.h>
	#include <conio.h>
#else
	#include <unistd.h>
	#include <termios.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>

	#define ESC "\033"
#endif

using namespace std;

#ifdef _WIN32
enum class Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	WHITE,
	GRAY,
	LBLUE,
	LGREEN,
	LCYAN,
	LRED,
	LMAGENTA,
	YELLOW,
	BWHITE
};
#else
enum class Color
{
	BLACK,
	RED,
	GREEN,
	BROWN,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	GRAY,
	LRED,
	LGREEN,
	YELLOW,
	LBLUE,
	LMAGENTA,
	LCYAN,
	BWHITE
};
#endif

const int KEY_ESC = 27;
#ifdef _WIN32
const int KEY_UP = 256 + 72;
const int KEY_DOWN = 256 + 80;
const int KEY_LEFT = 256 + 75;
const int KEY_RIGHT = 256 + 77;
const int KEY_DELETE = 256 + 83;
const int KEY_INSERT = 256 + 82;
const int KEY_ENTER = 13;
const int KEY_BEG = 256 + 71;
const int KEY_END = 256 + 79;
#else
const int KEY_UP = 65;
const int KEY_DOWN = 66;
const int KEY_LEFT = 68;
const int KEY_RIGHT = 67;
const int KEY_DELETE = 51;
const int KEY_INSERT = 50;
const int KEY_ENTER = 10;
const int KEY_BEG = 49;
const int KEY_END = 52;
#endif

const int LEFT_UP = 201;
const int LEFT_DW = 200;
const int RIGHT_UP = 187;
const int RIGHT_DW = 188;
const int LINE_HOR = 205;
const int LINE_VER = 186;


/// <summary>
/// Sets the background color of the console.
/// </summary>
void setBackgroundColor (Color color);

/// <summary>
/// Sets the foreground color of the console.
/// </summary>
void setForegroundColor (Color color);

/// <summary>
/// Clears the whole console.
/// </summary>
void clearScreen ();

/// <summary>
/// Sets the cursor to a particular position inside the console.
/// </summary>
void goToCoordinates (int x, int y);

/// <summary>
/// Gets the next key to be pressed.
/// <param name = "wait"> Used to tell the system if it should wait until a key is pressed. </param>
/// <returns> The code of the key pressed. </returns>
/// </summary>
int getKey (bool wait = true);

/// <summary>
/// Hides the console's cursor.
/// </summary>
void hideCursor ();

/// <summary>
/// Shows the console's cursor.
/// </summary>
void showCursor ();

/// <summary>
/// Sets the window's title.
/// </summary>
void setTitle (const char* title);

/// <summary>
/// Waits for a specific time (in miliseconds).
/// </summary>
void miliSleep (int miliseconds);

/// <summary>
/// Gets the width of the console.
/// <returns> The width of the console (in characters). </returns>
/// </summary>
int getScreenWidth ();

/// <summary>
/// Gets the height of the console.
/// <returns> The height of the console (in characters). </returns>
/// </summary>
int getScreenHeight ();

/// <summary>
/// Draws a frame inside the console.
/// <param name = "x1"> The x coordinate of the top-left corner.</param>
/// <param name = "y1"> The y coordinate of the top-left corner.</param>
/// <param name = "x2"> The x coordinate of the bottom-right corner.</param>
/// <param name = "y2"> The y coordinate of the bottom-right corner.</param>
/// </summary>
void drawFrame (int x1, int y1, int x2, int y2);

#endif
