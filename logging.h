
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


#ifndef LIBLOGGING_LOGGING_H
#define LIBLOGGING_LOGGING_H


#include <stdio.h>
#include <stdarg.h>

#include <libtypes/types.h>


typedef uchar LogSeverity;

typedef struct {
    LogSeverity value;
    bool nothing;
} Maybe_LogSeverity;

typedef struct {
    LogSeverity value;
    int error;
} Result_LogSeverity;


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


#define LOG_SEVERITY__DEBUG     10
#define LOG_SEVERITY__INFO      20
#define LOG_SEVERITY__WARNING   30
#define LOG_SEVERITY__ERROR     40
#define LOG_SEVERITY__CRITICAL  50


void
log_severity__to_str( LogSeverity,
                      char * buf,
                      size_t buf_size );


Result_LogSeverity
log_severity__from_str( char const * str );


LogSeverity
log_severity__from_str_e( char const * str,
                          int * err );


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
    if ( ( LOGGER ).log != NULL ) { \
        ( LOGGER ).log( LOGGER, log_level_debug, __VA_ARGS__ ); \
    }

// @public
#define log_info( LOGGER, ... ) \
    if ( ( LOGGER ).log != NULL ) { \
        ( LOGGER ).log( LOGGER, log_level_info, __VA_ARGS__ ); \
    }

// @public
#define log_warning( LOGGER, ... ) \
    if ( ( LOGGER ).log != NULL ) { \
        ( LOGGER ).log( LOGGER, log_level_warning, __VA_ARGS__ ); \
    }

// @public
#define log_error( LOGGER, ... ) \
    if ( ( LOGGER ).log != NULL ) { \
        ( LOGGER ).log( LOGGER, log_level_error, __VA_ARGS__ ); \
    }

// @public
#define log_critical( LOGGER, ... ) \
    if ( ( LOGGER ).log != NULL ) { \
        ( LOGGER ).log( LOGGER, log_level_critical, __VA_ARGS__ ); \
    }


#endif

