/**
This is the header for the parse tree and offers the ability to parse a given pattern string into
a pattern object.
@file parse.h
@author John Widdifield (jfwiddif)
*/

#ifndef PARSE_H
#define PARSE_H

#include "pattern.h"

/** Parse the given string into Pattern object.

    @param str string cntaining a pattern.
    @return pointer to a representation of the pattern.
***/
Pattern *parsePattern( char const *str );

#endif
