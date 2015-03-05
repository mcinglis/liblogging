
#include "logseverity.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libpp/map-lists.h>
#include <libpp/separators.h>
#include <libtypes/types.h>
#include <libmacro/assert.h>
#include <libmacro/minmax.h>
#include <libmacro/nelem.h>
#include <libstr/str.h>


#define DEF_SEV( L, U ) \
    LogSeverity const logseverity_##L = LOGSEVERITY_##U;
PP_MAP_LISTS( DEF_SEV, PP_SEP_NONE, LOGLEVELS )
#undef DEF_SEV


#define DEF_LEVEL( L, U ) \
    LogLevel const loglevel_##L = { \
        .name = #U, \
        .severity = LOGSEVERITY_##U \
    };
PP_MAP_LISTS( DEF_LEVEL, PP_SEP_NONE, LOGLEVELS )
#undef DEF_LEVEL


LogLevel const loglevels[] = {
#define EL( L, U ) \
    { .name = #U, .severity = LOGSEVERITY_##U }
PP_MAP_LISTS( EL, PP_SEP_COMMA, LOGLEVELS )
#undef EL
};


LogSeverity logseverity__min_bound( void ) { return INT_MIN; }
LogSeverity logseverity__max_bound( void ) { return INT_MAX; }


char const *
str__from_logseverity( LogSeverity const s )
{
    for ( size_t i = 0; i < NELEM( loglevels ); i++ ) {
        LogLevel const level = loglevels[ i ];
        if ( s == level.severity ) {
            return level.name;
        }
    }
    return "unknown";
}


LogSeverity
logseverity__from_str( char const * const str )
{
    ASSERT( str != NULL );

    for ( size_t i = 0; i < NELEM( loglevels ); i++ ) {
        LogLevel const level = loglevels[ i ];
        if ( str__equal_i( level.name, str ) ) {
            return level.severity;
        }
    }

    char * end_ptr = NULL;
    errno = 0;
    long const x = strtol( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( ( x < 0 && x < logseverity__min_bound() )
             || ( x > logseverity__max_bound() ) ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}


void
logseverity__arg_parse( char const * const name,
                        char const * const value,
                        void * const vlogsev )
{
    ASSERT( value != NULL, vlogsev != NULL );

    LogSeverity * const v = vlogsev;
    *v = logseverity__from_str( value );
}

