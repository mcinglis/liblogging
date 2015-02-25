
#include "logger.h"

#include <stdio.h>
#include <errno.h>

#include <libpp/map-lists.h>
#include <libpp/separators.h>
#include <libtypes/types.h>


Logger
logger__new_( Logger options )
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
logger__default_log( Logger const logger,
                     LogLevel const level,
                     char const * const format,
                     va_list var_args )
{
    if ( format == NULL || level.severity < logger.min_severity ) { return; }

    int const saved_errno = errno;
    if ( logger.name != NULL ) {
        fprintf( logger.file, "%s: ", logger.name );
    }
    if ( level.name != NULL ) {
        fprintf( logger.file, "%s: ", level.name );
    }
    vfprintf( logger.file, format, var_args );
    fprintf( logger.file, "\n" );
    errno = saved_errno;
}


#define DEF_FUNC( L, U ) \
    LOG_FUNC_DEF( log_##L, log_level_##L )
PP_MAP_LISTS( DEF_FUNC, PP_SEP_NONE, LOG_LEVELS )
#undef DEF_FUNC


