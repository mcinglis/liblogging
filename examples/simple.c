
#include "../logger.h"


int main( int const argc,
          char const * const * const argv )
{
    Logger const logger = logger__new( .c = argv[ 0 ],
                                       .min_severity = log_severity_info );

    log_info( logger,
            "Our logger has the default logging handler, which will print "
            "messages to stderr, prefixed with the `s` member (%s), as long "
            "as the given level's severity is less than `min_severity`: %u",
            ( char const * ) logger.c, logger.min_severity );

    log_warning( logger,
            "There are five pre-defined logging levels: debug (10), "
            "info (20), warning (30), error (40), and critical (50)." );

    log_error( logger,
            "ERROR's severity is higher than INFO's severity, so this will "
            "be printed" );

    log_debug( logger,
            "but DEBUG's severity is 10, so this won't be printed" );

    log_critical( logger,
            "Each of the default logging levels has a corresponding function "
            "that calls the `log` member of the given Logger value with that "
            "level." );
}

