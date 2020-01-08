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

#define CONSONANT 0
#define VOWEL 1

#define DEFAULT_DUPLICATION False
#define DEFAULT_RANDOM_ORDER False
#define DEFAULT_CONSTANT False
#define DEFAULT_QUIZ_NUM 5
#define DEFAULT_KU_NUM 1
#define DEFAULT_WORD_NUM 0
#define DEFAULT_FILENAME "waka.txt"

#define As 10
#define A 11
#define I 12
#define U 13
#define E 14
#define O 15

#define Ks 16
#define KA 17
#define KI 18
#define KU 19
#define KE 20
#define KO 21

#define Ss 22
#define SA 23
#define SI 24
#define SU 25
#define SE 26
#define SO 27

#define Ts 28
#define TA 29
#define TI 30
#define CHI 30
#define TU 31
#define TSU 31
#define TE 32
#define TO 33

#define Ns 34
#define NA 35
#define NI 36
#define NU 37
#define NE 38
#define NO 39
#define NN 40

#define Hs 41
#define HA 42
#define HI 43
#define HU 44
#define HE 45
#define HO 46

#define Ms 47
#define MA 48
#define MI 49
#define MU 50
#define ME 51
#define MO 52

#define Ys 53
#define YA 54
#define YU 56
#define YO 58

#define Rs 59
#define RA 60
#define RI 61
#define RU 62
#define RE 63
#define RO 64

#define Ws 65
#define WA 66
#define WI 67
#define WE 69
#define WO 70

#define Gs 71
#define GA 72
#define GI 73
#define GU 74
#define GE 75
#define GO 76

#define Zs 77
#define Js 77
#define ZA 78
#define ZI 79
#define ZU 80
#define ZE 81
#define ZO 82

#define Ds 83
#define DA 84
#define DI 85
#define DU 86
#define DE 87
#define DO 88

#define Bs 89
#define BA 90
#define BI 91
#define BU 92
#define BE 93
#define BO 94

#define BLANK 95
#define HIDDEN 96


extern int max_waka;
extern int wakalist[MAX_WAKA][MAX_WORD];

extern int dupl, rand_ord, constant;
extern int quiz_num, ku_num, word_num;
extern char filename[MAX_BUF_SIZE];



/* waka.c */
void parse_option(int, char*[]);
void init_option(void);


/* setup.c */
void init(void);
void init_wakalist(void);
void scan_wakas(FILE*);
int is_valid_char(char);
int waka_to_nums(int, char*);
int parse_hton(char);
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
