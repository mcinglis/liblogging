
// Copyright 2015  Malcolm Inglis <http://minglis.id.au>
//
// This file is part of Liblogging.
//
// Liblogging is free software: you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// Liblogging is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public
// License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with Liblogging. If not, see <https://gnu.org/licenses/>.


#include "logging.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <libmacro/minmax.h>
#include <libmacro/nelem.h>
#include <libmacro/require.h>
#include <libbase/str.h>
#include <libbase/uchar.h>


LogLevel const log_level_debug    = { .name = "DEBUG",
                                      .severity = LOG_SEVERITY__DEBUG };
LogLevel const log_level_info     = { .name = "INFO",
                                      .severity = LOG_SEVERITY__INFO };
LogLevel const log_level_warning  = { .name = "WARNING",
                                      .severity = LOG_SEVERITY__WARNING };
LogLevel const log_level_error    = { .name = "ERROR",
                                      .severity = LOG_SEVERITY__ERROR };
LogLevel const log_level_critical = { .name = "CRITICAL",
                                      .severity = LOG_SEVERITY__CRITICAL };


#define LEVELS \
        log_level_debug, log_level_info, log_level_warning, \
        log_level_error, log_level_critical


void
log_severity__to_str( LogSeverity const s,
                      char * const buf,
                      size_t const buf_size )
{
    if ( buf == NULL || buf_size == 0 ) {
        return;
    }
    LogLevel const levels[] = { LEVELS };
    for ( size_t i = 0; i < NELEM( levels ); i++ ) {
        if ( s == levels[ i ].severity ) {
            char const * const n = levels[ i ].name;
            memcpy( buf, n, MIN( strlen( n ), buf_size ) );
            return;
        }
    }
    snprintf( buf, buf_size, "%u", s );
}


Result_LogSeverity
log_severity__from_str( char const * const str )
{
    LogLevel const levels[] = { LEVELS };
    for ( size_t i = 0; i < NELEM( levels ); i++ ) {
        if ( str__equal_i( levels[ i ].name, str ) ) {
            return ( Result_LogSeverity ){ .value = levels[ i ].severity };
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


Logger
logger__new_( Logger options )
{
    if ( options.log == NULL ) {
        options.log = logger__default_log;
    }
    return options;
}


void
logger__default_log( Logger const logger,
                     LogLevel const level,
                     char const * const format,
                     ... )
{
    if ( format == NULL || level.severity < logger.min_severity ) {
        return;
    }
    if ( logger.name != NULL ) {
        fprintf( stderr, "%s: ", logger.name );
    }
    if ( level.name != NULL ) {
        fprintf( stderr, "%s: ", level.name );
    }
    va_list ap;
    va_start( ap, format );
    vfprintf( stderr, format, ap );
    va_end( ap );
    fprintf( stderr, "\n" );
}


