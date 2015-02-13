
#include "logger.h"

#include <stdio.h>
#include <errno.h>

#include <libpp/map-lists.h>
#include <libpp/separators.h>
#include <libtypes/types.h>


Logger
logger__new_( Logger options )
{
    if ( options.log == NULL ) {
        options.log = logger__default_log;
    }
    return options;
}


int
logger__default_log( Logger const logger,
                     LogLevel const level,
                     char const * const format,
                     va_list var_args )
{
    if ( format == NULL ) {
        return EINVAL;
    } else if ( level.severity < logger.min_severity ) {
        return 0;
    }
    char const * const logger_name = logger.c;
    if ( ( logger_name != NULL && fprintf( stderr, "%s: ", logger_name ) < 0 )
      || ( level.name != NULL && fprintf( stderr, "%s: ", level.name ) < 0 )
      || vfprintf( stderr, format, var_args ) < 0
      || fprintf( stderr, "\n" ) < 0 ) {
        return EIO;
    }
    return 0;
}


#define DEF_FUNC( L, U ) \
    LOG_FUNC_DEF( L, log_level_##L )
PP_MAP_LISTS( DEF_FUNC, PP_SEP_NONE, LOG_LEVELS )
#undef DEF_FUNC


