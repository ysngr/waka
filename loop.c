/* loop.c */

#include "waka.h"

#define SUB_WIN_LINE 1


static WINDOW *main_win, *sub_win;


static void show_options(void);

static int select_n(int, int*);
static void select_ms_ku(int*);
static void select_ms_word(int, int*);

static void show_nth_waka(int);
static void show_nth_waka_mkus(int, int*);
static void show_nth_waka_mwords(int, int*);
static void show_ntoh(int);

static int is_cmpall_int(int*, int, int);
static void wait_for_newline(void);

static void init_curses(void);



void show(void)
{
    int i;

    int is_nth_waka_appeared[MAX_WAKA];
    int n;
    int ms[MAX_WORD];

    // initialize
    srand((unsigned)time(NULL));
    set_aryelem_int(is_nth_waka_appeared, MAX_WAKA, True);
    n = range_from - 1;  // n will be increased (or reassigned) in function select_n
    switch( mode ){
        case MODE_VERSUS :
            set_aryelem_int(ms, MAX_WORD, False);
            switch( versus_ku_fs ){
                case 1 :
                    ms[0] = True;  ms[1] = True;  ms[2] = True;
                    break;
                case 2 :
                    ms[3] = True;  ms[4] = True;
                    break;
            }
            break;
        case MODE_KU :
            select_ms_ku(ms);
            break;
    }
    init_curses();

    // prologue
    show_options();
    wait_for_newline();

    // quiz loop
    for( i = 0; i < quiz_num; i++ ){
        // select index
        n = select_n(n, is_nth_waka_appeared);

        // show closed waka
        switch( mode ){
            case MODE_VERSUS :
                show_nth_waka_mkus(n, ms);
                wait_for_newline();
                break;
            case MODE_KU :
                if( is_const_open_place == False ){
                    select_ms_ku(ms);  // select ku opened
                }
                show_nth_waka_mkus(n, ms);
                wait_for_newline();
                break;
            case MODE_WORD :
                select_ms_word(n, ms);  // select word opened
                show_nth_waka_mwords(n, ms);
                wait_for_newline();
                break;
        }

        // show opened waka
        show_nth_waka(n);
        if( mode != MODE_SHOW_ALL && i != quiz_num-1 ){
            wait_for_newline();
        }
    }

    // epilogue
    // printf("Press enter to end...");
    wprintw(main_win, "Press enter to end...\n");
    wrefresh(main_win);
    wait_for_newline();

    endwin();

    return ;
}


static void show_options(void)
{
    // printf("[Options]\n");
    wprintw(main_win, "[Options]\n");
    wrefresh(main_win);

    // mode
    // printf("  Mode = ");
    wprintw(main_win, "  Mode = ");
    wrefresh(main_win);
    switch( mode ){
        case MODE_SHOW_ALL : // (-a)
            // printf("all\n");
            wprintw(main_win, "all\n");
            wrefresh(main_win);
            break;
        case MODE_VERSUS :  // (-v)
            // printf("versus ");
            wprintw(main_win, "versus ");
            wrefresh(main_win);
            switch( versus_ku_fs ){
                case 1 :
                    // printf("[open = first part]\n");
                    wprintw(main_win, "[open = first part]\n");
                    wrefresh(main_win);
                    break;
                case 2 :
                    // printf("[open = second part]\n");
                    wprintw(main_win, "[open = second part]\n");
                    wrefresh(main_win);
                    break;
            }
            break;
        case MODE_KU :  // (-k)
            // printf("ku ");
            wprintw(main_win, "ku ");
            wrefresh(main_win);
            // printf("[open = %d ku, ", opened_ku);
            wprintw(main_win, "[open = %d ku, ", opened_ku);
            wrefresh(main_win);
            // opened place (-c)
            if( is_const_open_place ){
                // printf("opened place = constant]\n");
                wprintw(main_win, "opened place = constant]\n");
                wrefresh(main_win);
            }else{
                // printf("opened place = fluctuating]\n");
                wprintw(main_win, "opened place = fluctuating]\n");
                wrefresh(main_win);
            }
            break;
        case MODE_WORD :  // (-w)
            // printf("word ");
            wprintw(main_win, "word ");
            wrefresh(main_win);
            // printf("[open = %d word]\n", opened_word);
            wprintw(main_win, "[open = %d word]\n", opened_word);
            wrefresh(main_win);
            break;
    }

    // order (-o)
    // printf("  Order = ");
    wprintw(main_win, "  Order = ");
    wrefresh(main_win);
    if( is_show_in_order ){
        // printf("in order\n");
        wprintw(main_win, "in order\n");
        wrefresh(main_win);
    }else{
        // printf("random, ");
        wprintw(main_win, "random, ");
        wrefresh(main_win);
        // duplication (-d)
        // printf("Duplication = ");
        wprintw(main_win, "Duplication = ");
        wrefresh(main_win);
        if( is_show_duplication ){
            // printf("True\n");
            wprintw(main_win, "True\n");
            wrefresh(main_win);
        }else{
            // printf("False\n");
            wprintw(main_win, "False\n");
            wrefresh(main_win);
        }
    }

    // index (-i)
    // printf("  Index = ");
    wprintw(main_win, "  Index = ");
    wrefresh(main_win);
    if( is_show_index ){
        // printf("True\n");
        wprintw(main_win, "True\n");
        wrefresh(main_win);
    }else{
        // printf("False\n");
        wprintw(main_win, "False\n");
        wrefresh(main_win);
    }

    // range (-f, -t)
    // printf("  Range = %d - %d\n", range_from+1, range_to+1);
    wprintw(main_win, "  Range = %d - %d\n", range_from+1, range_to+1);
    wrefresh(main_win);

    // quiz num (-n)
    // printf("  Quiz num = %d\n", quiz_num);
    wprintw(main_win, "  Quiz num = %d\n", quiz_num);
    wrefresh(main_win);

    // printf("Press enter to start...");
    wprintw(main_win, "Press enter to start...\n\n");
    wrefresh(main_win);

    return ;
}


static int select_n(int prev_idx, int *is_nth_waka_appeared)
{
    int next_idx;

    // if all waka is appeared then reset
    if( is_cmpall_int(is_nth_waka_appeared, MAX_WAKA, False) ){
        set_aryelem_int(is_nth_waka_appeared, MAX_WAKA, True);
    }

    if( is_show_in_order ){
        if( (next_idx = prev_idx + 1) > range_to ){
            next_idx = range_from;
        }
    }else{
        do{
            next_idx = (rand() % (range_to - range_from + 1)) + range_from;
            if( is_show_duplication ){
                break;
            }
        }while( is_nth_waka_appeared[next_idx] == False );
    }

    is_nth_waka_appeared[next_idx] = False;

    return next_idx;
}


static void select_ms_ku(int *ms)
{
    int i, idx;

    // initialize
    set_aryelem_int(ms, MAX_WORD, False);

    for( i = 0; i < opened_ku; i++ ){
        do{
            idx = rand() % MAX_KU;
        }while( ms[idx] == True );
        ms[idx] = True;
    }

    return ;
}


static void select_ms_word(int n, int *ms)
{
    int i, idx, max_word;

    // initialize
    set_aryelem_int(ms, MAX_WORD, False);

    // count word
    for( max_word = 0; wakalist[n][max_word] != 0; max_word++ );

    // set brank position opened
    for( i = 0; i < max_word; i++ ){
        if( wakalist[n][i] == BLANK ){
            ms[i] = True;
        }
    }

    for( i = 0; i < opened_word; i++ ){
        // case : all position is opened
        if( is_cmpall_int(ms, max_word, True) ){
            break;
        }
        // select
        do{
            idx = rand() % max_word;
        }while( ms[idx] == True );
        ms[idx] = True;
    }

    return ;
}


static void show_nth_waka(int n)
{
    int ms[MAX_WORD];
    set_aryelem_int(ms, MAX_WORD, True);
    show_nth_waka_mwords(n, ms);
    // printf("\n");
    wprintw(main_win, "\n");
    wrefresh(main_win);

    return ;
}


static void show_nth_waka_mkus(int n, int *mkus)
{
    int i;
    int ku;
    int ms[MAX_WORD];

    // make mwords array
    set_aryelem_int(ms, MAX_WORD, False);
    ku = 0;
    for( i = 0; wakalist[n][i] != 0; i++ ){
        if( wakalist[n][i] == BLANK ){
            ms[i] = True;
            ku++;
        }else if( mkus[ku] == True ){
            ms[i] = True;
        }else{
            ms[i] = False;
        }
    }

    // show
    show_nth_waka_mwords(n, ms);

    return ;
}


static void show_nth_waka_mwords(int n, int *mwords)
{
    int i;

    if( is_show_index ){
        // printf("%03d : ", n+1);
        wprintw(main_win, "%03d : ", n+1);
        wrefresh(main_win);
    }else{
        // printf("--- : ");
        wprintw(main_win, "--- : ");
        wrefresh(main_win);
    }

    for( i = 0; wakalist[n][i] != 0; i++ ){
        if( mwords[i] == True ){
            show_ntoh(wakalist[n][i]);
        }else{
            show_ntoh(HIDDEN);
        }
    }

    wprintw(main_win, "\n");
    wrefresh(main_win);

    return ;
}


static void show_ntoh(int charnum)
{
    // printf("%s", hslist[charnum-1]);
    wprintw(main_win, "%s", hslist[charnum-1]);
    // wrefresh(main_win);

    return ;
}


static int is_cmpall_int(int *ary, int size, int cmp)
{
    int i;
    for( i = 0; i < size; i++ ){
        if( ary[i] != cmp ){
            return False;
        }
    }

    return True;
}


static void wait_for_newline(void)
{
    char buf[MAX_BUF_SIZE];

    // do{
    //     // fgets(buf, MAX_BUF_SIZE, stdin);
    // }while( buf[0] != '\n' );

    while( True ){
        wgetnstr(sub_win, buf, MAX_BUF_SIZE);

        if( buf[0] == '\0' ){  // enter
            break;
        }else if( buf[0] == 'q' && buf[1] == '\0' ){  // quit
            wprintw(main_win, "\nQuit program. See you.\n");
            wrefresh(main_win);
            sleep(2);
            endwin();
            exit(1);
        }
    }

    return ;
}


static void init_curses(void)
{
    setlocale(LC_ALL, "");
    initscr();

    main_win = newwin(LINES-SUB_WIN_LINE, COLS, 0, 0);
    sub_win = newwin(SUB_WIN_LINE, COLS, LINES-SUB_WIN_LINE, 0);

    scrollok(main_win, TRUE);
    scrollok(sub_win, TRUE);

    curs_set(False);

    // title
    wmove(main_win, 0, (int)(COLS/2)-7);
    wprintw(main_win, "-- 小倉百人一首 -- \n\n");
    wrefresh(main_win);
    wrefresh(sub_win);

    return ;
}
