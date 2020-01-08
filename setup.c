/* setup.c */

#include "waka.h"

int moji_state;


void init(void)
{
    FILE *fp;

    if( (fp = fopen(filename, "r")) == NULL ){
        printf("File cannot open.\n");
        exit(EXIT_FAILURE);
    }

    init_wakalist();
    scan_wakas(fp);

    fclose(fp);

    return ;
}


void init_wakalist(void)
{
    int i;
    for( i = 0; i < MAX_WAKA; i++ ){
        set_aryelem_int(wakalist[i], MAX_WORD, 0);
    }

    return ;
}


void scan_wakas(FILE *fp)
{
    int idx;
    char wakabuf[MAX_BUF_SIZE];

    idx = 0;
    while( fgets(wakabuf, MAX_BUF_SIZE, fp) != NULL ){
        if( waka_to_nums(idx, wakabuf) ){
            idx++;
        }
    }

    max_waka = idx;
    if( ku_num + word_num == 0 ){
        quiz_num = max_waka;
    }

    return ;
}


int is_valid_char(char c)
{
    if( isalpha(c) || c == ' ' ){
        return True;
    }

    return False;
}


int waka_to_nums(int idx, char *waka)
{
    int i, cn_idx;
    int n;
    int charnum[MAX_WORD];

    // initialize
    if( waka[strlen(waka)-1] == '\n' ){
        waka[strlen(waka)-1] = '\0';  // kill newline
    }
    set_aryelem_int(charnum, MAX_WORD, 0);
    moji_state = CONSONANT;
    cn_idx = 0;

    // translate
    for( i = 0; waka[i] != '\0'; i++ ){
        if( is_valid_char(waka[i]) == False ){
            return False;
        }
        if( (n = parse_hton(waka[i])) == False ){
            return False;
        }
        charnum[cn_idx] += n;
        if( moji_state ==  CONSONANT ){
            cn_idx++;
        }
    }

    // copy to wakalist
    for( i = 0; i < cn_idx; i++ ){
        wakalist[idx][i] = charnum[i];
    }

    return True;
}


int parse_hton(char c)
{
    if( moji_state == CONSONANT ){
        switch ( c ) {
            case 'a' : return A;
            case 'i' : return I;
            case 'u' : return U;
            case 'e' : return E;
            case 'o' : return O;
            case 'k' : moji_state = VOWEL; return Ks;
            case 's' : moji_state = VOWEL; return Ss;
            case 't' : moji_state = VOWEL; return Ts;
            case 'n' : moji_state = VOWEL; return Ns;
            case 'h' : moji_state = VOWEL; return Hs;
            case 'm' : moji_state = VOWEL; return Ms;
            case 'y' : moji_state = VOWEL; return Ys;
            case 'r' : moji_state = VOWEL; return Rs;
            case 'w' : moji_state = VOWEL; return Ws;
            case 'g' : moji_state = VOWEL; return Gs;
            case 'z' :
            case 'j' : moji_state = VOWEL; return Zs;
            case 'd' : moji_state = VOWEL; return Ds;
            case 'b' : moji_state = VOWEL; return Bs;
            case ' ' : return BLANK;
        }
    }else if( moji_state == VOWEL ){
        switch( c ){
            case 'a' : moji_state = CONSONANT; return 1;
            case 'i' : moji_state = CONSONANT; return 2;
            case 'u' : moji_state = CONSONANT; return 3;
            case 'e' : moji_state = CONSONANT; return 4;
            case 'o' : moji_state = CONSONANT; return 5;
            case 'n' : moji_state = CONSONANT; return 6;
        }
    }

    return False;
}


void set_aryelem_int(int *ary, int size, int value)
{
    int i;
    for( i = 0; i < size; i++ ){
        ary[i] = value;
    }

    return ;
}
