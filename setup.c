/* setup.c */

#include"waka.h"


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

int wakalist[MAX_WAKA][MAX_WORD];


static void init_wakalist(void);
static void scan_wakas(FILE*);
static void wtons(int, char*);
static int hton(char*, int*);



void init(void)
{
    FILE *fp;

    if( (fp = fopen("waka.txt", "r")) == NULL ){
        fprintf(stderr, "File cannot open.\n");
        exit(EXIT_FAILURE);
    }

    init_wakalist();
    scan_wakas(fp);

    fclose(fp);

    return ;
}


static void init_wakalist(void)
{
    int i;
    for( i = 0; i < MAX_WAKA; i++ ){
        // elements of wakalist are initialized with 0
        set_aryelem_int(wakalist[i], MAX_WORD, 0);
    }

    return ;
}


static void scan_wakas(FILE *fp)
{
    char wakabuf[MAX_BUF_SIZE];

    int i;
    for( i = 0; i < MAX_WAKA; i++ ){
        fgets(wakabuf, MAX_BUF_SIZE, fp);
        wtons(i, wakabuf);
    }

    return ;
}


static void wtons(int idx, char *waka)
{
    int i, d, cn_idx;
    int charnum[MAX_WORD];

    // initialize
    if( waka[strlen(waka)-1] == '\n' ){
        waka[strlen(waka)-1] = '\0';  // kill newline
    }

    // translate
    for( i = 0, cn_idx = 0; waka[i] != '\0'; i += d ){
        d = hton(&(waka[i]), &(charnum[cn_idx++]));
    }

    // copy to wakalist
    for( i = 0; i < cn_idx; i++ ){
        wakalist[idx][i] = charnum[i];
    }

    return ;
}


static int hton(char *hs, int *res)
{
    int i;
    int len;

    for( i = 0; i < MAX_HS; i++ ){
        len = strlen(hslist[i]);
        if( strncmp(hs, hslist[i], len) == 0 ){
            *res = i + 1;
            break;
        }
    }

    return len;
}


void set_aryelem_int(int *ary, int size, int value)
{
    int i;
    for( i = 0; i < size; i++ ){
        ary[i] = value;
    }

    return ;
}
