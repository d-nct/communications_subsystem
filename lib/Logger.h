#ifndef LOG_H
#define LOG_H

#include "_config.h"
#include "_types.h"

class Logger {
public:
  /**
   * Log a message with the given log level.
   * 
   * @param level The log level of the message.
   * @param message The message to log.
  */
  static void log(LogLevel_t level, const char* message);

  /**
   * Log a message with the given log level, without newline.
   * 
   * @param level The log level of the message.
   * @param message The message to log.
  */
  static void print(LogLevel_t level, const char* message);

  /**
   * Set the minimum log level to log a message.
   * 
   * @param level The minimum log level to log a message.
  */
  static void setLogLevel(LogLevel_t level);

  /**
   * Convert LogLevel to a string.
   * 
   * @param level The log level to convert.
  */
  static const char* toString(LogLevel_t level);

  /**
   * Convert RSSI status to a string.
   * 
   * @param status The RSSI status to convert.
  */
  static const char* toString(RF_RSSI_Status_t status);

  /**
   * Convert Packet status to a string.
   * 
   * @param status The Packet status to convert.
  */
  static const char* toString(RF_Packet_Status_t status);

private:
  static LogLevel_t levelThreshold; /* Minimum level to log a message. */
};

LogLevel_t Logger::levelThreshold = LOG_DEBUG;  // Defina o nível padrão

#endif // LOG_H