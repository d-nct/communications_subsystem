# Logger Lib

## `Logger` Class
### Overview
The `Logger` class, defined in the "Log.h" file, provides a flexible logging mechanism for a C++ application. It supports logging messages with 4 log levels for serial communication:
1. `LOG_ERROR`: Prints errors only.
2. `LOG_WARNING`: Prints errors and warnings only.
3. `LOG_INFO`: Prints errors, warnings and general purpose informations, such as telemetry detais.
4. `LOG_DEBUG`: Prints everything, including boring and verborragic debug details.

Additionally, the class includes methods to set the minimum log level, convert log levels and other status indicators to strings, and maintains the current minimum log level threshold.

The enum `LogLevel_t` is defined in `_types.h`.

### Methods and Members
See the doxygen in `CommunicationRF.h`.

### Usage
1. Use `log()` to print whith `[<LogLevel>] <message>\n` and `print()` to print with `<message>` (without `\n`), both with differents log levels.

2. Ensure use `setLogLevel()` to set the minimum proper log level threshold to the project.