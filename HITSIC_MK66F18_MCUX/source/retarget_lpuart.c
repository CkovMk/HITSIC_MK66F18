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
#include "inc_stdlib.hpp"
#include "hitsic_common.h"

#define RETARGET_INST   (LPUART0)

#ifdef __cplusplus
extern "C"{
#endif

#if defined (__NEWLIB__)

// ******************************************************************
// Redlib C Library function : __sys_write
// Newlib C library function : _write
//
// Function called by bottom level of printf routine within C library
// to write multiple characters.
// ******************************************************************
int _write(int iFileHandle, char *pcBuffer, int iLength)
{
    // Check that iFileHandle == 1 to confirm that read is from stdout
    if(1 == iFileHandle)
    {
    if(kStatus_Success == LPUART_WriteBlocking(RETARGET_INST, pcBuffer, iLength))
    {
        return 0;
    }
    else
    {
        // Function returns number of unwritten bytes if error
        return iLength;
    }
    }
}

// ******************************************************************
// Function _read
//
// Called by bottom level of scanf routine within Newlib C library
// to read multiple characters.
// ******************************************************************
int _read(int iFileHandle, char *pcBuffer, int iLength)
{
	// Check that iFileHandle == 0 to confirm that read is from stdin
    if(0 == iFileHandle)
    {
	if(kStatus_Success == LPUART_ReadBlocking(RETARGET_INST, pcBuffer, iLength))
	{
	    return iLength;
	}
	else
	{
	    return 0;// Count of characters read
	}
    }
}

#endif // ! __NEWLIB__


#ifdef __cplusplus
}
#endif
