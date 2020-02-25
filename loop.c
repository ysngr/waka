/* loop.c */

#include "waka.h"


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
    printf("Press enter to end...");
    wait_for_newline();

    return ;
}


static void show_options(void)
{
    printf("[Options]\n");

    // mode
    printf("  Mode = ");
    switch( mode ){
        case MODE_SHOW_ALL : // (-a)
            printf("all\n");
            break;
        case MODE_VERSUS :  // (-v)
            printf("versus ");
            switch( versus_ku_fs ){
                case 1 :
                    printf("[open = first part]\n");
                    break;
                case 2 :
                    printf("[open = second part]\n");
                    break;
            }
            break;
        case MODE_KU :  // (-k)
            printf("ku ");
            printf("[open = %d ku, ", opened_ku);
            // opened place (-c)
            if( is_const_open_place ){
                printf("opened place = constant]\n");
            }else{
                printf("opened place = fluctuating]\n");
            }
            break;
        case MODE_WORD :  // (-w)
            printf("word ");
            printf("[open = %d word]\n", opened_word);
            break;
    }

    // order (-o)
    printf("  Order = ");
    if( is_show_in_order ){
        printf("in order\n");
    }else{
        printf("random, ");
        // duplication (-d)
        printf("Duplication = ");
        if( is_show_duplication ){
            printf("True\n");
        }else{
            printf("False\n");
        }
    }

    // index (-i)
    printf("  Index = ");
    if( is_show_index ){
        printf("True\n");
    }else{
        printf("False\n");
    }

    // range (-f, -t)
    printf("  Range = %d - %d\n", range_from+1, range_to+1);

    // quiz num (-n)
    printf("  Quiz num = %d\n", quiz_num);

    printf("Press enter to start...");

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
    printf("\n");

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
        printf("%03d : ", n+1);
    }else{
        printf("--- : ");
    }

    for( i = 0; wakalist[n][i] != 0; i++ ){
        if( mwords[i] == True ){
            show_ntoh(wakalist[n][i]);
        }else{
            show_ntoh(HIDDEN);
        }
    }

    return ;
}


static void show_ntoh(int charnum)
{
    printf("%s", hslist[charnum-1]);

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

    do{
        fgets(buf, MAX_BUF_SIZE, stdin);
    }while( buf[0] != '\n' );

    return ;
}
