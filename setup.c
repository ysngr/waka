/* setup.c */

#include"waka.h"


void init(void)
{
    FILE *fp;

    if( (fp = fopen(filename,"r")) == NULL ){
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
        if( wtons(idx, wakabuf) ){
            idx++;
        }
    }

    max_waka = idx;
    if( ku_num + word_num == 0 ){
        quiz_num = max_waka;
    }

    return ;
}


int wtons(int idx, char *waka)
{
    int i, d, cn_idx;
    int charnum[MAX_WORD];

    // initialize
    if( waka[strlen(waka)-1] == '\n' ){
        waka[strlen(waka)-1] = '\0';  // kill newline
    }

    // translate
    for( i = 0, cn_idx = 0; waka[i] != '\0'; i += d ){
        // todo commentout
        if( (d = hton(&(waka[i]), &(charnum[cn_idx++]))) == False ){
            return False;
        }
    }

    // copy to wakalist
    for( i = 0; i < cn_idx; i++ ){
        wakalist[idx][i] = charnum[i];
    }

    return True;
}


int hton(char *hs, int *res)
{
    int i;
    int len;

    for( i = 0; i < MAX_HS; i++ ){
        len = strlen(hslist[i]);
        if( strncmp(hs, hslist[i], len) == 0 ){
            *res = i + 1;
            return len;
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
