#include "AwesomeLibrary.h"

#ifndef _WIN32
int _kbhit(void) {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

int _getch(void) {
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#endif

void miliSleep (int miliseconds) 
{
	#ifdef _WIN32
	Sleep(miliseconds);
	#else
	usleep(miliseconds * 1000);
	#endif
}

int getKey (bool wait) 
{
	int key;

	if (wait || _kbhit())
	{
		key = _getch();
		
		if (key == 0 || key == 224)
			key += 256;
	}
	else
	{
		key = 0;
	}
	
	return key;
}

int getScreenWidth()
{
	#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	return (!GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo)) ? 80 : screenBufferInfo.srWindow.Right + 1;
	#else
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
	#endif
}

int getScreenHeight()
{
	#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	return (!GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo)) ? 80 : screenBufferInfo.srWindow.Bottom + 1;
	#else
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_row;
	#endif
}

#ifdef _WIN32
void setBackgroundColor(Color color)
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	wAttrib = screenBufferInfo.wAttributes;

	wAttrib &= ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);

	int c = static_cast<int>(color);

	if (c & 1)
		wAttrib |= BACKGROUND_BLUE;
	if (c & 2)
		wAttrib |= BACKGROUND_GREEN;
	if (c & 4)
		wAttrib |= BACKGROUND_RED;
	if (c & 8)
		wAttrib |= BACKGROUND_INTENSITY;

	SetConsoleTextAttribute(outputHandle, wAttrib);
}

void setForegroundColor(Color color)
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	wAttrib = screenBufferInfo.wAttributes;

	wAttrib &= ~(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

	int c = static_cast<int>(color);

	if (c & 1)
		wAttrib |= FOREGROUND_BLUE;
	if (c & 2)
		wAttrib |= FOREGROUND_GREEN;
	if (c & 4)
		wAttrib |= FOREGROUND_RED;
	if (c & 8)
		wAttrib |= FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(outputHandle, wAttrib);
}
#else
void setColor(Color color, bool isBackground)
{
	int ansiColor = static_cast<int>(color);
	if (isBackground)
	{
		ansiColor += 40; // Background color
	}
	else
	{
		ansiColor += 30; // Foreground color
	}
	std::cout << "\033[" << ansiColor << "m";
}

void setBackgroundColor(Color color)
{
	setColor(color, true);
}

void setForegroundColor(Color color)
{
	setColor(color, false);
}
#endif

void clearScreen () 
{
	#ifdef _WIN32
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	DWORD dw;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	DWORD dwSize;
	
	cout.flush();
	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	
	dwSize = screenBufferInfo.dwSize.X * screenBufferInfo.dwSize.Y;
	
	FillConsoleOutputCharacter(outputHandle, ' ', dwSize, coord, &dw);
	FillConsoleOutputAttribute(outputHandle, screenBufferInfo.wAttributes, dwSize, coord, &dw);
	SetConsoleCursorPosition(outputHandle, coord);
	#else
	printf("%s[2J%s[H", ESC, ESC);
	fflush(stdout);
	#endif
}

void goToCoordinates (int x, int y)
{
	#ifdef _WIN32
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	
	coord.X = x - 1;
	coord.Y = y - 1;
	
	SetConsoleCursorPosition(outputHandle, coord);
	#else
	printf("%s[%d;%dH", ESC, y, x);
	fflush(stdout);
	#endif
}

void hideCursor () 
{
	#ifdef _WIN32
	CONSOLE_CURSOR_INFO cursorInfo;
	
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	#else
	printf("%s[?25l", ESC);
	fflush(stdout);
	#endif
}

void showCursor () 
{
	#ifdef _WIN32
	CONSOLE_CURSOR_INFO cursorInfo;
	
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = TRUE;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	#else
	printf("%s[?25h", ESC);
	fflush(stdout);
	#endif
}

void setTitle (const char* title) 
{
	#ifdef _WIN32
	SetConsoleTitleA(title);
	#else
	printf("%s]2;%s%s", ESC, title, ESC);
	fflush(stdout);
	#endif
}


void drawFrame (int x1, int y1, int x2, int y2) 
{
	goToCoordinates(x1, y1);
	cout << (char)LEFT_UP;
	goToCoordinates(x2, y1);
	cout << (char)RIGHT_UP;
	goToCoordinates(x2, y2);
	cout << (char)RIGHT_DW;
	goToCoordinates(x1, y2);
	cout << (char)LEFT_DW;
	
	for (int i = x1 + 1; i < x2; i++) 
	{
		goToCoordinates(i, y1);
		cout << (char)LINE_HOR;
		goToCoordinates(i, y2);
		cout << (char)LINE_HOR;
	}
	
	for (int i = y1 + 1; i < y2; i++) 
	{
		goToCoordinates(x2, i);
		cout << (char)LINE_VER;
		goToCoordinates(x1, i);
		cout << (char)LINE_VER;
	}
}

