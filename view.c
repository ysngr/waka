/* view.c */

#include <ncurses.h>
#include <locale.h>
#include "waka.h"

#define USE_CURSES
#define SUB_WIN_LINE 1


#ifdef USE_CURSES
static WINDOW *main_win, *sub_win;
#endif



void init_screen(void)
{
    #ifdef USE_CURSES
        // config about curses
        setlocale(LC_ALL, "");
        initscr();

        main_win = newwin(LINES-SUB_WIN_LINE, COLS, 0, 0);
        sub_win = newwin(SUB_WIN_LINE, COLS, LINES-SUB_WIN_LINE, 0);

        scrollok(main_win, TRUE);
        scrollok(sub_win, TRUE);

        curs_set(False);

        // title
        wmove(main_win, 0, (int)(COLS/2)-10);
        wprintw(main_win, "-- 小倉百人一首 -- \n\n");
        wrefresh(main_win);
        wrefresh(sub_win);

    #else
        // title
        printf("\t\t\t\t-- 小倉百人一首 --\n\n");

    #endif

    return ;
}


void end_screen(int is_exit)
{
    if( is_exit ){
        print("\nQuit program...\n");
    }else{
        print("See you again !\n");
    }

    #ifdef USE_CURSES
        sleep(1);
        endwin();
    #endif

    if( is_exit ){
        exit(1);
    }

    return ;
}


void print(const char *format)
{
    #ifdef USE_CURSES
        wprintw(main_win, format);
        wrefresh(main_win);
    #else
        printf(format);
    #endif

    return ;
}


void prints(const char *format, const char *s)
{
    #ifdef USE_CURSES
        wprintw(main_win, s);
        wrefresh(main_win);
    #else
        printf(format, s);
    #endif
}


void printd(const char *format, const int d)
{
    #ifdef USE_CURSES
        wprintw(main_win, format, d);
        wrefresh(main_win);
    #else
        printf(format, d);
    #endif

    return ;
}


void printd2(const char *format, const int fd, const int sd)
{
    #ifdef USE_CURSES
        wprintw(main_win, format, fd, sd);
        wrefresh(main_win);
    #else
        printf(format, fd, sd);
    #endif

    return ;
}


void strnget(char *s, int size)
{
    #ifdef USE_CURSES
        wgetnstr(sub_win, s, size);
    #else
        fgets(s, size, stdin);
        if( s[strlen(s)-1] == '\n' ){
            s[strlen(s)-1] = '\0';  // kill newline
        }
    #endif

    return ;
}


void adjust_line(void)
{
    #ifdef USE_CURSES
        print("\n");
    #endif

    return ;
}
