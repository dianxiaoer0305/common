/* $Id: utils.c 2433 2010-03-28 20:57:36Z aturner $ */

/*
 * Copyright (c) 2001-2010 Aaron Turner.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright owners nor the names of its
 *    contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "defines.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#ifdef DEBUG
extern int debug;
#endif

/**
 * this is wrapped up in a #define safe_malloc
 * This function, detects failures to malloc memory and zeros out the
 * memory before returning
 */

void *
_our_safe_malloc(size_t len, const char *funcname, const int line, const char *file)
{
    u_char *ptr;

    if ((ptr = malloc(len)) == NULL) {
        fprintf(stderr, "ERROR in %s:%s() line %d: Unable to malloc() %zu bytes", file, funcname, line, len);
        exit(-1);
    }

    /* zero memory */
    memset(ptr, 0, len);

    /* wrapped inside an #ifdef for better performance */
    dbgx(5, "Malloc'd %zu bytes in %s:%s() line %d", len, file, funcname, line);

    return (void *)ptr;
}

/**
 * this is wrapped up in a #define safe_realloc
 * This function, detects failures to realloc memory and zeros
 * out the NEW memory if len > current len.  As always, remember
 * to use it as:
 * ptr = safe_realloc(ptr, size)
 */
void *
_our_safe_realloc(void *ptr, size_t len, const char *funcname, const int line, const char *file)
{

    if ((ptr = realloc(ptr, len)) == NULL) {
        fprintf(stderr, "ERROR: in %s:%s() line %d: Unable to remalloc() buffer to %zu bytes", file, funcname, line, len);
        exit(-1);
    }

    dbgx(5, "Remalloc'd buffer to %zu bytes in %s:%s() line %d", len, file, funcname, line);

    return ptr;
}

/**
 * this is wrapped up in a #define safe_strdup
 * This function, detects failures to realloc memory
 */
char *
_our_safe_strdup(const char *str, const char *funcname, const int line, const char *file)
{
    char *newstr;

    if ((newstr = (char *)malloc(strlen(str) + 1)) == NULL) {
        fprintf(stderr, "ERROR in %s:%s() line %d: Unable to strdup() %zu bytes\n", file, funcname, line, strlen(str));
        exit(-1);
    }

    memcpy(newstr, str, strlen(str) + 1);

    return newstr;

}

/**
 * calls free and sets to NULL.
 */
void
_our_safe_free(void *ptr, const char *funcname, const int line, const char *file)
{
    if (ptr == NULL) {
        fprintf(stderr, "ERROR in %s:%s() line %d: Unable to call free on a NULL ptr", file, funcname, line);
        exit(-1);
    }

    free(ptr);
    ptr = NULL;
}

