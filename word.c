/* word.c */

#include "waka.h"


void select_ms_word(int n, int *ms)
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


void show_nth_waka_mwords(int n, int *mwords)
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
