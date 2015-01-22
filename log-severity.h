
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

typedef struct {
    LogLevel value;
    bool nothing;
} Maybe_LogLevel;

typedef struct {
    LogLevel value;
    int error;
} Result_LogLevel;


// Add or remove default levels here: (but for your own application, it would
// probably be best to define your own levels directly)

#define LOG_SEVERITY_DEBUG     10
#define LOG_SEVERITY_INFO      20
#define LOG_SEVERITY_WARNING   30
#define LOG_SEVERITY_ERROR     40
#define LOG_SEVERITY_CRITICAL  50

#define LOG_LEVELS \
    ( debug,    DEBUG ), \
    ( info,     INFO ), \
    ( warning,  WARNING ), \
    ( error,    ERROR ), \
    ( critical, CRITICAL )


#define DECL_SEV( L, U ) \
    extern LogSeverity const log_severity_##L;
PP_MAP_LISTS( DECL_SEV, PP_SEP_NONE, LOG_LEVELS )
#undef DECL_SEV


#define DECL_LEVEL( L, U ) \
    extern LogLevel const log_level_##L;
PP_MAP_LISTS( DECL_LEVEL, PP_SEP_NONE, LOG_LEVELS )
#undef DECL_LEVEL


extern LogLevel const log_levels[ PP_COUNT( LOG_LEVELS ) ];


void
log_severity__to_str( LogSeverity,
                      char * buf,
                      size_t buf_size );


Result_LogSeverity
log_severity__from_str( char const * str );


LogSeverity
log_severity__from_str_e( char const * str,
                          int * err );


#endif

