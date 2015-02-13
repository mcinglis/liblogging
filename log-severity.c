
#include "log-severity.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libpp/map-lists.h>
#include <libpp/separators.h>
#include <libtypes/types.h>
#include <libmacro/minmax.h>
#include <libmacro/nelem.h>
#include <libbase/str.h>

#include "log-severity.h"


#define DEF_SEV( L, U ) \
    LogSeverity const log_severity_##L = LOG_SEVERITY_##U;
PP_MAP_LISTS( DEF_SEV, PP_SEP_NONE, LOG_LEVELS )
#undef DEF_SEV


#define DEF_LEVEL( L, U ) \
    LogLevel const log_level_##L = { \
        .name = #U, \
        .severity = LOG_SEVERITY_##U \
    };
PP_MAP_LISTS( DEF_LEVEL, PP_SEP_NONE, LOG_LEVELS )
#undef DEF_LEVEL


LogLevel const log_levels[] = {
#define EL( L, U ) \
    { .name = #U, .severity = LOG_SEVERITY_##U }
PP_MAP_LISTS( EL, PP_SEP_COMMA, LOG_LEVELS )
#undef EL
};


LogSeverity log_severity__min_bound( void ) { return INT_MIN; }
LogSeverity log_severity__max_bound( void ) { return INT_MAX; }


char const *
log_severity__to_conststr( LogSeverity const s )
{
    for ( size_t i = 0; i < NELEM( log_levels ); i++ ) {
        LogLevel const level = log_levels[ i ];
        if ( s == level.severity ) {
            return level.name;
        }
    }
    return NULL;
}


void
log_severity__to_str( LogSeverity const sev,
                      char * const buf,
                      size_t const buf_size )
{
    if ( buf_size == 0 ) { return; }
    if ( buf == NULL ) { errno = EINVAL; return; }

    char const * const str = log_severity__to_conststr( sev );
    if ( str == NULL ) {
        snprintf( buf, buf_size, "%d", sev );
    } else {
        memcpy( buf, str, MIN( strlen( str ), buf_size ) );
    }
}


LogSeverity
log_severity__from_str( char const * const str )
{
    for ( size_t i = 0; i < NELEM( log_levels ); i++ ) {
        LogLevel const level = log_levels[ i ];
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
    } else if ( ( x < 0 && x < log_severity__min_bound() )
             || ( x > log_severity__max_bound() ) ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

