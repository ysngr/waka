/* ku.c */

#include "waka.h"


void select_ms_ku(int *ms)
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


void show_nth_waka_mkus(int n, int *mkus)
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
