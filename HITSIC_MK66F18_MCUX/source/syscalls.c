#include "hitsic_common.h"
#include "inc_stdlib.h"
#include "ff.h"

#include  <sys/unistd.h>

#if 0 // DISABLED. this is not completed yet.

namespace std
{
struct __FILE
{
    FIL fatfsFIL;
    BYTE mode;
    FRESULT fr;
};

FILE __stdout;
FILE __stdin;
FILE __stderr;

#ifdef __cplusplus
extern "C"
{
#endif

//char *__env[1] =
//{ 0 };
//char **environ = __env;

/* Provide prototypes for most of the _<systemcall> names that are
 provided in newlib for some compilers.  */
int close(int file)
{

}

int lseek(int file, int ptr, int dir)
{
    return 0;
}
int open(const char *name, int flags, int mode)
{
    return -1;
}
int read(int file, char *ptr, int len)
{
    return 0;
}
int write(int file, char *ptr, int len)
{

    return len;
}

void _exit(void)
{
    while (1);
}

void _kill(void)
{

}

void _fstat(void)
{

}

#ifdef __cplusplus
}
#endif
} // ! namesapce std

#endif // ! ifdef 0
