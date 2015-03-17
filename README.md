**Liblogging** is a flexible-yet-simple logging library for C.

``` c
#include <liblogging/logger.h>

int main( int const argc,
          char const * const * const argv )
{
    Logger const logger = logger__new( .name = argv[ 0 ],
                                       .file = stdout, // default: stderr
                                       .min_severity = logseverity_info );

    log_info( logger,
            "Our logger has the default logging handler, which will print "
            "messages to `file`, prefixed with the `name` member (%s), so "
            "long as the message's level's severity is less than the "
            "logger's `min_severity` member: %u",
            logger.name, logger.min_severity );

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
```

The design of Liblogging makes it easy for you to add your own logging levels (define a new `LogLevel` value, and a corresponding function to make it easy to use), and to control *how* you handle log events (set the `log` member on your `Logger` value to your own function).

For example, to define your own logging level `wtf`:

``` c
// Define the level - it could be named anything, and needn't be `const`:
LogLevel const log_level_wtf = { .name = "WTF", .severity = 100 };

// Define the `log_wtf` function with the normal behavior - you could define
// your own function with whatever name to have whatever behavior you want:
LOG_FUNC_DEF( log_wtf, log_level_wtf )

int main( void )
{
    Logger const logger = logger__new( .min_severity = logseverity_warning );
    log_critical( logger, "this is bad enough!" );
    // CRITICAL: this is bad enough!
    log_wtf( logger, "but this is catastrophic!!!" );
    // WTF: but this is catastrophic!!!
}
```


## Releases

I'll tag the releases according to [semantic versioning](http://semver.org/spec/v2.0.0.html). All the macros preceded by `// @public`, or between `// @public begin` and `// @public end`, are considered public: they'll only change between major versions. The other macros could change any time. Non-preprocessor identifiers defined in header files are always considered public. New identifiers prefixed with `log` or `liblogging` (any case) will not warrant a major version bump.

Every version tag will be signed with [my GPG key](http://pool.sks-keyservers.net/pks/lookup?op=vindex&search=0xD020F814) (fingerprint: `0xD020F814`).


## Dependencies

`Package.json` specifies the dependencies of Liblogging: where to get them, and what version to use. I've developed a tool called [Puck](https://gitorious.org/mcinglis/puck) that will parse such a `Package.json`, download the specified repositories, check out the specified version, and, if the dependency has its own `Package.json`, repeat that process for *its* dependencies. With `puck` on your PATH, in the directory of Liblogging:

``` sh
$ puck update
$ puck execute build
# Now you can:
$ make
```

There's nothing magic to what Puck does, so if you would prefer, you can set up the dependencies manually. You just need to have the dependencies in the `deps` directory within the Liblogging directory, and have them built (if necessary) before building Liblogging.


## Collaboration

Liblogging is available at [Bitbucket](https://bitbucket.org/mcinglis/liblogging) and [GitHub](https://github.com/mcinglis/liblogging).

Questions, discussion, bug reports and feature requests are welcome at [the GitHub issue tracker](https://github.com/mcinglis/liblogging/issues), or via [emails](mailto:me@minglis.id.au).

To contribute changes, you're welcome to [email me](mailto:me@minglis.id.au) patches as per `git format-patch`, or to send me a pull request on any of the aforementioned sites. You're also welcome to just send me a link to your remote repository, and I'll merge stuff from that as I want to.

To accept notable contributions, I'll require you to assign your copyright to me. In your email/pull request and commit messages, please insert: "*I hereby irrevocably transfer to Malcolm Inglis (http://minglis.id.au) all copyrights, title, and interest, throughout the world, in these contributions to Liblogging*". If you can, please sign the email or pull request, ensuring your GPG key is publicly available.


## License

**Copyright 2015 Malcolm Inglis <http://minglis.id.au>**

Liblogging is free software: you can redistribute it and/or modify it under the terms of the [GNU Affero General Public License](https://gnu.org/licenses/agpl.html) as published by the [Free Software Foundation](https://fsf.org), either version 3 of the License, or (at your option) any later version.

Liblogging is distributed in the hope that it will be useful, but **without any warranty**; without even the implied warranty of **merchantability** or **fitness for a particular purpose**. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with Liblogging. If not, see <https://gnu.org/licenses/>.

[Contact me](mailto:me@minglis.id.au) for proprietary licensing options.

### Why AGPL?

[I believe that nonfree software is harmful](http://minglis.id.au/blog/2014/04/09/free-software-free-society.html), and I don't want to contribute to its development at all. I believe that a free society must necessarily operate on free software. I want to encourage the development of free software, and discourage the development of nonfree software.

The [GPL](https://gnu.org/licenses/gpl.html) was designed to ensure that the software stays free software; "to ensure that every user has freedom". The GPL's protections may have sufficed in 1990, but they don't in 2014. The GPL doesn't consider users of a web service to be users of the software implementing that server. Thankfully, the AGPL does.

The AGPL ensures that if Liblogging is used to implement a web service, then the entire source code of that web service must be free software. This way, I'm not contributing to nonfree software, whether it's executed locally or provided over a network.

