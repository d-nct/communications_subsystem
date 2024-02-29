#include "Logger.h"

template <typename T>
void Logger::log(LogLevel_t level, const T& message) {
    if (level >= levelThreshold) {
        Serial.print("[");
        Serial.print(toString(level));
        Serial.print("] ");
        Serial.println(message);
    }
}

template <typename T>
void Logger::print(LogLevel_t level, const T& message) {
    if (level >= levelThreshold) {
        Serial.print(message);
    }
}

void Logger::setLogLevel(LogLevel_t level) {
    levelThreshold = level;
}

const char* Logger::toString(LogLevel_t level) {
    switch (level) {
        case LOG_ERROR:   return "ERROR";
        case LOG_WARNING: return "WARNING";
        case LOG_INFO:    return "INFO";
        case LOG_DEBUG:   return "DEBUG";
        default:          return "UNKNOWN";
    }
}

const char* Logger::toString(RF_RSSI_Status_t status){
    switch (status) {
        case RSSI_GOOD:      return "GOOD";
        case RSSI_NORMAL:    return "NORMAL";
        case RSSI_WARNING:   return "WARNING";
        case RSSI_CRITICAL:  return "CRITICAL";
        case RSSI_NO_SIGNAL: return "NO SIGNAL";
        default:             return "UNKNOWN";
    }
}

const char* Logger::toString(RF_Packet_Status_t status) {
    switch (status) {
        case PACKET_GOOD:      return "GOOD";
        case PACKET_NORMAL:    return "NORMAL";
        case PACKET_WARNING:   return "WARNING";
        case PACKET_CRITICAL:  return "CRITICAL";
        case PACKET_NO_SIGNAL: return "NO SIGNAL";
        default:               return "UNKNOWN";
    }
}