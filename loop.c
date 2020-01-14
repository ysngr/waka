/* loop.c */

#include "waka.h"



void show(void)
{
    int i;

    int idxlist[max_waka];  // index list of shown waka
    int n;
    int ms[MAX_WORD];

    // prologue
    show_options();
    wait_for_newline();

    // initialize
    srand((unsigned)time(NULL));
    set_aryelem_int(idxlist, max_waka, True);
    n = Init;
    select_ms(Init, ms);

    for( i = 0; i < quiz_num; i++ ){
        // select waka and opened character
        n = select_n(n, idxlist);
        if( word_num > 0 || (ku_num > 0 && constant == False) ){
            select_ms(n, ms);
        }
        // show hidden waka
        if( ku_num > 0 ){
            show_nth_waka_mkus(n, ms);
            wait_for_newline();
        }else if( word_num > 0 ){
            show_nth_waka_mwords(n, ms);
            wait_for_newline();
        }
        // show opened waka
        show_nth_waka(n);
        if( ku_num + word_num != 0 && i != quiz_num-1 ){
            wait_for_newline();
        }
    }

    // epilogue
    printf("Press enter to end...");
    wait_for_newline();

    return ;
}


void show_options(void)
{
    printf(" === Quiz start === \n");
    printf("[options]\n");
    // [f]
    printf("File = %s\n", filename);
    // [i]
    printf("Index : ");
    if( open_index == True ){
        printf("open\n");
    }else{
        printf("close\n");
    }
    // [k [c] | w | p | v]
    printf("Open ");
    if( ku_num + word_num == 0 ){  // [p]
        printf("all\n");
    }else{
        if( ku_num > 0 ){
            // [v]
            if( versus_mode == 1 ){
                printf("first part\n");
            }else if( versus_mode == 2 ){
                printf("second part\n");
            }
            // [k]
            else{
                printf("%d ku\n", ku_num);
                // [c]
                printf("Opened place : ");
                if( constant == True ){
                    printf("constant\n");
                }else{
                    printf("unsettled\n");
                }
            }
        }
        // [w]
        else if( word_num > 0 ){
            printf("%d word", word_num);
            if( word_num != 1 ){
                printf("s");
            }
            printf("\n");
        }
        // [r]
        printf("Order = ");
        if( rand_ord == True ){
            printf("random\n");
            // [d]
            printf("Duplication = ");
            if( dupl == True ){
                printf("True\n");
            }else {
                printf("False\n");
            }
        }else{
            printf("numerical\n");
        }
        // [n]
        printf("Quiz num = %d\n", quiz_num);
    }

    printf("Press enter to start...");

    return ;
}


void show_nth_waka_mkus(int n, int *mkus)
{
    int i;
    int ku;
    int ms[MAX_WORD];

    // make ms array
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


void show_nth_waka_mwords(int n, int *mwords)
{
    int i;

    if( open_index == True ){
        printf("%3d : ", n+1);
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


void show_nth_waka(int n)
{
    int i;

    if( open_index == True ){
        printf("%3d : ", n+1);
    }

    for( i = 0; wakalist[n][i] != 0; i++ ){
        show_ntoh(wakalist[n][i]);
    }
    printf("\n");

    return ;
}


void show_ntoh(int charnum)
{
    printf("%s", hslist[charnum-1]);

    return ;
}


int select_n(int prev_idx, int *idxlist)
{
    int next_idx;

    if( is_cmpall_int(idxlist, max_waka, False) ){
        set_aryelem_int(idxlist, max_waka, True);
    }

    if( rand_ord == True ){
        do{
            next_idx = rand() % max_waka;
            if( dupl == True ){
                break;
            }
        }while( idxlist[next_idx] == False );
    }else{
        next_idx = (prev_idx + 1) % max_waka;
    }

    idxlist[next_idx] = False;

    return next_idx;
}


void select_ms(int n, int *ms)
{
    if( ku_num > 0 ){
        gen_idxs(ms, MAX_KU, ku_num, False);
        // in case ku, function gen_idxs does not use 4th parameter
        // therefore, this 4th parameter (False) is dummy value
    }

    else if( word_num > 0 ){
        if( n == Init ){
            return ;
        }
        int max_word;
        for( max_word = 0; wakalist[n][max_word] != 0; max_word++ );
        gen_idxs(ms, max_word, word_num, n);
    }

    return ;
}


void gen_idxs(int *ms, int max_idx, int num, int n)
{
    int i, idx;

    // initialize
    set_aryelem_int(ms, MAX_WORD, False);
    if( word_num > 0 ){
        // set brank position opened
        for( i = 0; i < max_idx; i++ ){
            if( wakalist[n][i] == BLANK ){
                ms[i] = True;
            }
        }
    }

    // select opened position
    if( versus_mode == 1 ){
        ms[0] = True;
        ms[1] = True;
        ms[2] = True;
    }else if( versus_mode == 2 ){
        ms[3] = True;
        ms[4] = True;
    }else{
        for( i = 0; i < num; i++ ){
            // case : all position is opened
            if( is_cmpall_int(ms, max_idx, True) ){
                break;
            }
            // select
            do{
                idx = rand() % max_idx;
            }while( ms[idx] == True );
            ms[idx] = True;
        }
    }

    return ;
}


int is_in(int n, int *ns, int size)
{
    int i;
    for( i = 0; i < size; i++ ){
        if( n == ns[i] ){
            return True;
        }
    }

    return False;
}


int is_cmpall_int(int *ary, int size, int cmp)
{
    int i;
    for( i = 0; i < size; i++ ){
        if( ary[i] != cmp ){
            return False;
        }
    }

    return True;
}


void wait_for_newline(void)
{
    char buf[MAX_BUF_SIZE];

    do{
        fgets(buf, MAX_BUF_SIZE, stdin);
    }while( buf[0] != '\n' );

    return ;
}
