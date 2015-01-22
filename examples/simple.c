
#include "../logger.h"


int main( int const argc,
          char const * const * const argv )
{
    Logger const l = logger__new( .s = argv[ 0 ],
                                  .min_severity = log_level_info.severity );

    log_info( l, "Our logger has the default logging handler (%p), "
                 "which will print messages to stderr as long as the "
                 "given level's severity is less than `min_severity`: %u",
                 l.log, l.min_severity );

    log_warning( l, "ERROR's severity is 30, so this will be printed" );

    log_debug( l, "but DEBUG's severity is 10, so this won't be printed" );

    log_error( l, "There are five pre-defined logging levels: debug (10), "
                  "info (20), warning (30), error (40), and critical (50)." );

    log_critical( l, "Each of the default logging levels has a corresponding "
                     "function that calls the `log` member of the given "
                     "Logger value with that level." );
}

