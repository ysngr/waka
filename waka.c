/* waka.c */

#include "waka.h"

int max_waka;
int wakalist[MAX_WAKA][MAX_WORD];

int dupl, rand_ord, constant;
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
    while( (opt = getopt(argc, argv, "cdf:hk:n:prw:")) != -1 ){
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
                fprintf(stderr, "Usage : %s [-d] [-f filename] [-k ku_num [-c] | -w word_num | -p] [-h] [-n quiz_num] [-r]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    return ;
}
