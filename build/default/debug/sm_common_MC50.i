# 1 "sm_common_MC50.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "sm_common_MC50.c" 2







# 1 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stdio.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stdio.h" 2 3






# 1 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\features.h" 1 3
# 10 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stdio.h" 2 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stdio.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 1 3





typedef void * va_list[1];




typedef void * __isoc_va_list[1];
# 122 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 137 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long ssize_t;
# 168 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 246 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long off_t;
# 399 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct _IO_FILE FILE;
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stdio.h" 2 3
# 52 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stdio.h" 3
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int ungetc(int, FILE *);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);

char *fgets(char *restrict, int, FILE *restrict);

char *gets(char *);


int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

__attribute__((__format__(__printf__, 1, 2)))
int printf(const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int fprintf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int sprintf(char *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 3, 4)))
int snprintf(char *restrict, size_t, const char *restrict, ...);

__attribute__((__format__(__printf__, 1, 0)))
int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 2, 0)))
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 3, 0)))
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

__attribute__((__format__(__scanf__, 1, 2)))
int scanf(const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int fscanf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int sscanf(const char *restrict, const char *restrict, ...);

__attribute__((__format__(__scanf__, 1, 0)))
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__scanf__, 2, 0)))
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);
# 8 "sm_common_MC50.c" 2


# 1 "./sm_common.h" 1
# 15 "./sm_common.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stddef.h" 1 3
# 19 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stddef.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 18 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int wchar_t;
# 132 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\bits/alltypes.h" 3
typedef int ptrdiff_t;
# 19 "C:\\Program Files\\Microchip\\xc8\\v2.36\\pic\\include\\c99\\stddef.h" 2 3
# 15 "./sm_common.h" 2
# 27 "./sm_common.h"
typedef enum {ev_NULL,
                    ev_ParameterIsSelected,
                    ev_ParameterIsEdited,
                    ev_CancelEdition,
                    ev_ParameterIsSaved,
                    ev_showCounter,
                    ev_goto_MenuConfig,
                    ev_goto_StandBy,
                    ev_addRemotes,
                    ev_NextRemote,
                    ev_GateClosed,
                    ev_GateOpened,
                    ev_OpenGate,
                    ev_StopGate,
                    ev_CloseGate,
                    ev_ClosedGate,
                    ev_ErrorGate,
                    ev_MotorIsOpen,
                    ev_ErrorLearning,
                    ev_LearningComplete,
                    ev_SartLearning,
                    } sm_event_t;



typedef enum {
  HIST_NONE=0,
  HIST_SHALLOW,
  HIST_DEEP
} sm_history_t;
# 73 "./sm_common.h"
typedef struct {
 int current_state;
 int initial_state;
 int last_event;
 sm_history_t history;

 void* parent_machine;
 int parent_state;
} sm_t;
# 97 "./sm_common.h"
void sm_init(sm_t *psm, int initial_state, sm_history_t hist_mode);
# 108 "./sm_common.h"
void sm_restart(sm_t *psm);






int sm_get_current_state(sm_t *psm);
# 125 "./sm_common.h"
void sm_send_event(sm_t *psm, int event);
# 10 "sm_common_MC50.c" 2


void sm_init(sm_t *psm, int initial_state, sm_history_t hist_mode)
{
 psm->initial_state = initial_state;
 psm->history = hist_mode;
 psm->current_state = initial_state;


 psm->parent_machine = ((void*)0);
 sm_restart(psm);
}

void sm_restart(sm_t *psm){
 if(psm->history == HIST_NONE){
  psm->current_state = psm->initial_state;
 }
 psm->last_event = 0;
}

int sm_get_current_state(sm_t *psm){
 return psm->current_state;
}

void sm_send_event(sm_t *psm, int event)
{
 if(( psm->parent_machine == ((void*)0)) || (sm_get_current_state(psm->parent_machine)==psm->parent_state))

 {
  psm->last_event = event;
 }
}
