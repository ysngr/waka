#ifndef WAKA_H
#define WAKA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>


#define True 1
#define False 0
#define Init -1

#define MAX_WAKA 100
#define MAX_WORD 40
#define MAX_KU 5
#define MAX_BUF_SIZE 1024


#define A 1
#define I 2
#define U 3
#define E 4
#define O 5

#define KA 6
#define KI 7
#define KU 8
#define KE 9
#define KO 10

#define SA 11
#define SI 12
#define SU 13
#define SE 14
#define SO 15

#define TA 16
#define TI 17
#define TU 18
#define TE 19
#define TO 20

#define NA 21
#define NI 22
#define NU 23
#define NE 24
#define NO 25

#define HA 26
#define HI 27
#define HU 28
#define HE 29
#define HO 30

#define MA 31
#define MI 32
#define MU 33
#define ME 34
#define MO 35

#define YA 36
#define YU 37
#define YO 38

#define RA 39
#define RI 40
#define RU 41
#define RE 42
#define RO 43

#define WA 44
#define WI 45
#define WE 46
#define WO 47
#define NN 48

#define GA 49
#define GI 50
#define GU 51
#define GE 52
#define GO 53

#define ZA 54
#define ZI 55
#define ZU 56
#define ZE 57
#define ZO 58

#define DA 59
#define DI 60
#define DU 61
#define DE 62
#define DO 63

#define BA 64
#define BI 65
#define BU 66
#define BE 67
#define BO 68

#define BLANK 69
#define HIDDEN 70

#define MAX_HS 70
#define MAX_CHARNUM 5

extern const char hslist[MAX_HS][MAX_CHARNUM];

extern int max_waka;
extern int wakalist[MAX_WAKA][MAX_WORD];


#define DEFAULT_DUPLICATION False
#define DEFAULT_RANDOM_ORDER False
#define DEFAULT_CONSTANT False
#define DEFAULT_OPEN_INDEX False
#define DEFAULT_VERSUS_MODE False
#define DEFAULT_QUIZ_NUM 5
#define DEFAULT_KU_NUM 1
#define DEFAULT_WORD_NUM 0
#define DEFAULT_FILENAME "waka.txt"

extern int dupl, rand_ord, constant, open_index;
extern int quiz_num, ku_num, word_num, versus_mode;
extern char filename[MAX_BUF_SIZE];



/* waka.c */
void parse_option(int, char*[]);
void init_option(void);


/* setup.c */
void init(void);
void init_wakalist(void);
void scan_wakas(FILE*);
int wtons(int, char*);
int hton(char*, int*);
extern void set_aryelem_int(int*, int, int);


/* loop.c */
void show(void);
void show_options(void);
void show_nth_waka_mkus(int, int*);
void show_nth_waka_mwords(int, int*);
void show_nth_waka(int);
void show_ntoh(int);
int select_n(int, int*);
void select_ms(int, int*);
void gen_idxs(int*, int, int, int);
int is_in(int, int*, int);
int is_cmpall_int(int*, int, int);
void wait_for_newline(void);


#endif
