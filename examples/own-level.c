
#include "../logger.h"


// Define the level - it could be named anything:
LogLevel const log_level_wtf = { .name = "WTF", .severity = 100 };

// Define the `log_wtf` function with the normal behavior - you could define
// your own function with whatever named to have whatever behavior you want:
LOG_FUNC_DEF( log_wtf, log_level_wtf )

int main( void )
{
    Logger const logger = logger__new( .min_severity = logseverity_info );
    log_critical( logger, "this is bad enough!" );
    // CRITICAL: this is bad enough!
    log_wtf( logger, "but this is catastrophic!!!" );
    // WTF: but this is catastrophic!!!
}

