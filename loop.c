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
    printf("File = %s\n", filename);
    printf("Open ");
    if( ku_num + word_num == 0 ){
        printf("all\n");
    }else{
        if( ku_num > 0 ){
            printf("%d ku\n", ku_num);
            printf("Opened place : ");
            if( constant == True ){
                printf("constant\n");
            }else{
                printf("unsettled\n");
            }
        }else if( word_num > 0 ){
            printf("%d word", word_num);
            if( word_num != 1 ){
                printf("s");
            }
            printf("\n");
        }
        printf("Order = ");
        if( rand_ord == True ){
            printf("random\n");
            printf("Duplication = ");
            if( dupl == True ){
                printf("True\n");
            }else {
                printf("False\n");
            }
        }else{
            printf("numerical\n");
        }
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
    for( i = 0; wakalist[n][i] != 0; i++ ){
        show_ntoh(wakalist[n][i]);
    }
    printf("\n");

    return ;
}


void show_ntoh(int charnum)
{
    switch( charnum ){
        case A : printf("あ"); break;
        case I : printf("い"); break;
        case U : printf("う"); break;
        case E : printf("え"); break;
        case O : printf("お"); break;
        case KA : printf("か"); break;
        case KI : printf("き"); break;
        case KU : printf("く"); break;
        case KE : printf("け"); break;
        case KO : printf("こ"); break;
        case SA : printf("さ"); break;
        case SI : printf("し"); break;
        case SU : printf("す"); break;
        case SE : printf("せ"); break;
        case SO : printf("そ"); break;
        case TA : printf("た"); break;
        case CHI : printf("ち"); break;
        case TSU : printf("つ"); break;
        case TE : printf("て"); break;
        case TO : printf("と"); break;
        case NA : printf("な"); break;
        case NI : printf("に"); break;
        case NU : printf("ぬ"); break;
        case NE : printf("ね"); break;
        case NO : printf("の"); break;
        case HA : printf("は"); break;
        case HI : printf("ひ"); break;
        case HU : printf("ふ"); break;
        case HE : printf("へ"); break;
        case HO : printf("ほ"); break;
        case MA : printf("ま"); break;
        case MI : printf("み"); break;
        case MU : printf("む"); break;
        case ME : printf("め"); break;
        case MO : printf("も"); break;
        case YA : printf("や"); break;
        case YU : printf("ゆ"); break;
        case YO : printf("よ"); break;
        case RA : printf("ら"); break;
        case RI : printf("り"); break;
        case RU : printf("る"); break;
        case RE : printf("れ"); break;
        case RO : printf("ろ"); break;
        case WA : printf("わ"); break;
        case WI : printf("ゐ"); break;
        case WE : printf("ゑ"); break;
        case WO : printf("を"); break;
        case NN : printf("ん"); break;
        case GA : printf("が"); break;
        case GI : printf("ぎ"); break;
        case GU : printf("ぐ"); break;
        case GE : printf("げ"); break;
        case GO : printf("ご"); break;
        case ZA : printf("ざ"); break;
        case ZI : printf("じ"); break;
        case ZU : printf("ず"); break;
        case ZE : printf("ぜ"); break;
        case ZO : printf("ぞ"); break;
        case DA : printf("だ"); break;
        case DI : printf("ぢ"); break;
        case DU : printf("づ"); break;
        case DE : printf("で"); break;
        case DO : printf("ど"); break;
        case BA : printf("ば"); break;
        case BI : printf("び"); break;
        case BU : printf("ぶ"); break;
        case BE : printf("べ"); break;
        case BO : printf("ぼ"); break;
        case BLANK : printf("　"); break;
        case HIDDEN : printf("ｘ"); break;
    }

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

    set_aryelem_int(ms, MAX_WORD, False);
    if( word_num > 0 ){
        for( i = 0; i < max_idx; i++ ){
            if( wakalist[n][i] == BLANK ){
                ms[i] = True;
            }
        }
    }

    for( i = 0; i < num; i++ ){
        // opend all character
        if( is_cmpall_int(ms, max_idx, True) ){
            break;
        }
        // select opened place
        do{
            idx = rand() % max_idx;
        }while( ms[idx] == True );
        ms[idx] = True;
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
