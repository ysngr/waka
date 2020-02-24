/* setup.c */

#include"waka.h"


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


void init_wakalist(void)
{
    int i;
    for( i = 0; i < MAX_WAKA; i++ ){
        // elements of wakalist are initialized with 0
        set_aryelem_int(wakalist[i], MAX_WORD, 0);
    }

    return ;
}


void scan_wakas(FILE *fp)
{
    char wakabuf[MAX_BUF_SIZE];

    int i;
    for( i = 0; i < MAX_WAKA; i++ ){
        fgets(wakabuf, MAX_BUF_SIZE, fp);
        wtons(i, wakabuf);
    }

    return ;
}


void wtons(int idx, char *waka)
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


int hton(char *hs, int *res)
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
