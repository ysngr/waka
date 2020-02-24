/* loop.c */

#include "waka.h"


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
    // show_options();  // TODO
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


/*
void show_options(void)  // TODO
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
*/


void show_nth_waka(int n)
{
    int ms[MAX_WORD];
    set_aryelem_int(ms, MAX_WORD, True);
    show_nth_waka_mwords(n, ms);
    printf("\n");

    return ;
}


void show_ntoh(int charnum)
{
    printf("%s", hslist[charnum-1]);

    return ;
}


int select_n(int prev_idx, int *is_nth_waka_appeared)
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
