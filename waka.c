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

int range_from, range_to, quiz_num, is_show_index;
int mode;
int versus_ku_fs;
int opened_ku, is_const_open_place;
int opened_word;
int is_show_in_order, is_show_duplication;


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
    // set default value

    range_from = 0;
    range_to = 99;
    quiz_num = 100;
    is_show_index = False;

    mode = MODE_VERSUS;
    versus_ku_fs = 1;
    opened_ku = 0;
    is_const_open_place = False;
    opened_word = 0;

    is_show_in_order = False;
    is_show_duplication = False;

    return ;
}


void parse_option(int argc, char *argv[])
{
    int opt;
    int is_mode_changed = False;  // mode can be changed only once from default

    opterr = 0;
    while( (opt = getopt(argc, argv, "in:f:t:av:k:cw:odh")) != -1 ){
        switch( opt ){
            case 'i' :
                is_show_index = True;
                break;
            case 'n' :
                if( (quiz_num = atoi(optarg)) <= 0 ){
                    error_parse_option('n');
                }
                break;
            case 'f' :
                range_from = atoi(optarg);
                if( range_from <= 0 || MAX_WAKA < range_from ){
                    error_parse_option('f');
                }
                range_from--;
                break;
            case 't' :
                range_to = atoi(optarg);
                if( range_to <= 0 || MAX_WAKA < range_to ){
                    error_parse_option('t');
                }
                range_to--;
                break;
            case 'a' :
                if( is_mode_changed && mode != MODE_SHOW_ALL ){
                    error_parse_option('a');
                }else{
                    is_mode_changed = True;
                    mode = MODE_SHOW_ALL;
                }
                break;
            case 'v' :
                versus_ku_fs = atoi(optarg);
                if( versus_ku_fs != 1 && versus_ku_fs != 2 ){
                    error_parse_option('v');
                }
                if( is_mode_changed && mode != MODE_VERSUS ){
                    error_parse_option('v');
                }else{
                    is_mode_changed = True;
                    mode = MODE_VERSUS;
                }
                break;
            case 'k' :
                opened_ku = atoi(optarg);
                if( opened_ku <= 0 || opened_ku >= 5 ){
                    error_parse_option('k');
                }
                if( is_mode_changed && mode != MODE_KU ){
                    error_parse_option('k');
                }else{
                    is_mode_changed = True;
                    mode = MODE_KU;
                }
                break;
            case 'c' :
                is_const_open_place = True;
                if( is_mode_changed && mode != MODE_KU ){
                    error_parse_option('c');
                }else{
                    is_mode_changed = True;
                    mode = MODE_KU;
                }
                break;
            case 'w' :
                if( (opened_word = atoi(optarg)) <= 0 ){
                    error_parse_option('w');
                }
                if( is_mode_changed && mode != MODE_WORD ){
                    error_parse_option('w');
                }else{
                    is_mode_changed = True;
                    mode = MODE_WORD;
                }
                break;
            case 'o' :
                is_show_in_order = True;
                break;
            case 'd' :
                is_show_duplication = True;
                break;
            case 'h' :
            case '?' :
            default :
                // TODO
                fprintf(stderr, "TODO write help.\n");
                exit(1);
        }
    }

    if( range_to < range_from ){
        int temp = range_to;
        range_to = range_from;
        range_from = temp;
    }

    if( mode == MODE_SHOW_ALL ){
        quiz_num = range_to - range_from + 1;
    }

    return ;
}


void error_parse_option(char c)
{
    fprintf(stderr, "Invalid argument of option -%c.\n", c);
    exit(EXIT_FAILURE);
}
