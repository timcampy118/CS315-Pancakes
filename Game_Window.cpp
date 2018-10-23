#include "Game_Window.h"

#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <menu.h>
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>
#include <string.h>
#include "Player.h"


Game_Window::Game_Window() {
	return;
}

void Game_Window::displayStartScreen(){
	int rows, cols = 0;
        WINDOW *my_win;

        initscr();
        getmaxyx(stdscr,rows,cols);
        cout << rows << endl;

        printPancakes(0,0);
        mvprintw(7, 0, "Team Teamwork (18)");
        mvprintw(rows-1, 0, "Jack Shirley, Jay Khatri, Zackary Ramirez, Timothy Nguyen");
        refresh();

        my_win = create_newwin(5, 23, (rows/2)-12, (cols/2)-3);
        keypad(my_win,true);

        int choice = 0;
        while(true){
                wattron(my_win, A_REVERSE);
                mvwprintw(my_win, 1, 1, "Press ENTER to start");
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
                wattroff(my_win, A_REVERSE);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		choice = wgetch(my_win);
                if(choice == 10){
                        break;
                }
                wrefresh(my_win);
        }

        mvprintw(25, 0, "Started");
        getch();
        endwin();
	
}

vector<int> Game_Window::displaySetupScreen(int size)
{
        initscr();
        noecho();
        //cbreak();
        timeout(0);
        int x;



        vector<int> order;
        vector<int> remain;


         for(int x=0; x<size; x++)
        {
                remain.push_back(x+1);
        }
        
        while((int)(order.size())!=size)
        {
                move(x,0);
                printw("Type in the next pancake 1-%d, type 0 for a random list",size);
                x++;
                int c=getch();
                while(getch()!=10)
                {
                        int tmp=c;
                        c=getch()-48;
                        if(c==-38||c==tmp||c==-49)
                                c=tmp;
                        else
                        {
                        move(0+x,0);
                        printw("%d\n", c);
                         x++;
                        refresh();     
                        }
                        
                }
                if(c==0)
                {
                        vector<int> random;


                         for(int x=0; x<size; x++)
                        {
                                random.push_back(x);
                        }
                        random_shuffle(random.begin(), random.end());
                        return random;

                }
                else if(c>0&&c<=(size))
                {
                        
                       

                        //if (find(remain.begin(), remain.end(), c) != remain.end() )
                        //{
                        //    move(0+x,0);
                        //    printw("Number already used");
                       // }
                       // else
                        //{
                                order.push_back(c);
                                printw("Added");
                                x++;
                                //remain.erase((int)find(remain.begin(), remain.end()));

//                        }
                        
                        
                }
                 else
                {
                        printw("Invalid input");     
                }
              
        }
        printw("Done");
        return order;
}



/*
vector<int> Game_Window::displaySetupScreen(int size)
{
    initscr();
    noecho();
    cbreak();
    erase();
    int Ymax, xMax;
    getmaxyx(stdscr,Ymax,xMax);

    WINDOW * menuwin = newwin(6,xMax-12,Ymax-8,5);
    box(menuwin,0,0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);

    vector<int> choices(size);
    vector<int> order(size);


    for(int x=0; x<choices.size(); x++)
    {
        choices[x]=x;
    }

    int choice;
    int highlight=0;

    while(choices.size()!=0)
    {
        for(int x=0; x<size; x++)
        {
            if(x==highlight)
            {
                wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin, x+1, 1, to_string(choices[x]).c_str());
                wattroff(menuwin,A_REVERSE);
            }
            choice=wgetch(menuwin);

            switch(choice)
            {
                case KEY_UP:
                    highlight--;
                    if(highlight==-1)
                        highlight=0;
                    break;
                case KEY_DOWN:
                    highlight++;
                    if(highlight==size)
                        highlight=size-1;
                    break;
            }
            if(choice==10)
            {
                order.push_back(choices[highlight]);
                choices.erase(choices.begin()+highlight);
            }


            }

        }


        return order;
}
*/
WINDOW* Game_Window::create_newwin(int height, int width, int starty, int startx)
{       
	WINDOW *local_win;

        local_win = newwin(height, width, starty, startx);
        box(local_win, 0 , 0);
        wrefresh(local_win);

        return local_win;
}


void Game_Window::printPancakes(int y, int x){
        mvprintw(y, x, "__________                              __                  ");
        mvprintw(y+1, x, "|______   |_____    ____   ____ _____ |  | __ ____   ______");
        mvprintw(y+2, x, " |     ___||__  |  /    \\_/ ___\\__ \\  |  |/ // __ \\/  ___/");
        mvprintw(y+3, x, " |    |    / __ | |   |  \\  \\___ / __\\|    <\\ ___/\\___\\ ");
        mvprintw(y+4, x, " |____|    (____  /___|  /\\___  >____ |__|_ \\___  >____  >");
        mvprintw(y+5, x, "                \\/     \\/     \\/     \\/    \\/   \\/     \\/ ");
}
