/* waka.c */

#include "waka.h"


int range_from, range_to, quiz_num, is_show_index;
int mode;
int versus_ku_fs;
int opened_ku, is_const_open_place;
int opened_word;
int is_show_in_order, is_show_duplication;

extern char *optarg;
extern int optind, opterr, optopt;


static void init_option(void);
static void parse_option(int, char*[]);
static void error_parse_option(char);
static void show_usage(char*);



int main(int argc, char *argv[])
{
    init_option();
    parse_option(argc, argv);
    init();
    show();

    return 0;
}


static void init_option(void)
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


static void parse_option(int argc, char *argv[])
{
    int opt;
    int is_mode_changed = False;  // mode can be changed only once from default

    opterr = 0;
    while( (opt = getopt(argc, argv, "av:k:cw:odif:t:n:h")) != -1 ){
        switch( opt ){
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
            case 'i' :
                is_show_index = True;
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
            case 'n' :
                if( (quiz_num = atoi(optarg)) <= 0 ){
                    error_parse_option('n');
                }
                break;
            case 'h' :
                show_usage(argv[0]);
                fprintf(stderr, "\nOptions:\n");
                fprintf(stderr, "  -a       : Display all parts of waka.\n");
                fprintf(stderr, "  -v <num> : Configure phrase to open. [num=1,2]\n");
                fprintf(stderr, "  -k <num> : Configure the number of ku to open. [num=1..4]\n");
                fprintf(stderr, "  -c       : Keep the constant position of ku to open.\n");
                fprintf(stderr, "  -w <num> : Configure the number of words to open. [num=1..%d]\n", MAX_WORD);
                fprintf(stderr, "  -o       : Display waka in order.\n");
                fprintf(stderr, "  -d       : Permit duplicate display.\n");
                fprintf(stderr, "  -i       : Display index of waka.\n");
                fprintf(stderr, "  -f <num> : Configure range of waka: start index. [num=1..100]\n");
                fprintf(stderr, "  -t <num> : Configure range of waka: end index. [num=1..100]\n");
                fprintf(stderr, "  -n <num> : Configure the number of quiz. [num=1..]\n");
                fprintf(stderr, "  -h       : Display this help.\n");
                fprintf(stderr, "\nDefault option settings:\n%s -v 1 -f 1 -t 100 -n 100\n", argv[0]);
                exit(1);
            case '?' :
            default :
                fprintf(stderr, "Invalid commandline option '%c'.\n", optopt);
                show_usage(argv[0]);
                exit(EXIT_FAILURE);
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


static void error_parse_option(char c)
{
    fprintf(stderr, "Invalid argument of option -%c.\n", c);
    exit(EXIT_FAILURE);
}


static void show_usage(char *program_name)
{
    int i = 0;

    fprintf(stderr, "Usage: %s [-a | -v <num> | -k <num> [-c] | -w <num>] [-o | -d]\n", program_name);

    for( i = 0; i < strlen("Usage: ")+strlen(program_name)+1; i++ ){
        fprintf(stderr, " ");
    }
    fprintf(stderr, "[-i] [-f <num>] [-t <num>] [-n <num>] [-h]\n");

    return ;
}
