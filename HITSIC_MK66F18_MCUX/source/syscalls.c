/**
 * Copyright 2018 - 2020 HITSIC
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <inc_stdlib.hpp>
#include "hitsic_common.h"
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

int _lseek(int file, int ptr, int dir)
{
    return 0;
}
int _open(const char *name, int flags, int mode)
{
    return -1;
}
int _read(int file, char *ptr, int len)
{
    return 0;
}
int _write(int file, char *ptr, int len)
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
