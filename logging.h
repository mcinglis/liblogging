
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


#ifndef LIBLOGGING_LOGGING_H
#define LIBLOGGING_LOGGING_H


#include <stdio.h>
#include <stdarg.h>

#include <libtypes/types.h>


typedef struct LogSeverity {
    uchar v;
} LogSeverity;


typedef struct LogLevel {
    char const * name;
    LogSeverity severity;
} LogLevel;


typedef struct Logger {
    char const * name;
    LogSeverity min_severity;
    void ( * log )( struct Logger, LogLevel, char const * format, ... );
    // @invariant this.log != NULL
} Logger;


extern LogLevel const log_level_debug;
extern LogLevel const log_level_info;
extern LogLevel const log_level_warning;
extern LogLevel const log_level_error;
extern LogLevel const log_level_critical;


bool
log_level__is_valid( LogLevel );


bool
logger__is_valid( Logger );


LogSeverity
log_severity__from_str( char const * str,
                        bool * err );


Logger
logger__new_( Logger options );

// @public
#define logger__new( ... ) \
    logger__new_( ( Logger ){ __VA_ARGS__ } )


void
logger__default_log( Logger,
                     LogLevel,
                     char const * format,
                     ... );


// @public
#define log_debug( LOGGER, ... ) \
    ( LOGGER ).log( LOGGER, log_level_debug, __VA_ARGS__ )

// @public
#define log_info( LOGGER, ... ) \
    ( LOGGER ).log( LOGGER, log_level_info, __VA_ARGS__ )

// @public
#define log_warning( LOGGER, ... ) \
    ( LOGGER ).log( LOGGER, log_level_warning, __VA_ARGS__ )

// @public
#define log_error( LOGGER, ... ) \
    ( LOGGER ).log( LOGGER, log_level_error, __VA_ARGS__ )

// @public
#define log_critical( LOGGER, ... ) \
    ( LOGGER ).log( LOGGER, log_level_critical, __VA_ARGS__ )


#endif

