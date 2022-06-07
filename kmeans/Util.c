/* Some useful functions to read, write PBM, PGM, PPM files
**
**
** E.B. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

char pm_getc(FILE* file)
    {
    int ich;
    char ch;

    ich = getc( file );
    if ( ich == EOF )
        pm_erreur("EOF / read error" );
    ch = (char) ich;

    if ( ch == '#' )
        {
        do
            {
            ich = getc( file );
            if ( ich == EOF )
                pm_erreur("EOF / read error" );
            ch = (char) ich;
            }
        while ( ch != '\n' && ch != '\r' );
        }

    return ch;
    }


bit pm_getbit(FILE* file)
    {
    char ch;

    do
        {
        ch = pm_getc( file );
        }
    while ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' );

    if ( ch != '0' && ch != '1' )
        pm_erreur("read error : != [0|1]" );

    return ( ch == '1' ) ? 1 : 0;
    }


unsigned char pm_getrawbyte(FILE* file)
    {
    int iby;

    iby = getc( file );
    if ( iby == EOF )
        pm_erreur("EOF / read error " );
    return (unsigned char) iby;
    }

int pm_getint( FILE* file)
    {
    char ch;
    int i;

    do
        {
        ch = pm_getc( file );
        }
    while ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' );

    if ( ch < '0' || ch > '9' )
        pm_erreur( "read error : != [0-9]" );

    i = 0;
    do
        {
        i = i * 10 + ch - '0';
        ch = pm_getc( file );
        }
    while ( ch >= '0' && ch <= '9' );

    return i;
    }

void pm_erreur(char *texte)
{
  fprintf(stderr, "\n%s \n\n", texte);
  exit(1);
}
