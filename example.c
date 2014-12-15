
#include "logging.h"

int main( int const argc,
          char const * const * const argv )
{
    Logger const l = logger__new( .name = argv[ 0 ],
                                  .min_severity = 20 );

    log_info( l, "Our logger has the default logging handler (%p), "
                 "which will print messages to stderr as long as the "
                 "given level's severity is less than `min_severity`: %u",
                 l.log, l.min_severity );

    log_warning( l, "error's severity is 30, so this will be printed" );

    log_error( l, "There are five pre-defined logging levels: debug (10),"
                  "info (20), warning (30), error (40), and critical (50)." );

    log_critical( l, "Each of the default logging levels has a corresponding "
                     "macro that is shorthand for calling the `log` member of "
                     "the given Logger value." );

    // For example, this:
    log_debug( l, "hello world #%d", 42 );
    // is shorthand for:
    l.log( l, log_level_debug, "hello world #%d", 42 );
}

