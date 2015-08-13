
#include "logger.h"

#include <stdio.h>
#include <errno.h>

#include <libpp/map-lists.h>
#include <libpp/separators.h>
#include <libtypes/types.h>
#include <libmacro/assert.h>


Logger
logger__new_(
        Logger options )
{
    if ( options.file == NULL ) {
        options.file = stderr;
    }
    if ( options.log == NULL ) {
        options.log = logger__default_log;
    }
    return options;
}


void
logger__default_log(
        Logger const logger,
        LogLevel const level,
        char const * const format,
        va_list var_args )
{
    if ( format == NULL || level.severity < logger.min_severity ) { return; }

    int const saved_errno = errno;
    FILE * const file = logger.file ? logger.file : stderr;
    if ( logger.name != NULL ) {
        fprintf( file, "%s: ", logger.name );
    }
    if ( level.name != NULL ) {
        fprintf( file, "%s: ", level.name );
    }
    vfprintf( file, format, var_args );
    fprintf( file, "\n" );
    errno = saved_errno;
}


void
logger__parse_log_severity(
        Logger * const logger,
        char const * const str )
{
    ASSERT( logger != NULL );

    LogSeverity const ls = logseverity__from_str( str );
    if ( errno ) { return; }
    logger->min_severity = ls;
}


#define DEF_FUNC( L, U ) \
    LOG_FUNC_DEF( log_##L, loglevel_##L )
PP_MAP_LISTS( DEF_FUNC, PP_SEP_NONE, LOGLEVELS )
#undef DEF_FUNC


