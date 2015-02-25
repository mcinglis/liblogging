
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


#ifndef LIBLOGGING_LOGGER_H
#define LIBLOGGING_LOGGER_H


#include <stdio.h>
#include <stdarg.h>

#include <libpp/map-lists.h>
#include <libpp/separators.h>
#include <libtypes/types.h>

#include "log-severity.h"


typedef struct logger {
    LogSeverity min_severity;
    char const * name;
    FILE * file;
    void const * c;   // extra constant state
    void * m;         // extra mutable state
    void ( * log )( struct logger, LogLevel, char const * format, va_list );
} Logger;


Logger
logger__new_( Logger options );

// @public
#define logger__new( ... ) \
    logger__new_( ( Logger ){ __VA_ARGS__ } )


void
logger__default_log( Logger,
                     LogLevel,
                     char const * format,
                     va_list );


#define LOGGER_DEFAULT \
    { .log = logger__default_log, \
      .min_severity = LOG_SEVERITY_INFO }


#define LOG_FUNC_DEF( NAME, LEVEL ) \
    void                                                                      \
    NAME( Logger const logger,                                                \
          char const * format,                                                \
          ... )                                                               \
    {                                                                         \
        /* We assume that `va_*` will not modify `errno`; neither ISO C11 */  \
        /* nor POSIX.1-2008 suggest that they would. */                       \
        va_list ap;                                                           \
        va_start( ap, format );                                               \
        if ( logger.log != NULL ) {                                           \
            logger.log( logger, LEVEL, format, ap );                          \
        }                                                                     \
        va_end( ap );                                                         \
    }


#ifdef HAVE_ATTRIBUTE_FORMAT
#define DECL_FUNC_ATTR __attribute__((format(printf, 2, 3)))
#else
#define DECL_FUNC_ATTR
#endif

#define DECL_FUNC( L, U ) \
    void log_##L( Logger, char const * format, ... ) DECL_FUNC_ATTR;
PP_MAP_LISTS( DECL_FUNC, PP_SEP_NONE, LOG_LEVELS )
#undef DECL_FUNC


#endif

