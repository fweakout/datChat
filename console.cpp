#include <curses.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

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
	WINDOW *testwin = newwin(10,20,0,0);
	box(testwin, 0, 0);
	wrefresh(testwin);
	string = getString(testwin);
	print(1,1,string, testwin);
	wrefresh(testwin);
	getch();
	endwin();
	return 0;
}
