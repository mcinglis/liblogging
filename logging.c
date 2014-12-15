
// Copyright 2014  Malcolm Inglis <http://minglis.id.au>
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
#include <limits.h>

#include <libmacro/require.h>
#include <libbase/str.h>
#include <libbase/uchar.h>


LogLevel const log_level_debug    = { .name = "debug",    .severity = { 10 } };
LogLevel const log_level_info     = { .name = "info",     .severity = { 20 } };
LogLevel const log_level_warning  = { .name = "warning",  .severity = { 30 } };
LogLevel const log_level_error    = { .name = "error",    .severity = { 40 } };
LogLevel const log_level_critical = { .name = "critical", .severity = { 50 } };


LogSeverity
log_severity__from_str( char const * const str,
                        bool * const err )
{
    return ( LogSeverity ){ uchar__from_str( str, err ) };
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
    if ( format == NULL || level.severity.v < logger.min_severity.v ) {
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

