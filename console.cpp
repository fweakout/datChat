#include <curses.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

class ConsoleWindow
{
	WINDOW *window;
	int xpos, ypos;
	int xsize, ysize;
	
	public:
		ConsoleWindow(int x,int y,int width,int height);
		void write(std::string string);
		WINDOW * getScr();
};

ConsoleWindow::ConsoleWindow(int x,int y,int width,int height)
{
	xpos = x;
	ypos = y;
	xsize = width;
	ysize = height;
	window = newwin(width, height, x, y);
}

void ConsoleWindow::write(std::string string)
{
	char cstr[80];
	for(int i = 0; i < string.length() && i < 80; i++){
		cstr[i] = string.at(i);
	}
	wprintw(window, cstr);
}

WINDOW * ConsoleWindow::getScr()
{
	return window;	
}

void init()
{
	initscr();
	noecho();
	cbreak();
	raw();
	keypad(stdscr, TRUE);	
}

void print(int x, int y, std::string string, WINDOW *scr)
{
	char cstr[80];
	for(int i = 0; i < string.length() && i < 80; i++){
		cstr[i] = string.at(i);
	}
	mvwprintw(scr, x,y, cstr);
}

std::string getString(WINDOW *scr)
{
	std::string str;
	int key;
	while((char)key != '\n')
	{	
		key = wgetch(scr);
		if(key == KEY_BACKSPACE)
		{
			str = str.substr(0, str.size() -1);
			
		}
		else
		{
			str += (char)key;
		}
	}
	return str;
}


int main()
{
	std::cout << "start" << std::endl;
	std::string string;
	init();
	refresh();
	ConsoleWindow testwindow = ConsoleWindow(0,0,10,10);
	ConsoleWindow bananawindow = ConsoleWindow(10,10,10,10);
	testwindow.write("hello my name is banana cool bro");
	bananawindow.write("this is another window yo");
	wrefresh(testwindow.getScr());
	wrefresh(bananawindow.getScr());
	getch();
	endwin();
	return 0;
}
