/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set expandtab shiftwidth=4 tabstop=4: */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "thirdparty/stringencoders-3.10.3/arraytoc.h"
/**
 * raw data to base85 char map
 */
static char gsIntToChar[85];

/**
 * base 85 char to int
 */
static uint32_t gsCharToInt[256];

/*
 * Set up the above arrays
 */
void initTables()
{
    int i = 0;
    int j = 0 ;
    for (i = 0 ; i < 256 ; i++) {
        gsCharToInt[i] = 99 ;
    }

    /* i < 33 or '!' is unprintable
     * 127 is an unprintable character
     */
    for (i = '!', j = 0; j < 85 && i < 127; ++i) {

        /* You can have 8 restrictions in the following line.
         * Traditional postscript removes: ';', '&', '\', '"'
         *   so that 'last' character is 'y' ('z' is special)
         * For web/cookie applications, I recommend those plus ','
         */
        if (i == ';' || i == '&' || i == '\\' || i == '"' || i == ',') {
            continue ;
        }
        gsIntToChar[j] = (char)i ;
        gsCharToInt[i] = (uint32_t)j ;
        ++j;
    }

    if (j != 85) {
        fprintf(stderr, "Error in base85 table.  You probably had too many restrictions\n");
        exit(1);
    }
}

/**
 * beginning headers
 */
void printStart()
{
    printf("/* do not edit -- autogenerated from b85gen */\n");

}

int main()
{
    initTables();
    printStart();
    uint32_array_to_c(gsCharToInt, 256, "gsCharToInt");
    char_array_to_c(gsIntToChar, 85, "gsIntToChar");
    return 0;
}
