/* waka.c */

#include "waka.h"

const char hslist[MAX_HS][MAX_CHARNUM] = {
    {"あ"}, {"い"}, {"う"}, {"え"}, {"お"},  // 01 ~ 05
    {"か"}, {"き"}, {"く"}, {"け"}, {"こ"},  // 06 ~ 10
    {"さ"}, {"し"}, {"す"}, {"せ"}, {"そ"},  // 11 ~ 15
    {"た"}, {"ち"}, {"つ"}, {"て"}, {"と"},  // 16 ~ 20
    {"な"}, {"に"}, {"ぬ"}, {"ね"}, {"の"},  // 21 ~ 25
    {"は"}, {"ひ"}, {"ふ"}, {"へ"}, {"ほ"},  // 26 ~ 30
    {"ま"}, {"み"}, {"む"}, {"め"}, {"も"},  // 31 ~ 35
    {"や"}, {"ゆ"}, {"よ"},  // 36 ~ 38
    {"ら"}, {"り"}, {"る"}, {"れ"}, {"ろ"},  // 39 ~ 43
    {"わ"}, {"ゐ"}, {"ゑ"}, {"を"}, {"ん"},  // 44 ~ 48
    {"が"}, {"ぎ"}, {"ぐ"}, {"げ"}, {"ご"},  // 49 ~ 53
    {"ざ"}, {"じ"}, {"ず"}, {"ぜ"}, {"ぞ"},  // 54 ~ 58
    {"だ"}, {"ぢ"}, {"づ"}, {"で"}, {"ど"},  // 59 ~ 63
    {"ば"}, {"び"}, {"ぶ"}, {"べ"}, {"ぼ"},  // 64 ~ 68
    {"　"}, {"ｘ"}  // 69 ~ 70
};


int max_waka;
int wakalist[MAX_WAKA][MAX_WORD];

int dupl, rand_ord, constant, open_index, versus_mode;
int quiz_num, ku_num, word_num;
char filename[MAX_BUF_SIZE];

extern char *optarg;
extern int optind, opterr, optopt;



int main(int argc, char *argv[])
{
    init_option();
    parse_option(argc, argv);
    init();
    show();

    return 0;
}



void init_option(void)
{
    dupl = DEFAULT_DUPLICATION;
    rand_ord = DEFAULT_RANDOM_ORDER;
    constant = DEFAULT_CONSTANT;
    open_index = DEFAULT_OPEN_INDEX;
    versus_mode = DEFAULT_VERSUS_MODE;
    quiz_num = DEFAULT_QUIZ_NUM;
    ku_num = DEFAULT_KU_NUM;
    word_num = DEFAULT_WORD_NUM;
    strncpy(filename, DEFAULT_FILENAME, MAX_BUF_SIZE);

    return ;
}


void parse_option(int argc, char *argv[])
{
    int opt;

    opterr = 0;
    while( (opt = getopt(argc, argv, "cdf:hik:n:prvw:")) != -1 ){
        switch( opt ){
            case 'c' :
                constant = True;
                break;
            case 'd' :
                dupl = True;
                break;
            case 'f' :
                strncpy(filename, optarg, MAX_BUF_SIZE);
                break;
            case 'i' :
                open_index = True;
                break;
            case 'k' :
                ku_num = atoi(optarg);
                if( ku_num <= 0 || 5 <= ku_num ){
                    fprintf(stderr, "Invalid argument of option -k.\n");
                    exit(EXIT_FAILURE);
                }
                word_num = False;
                break;
            case 'n' :
                if( (quiz_num = atoi(optarg)) <= 0 ){
                    fprintf(stderr, "Invalid argument of option -n.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'p' :
                ku_num = False;
                word_num = False;
                break;
            case 'r' :
                rand_ord = True;
                break;
            case 'v' :
                versus_mode = True;
                ku_num = 3;
                word_num = False;
                break;
            case 'w' :
                if( (word_num = atoi(optarg)) <= 0 ){
                    fprintf(stderr, "Invalid argument of option -w.\n");
                    exit(EXIT_FAILURE);
                }
                ku_num = False;
                break;
            case 'h' :
            case '?' :
            default :
                fprintf(stderr, "Usage : %s [-d] [-f filename] [-k ku_num [-c] | -w word_num | -p | -v] [-h] [-i] [-n quiz_num] [-r]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    return ;
}
