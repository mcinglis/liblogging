
#include "log-severity.h"

#include <stdio.h>
#include <string.h>

#include <libpp/map-lists.h>
#include <libpp/separators.h>
#include <libtypes/types.h>
#include <libmacro/minmax.h>
#include <libmacro/nelem.h>
#include <libbase/uchar.h>
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


void
log_severity__to_str( LogSeverity const s,
                      char * const buf,
                      size_t const buf_size )
{
    if ( buf == NULL || buf_size == 0 ) {
        return;
    }
    for ( size_t i = 0; i < NELEM( log_levels ); i++ ) {
        if ( s == log_levels[ i ].severity ) {
            char const * const n = log_levels[ i ].name;
            memcpy( buf, n, MIN( strlen( n ), buf_size ) );
            return;
        }
    }
    snprintf( buf, buf_size, "%u", s );
}


Result_LogSeverity
log_severity__from_str( char const * const str )
{
    for ( size_t i = 0; i < NELEM( log_levels ); i++ ) {
        if ( str__equal_i( log_levels[ i ].name, str ) ) {
            return ( Result_LogSeverity ){ .value = log_levels[ i ].severity };
        }
    }
    Result_uchar const r = uchar__from_str( str );
    return ( Result_LogSeverity ){ .value = r.value, .error = r.error };
}


LogSeverity
log_severity__from_str_e( char const * const str,
                          int * const err )
{
    Result_LogSeverity const r = log_severity__from_str( str );
    if ( err != NULL ) {
        *err = r.error;
    }
    return r.value;
}

