
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


#ifndef LIBLOGGING_LOG_SEVERITY_H
#define LIBLOGGING_LOG_SEVERITY_H


#include <libpp/count.h>
#include <libpp/map-lists.h>
#include <libpp/separators.h>
#include <libtypes/types.h>


typedef int LogSeverity;

typedef struct loglevel {
    char const * name;
    LogSeverity severity;
} LogLevel;


// Add or remove default levels here: (but for your own application, it would
// probably be best to define your own levels directly)

// @public begin

#define LOGSEVERITY_DEBUG     10
#define LOGSEVERITY_INFO      20
#define LOGSEVERITY_WARNING   30
#define LOGSEVERITY_ERROR     40
#define LOGSEVERITY_CRITICAL  50

#define LOGLEVELS \
    ( debug,    DEBUG ), \
    ( info,     INFO ), \
    ( warning,  WARNING ), \
    ( error,    ERROR ), \
    ( critical, CRITICAL )

// @public end


#define DECL_SEV( L, U ) \
    extern LogSeverity const logseverity_##L;
PP_MAP_LISTS( DECL_SEV, PP_SEP_NONE, LOGLEVELS )
#undef DECL_SEV


#define DECL_LEVEL( L, U ) \
    extern LogLevel const loglevel_##L;
PP_MAP_LISTS( DECL_LEVEL, PP_SEP_NONE, LOGLEVELS )
#undef DECL_LEVEL


extern LogLevel const loglevels[ PP_COUNT( LOGLEVELS ) ];


LogSeverity
logseverity__min_bound( void );


LogSeverity
logseverity__max_bound( void );


LogSeverity
logseverity__from_str( char const * str );


char const *
str__from_logseverity( LogSeverity );


#endif

