#include "Package.h"

com_serialized* Package::serialize(const Telemetry& data, com_serialized* serializedData) {
  std::memcpy(serializedData, &data, sizeof(data));
}

Telemetry Package::deserialize(const com_serialized* serializedData) {
  Telemetry result;
  std::memcpy(&result, serializedData, sizeof(result));
  return result;
}

void Package::printTelemetry(const Telemetry& telemetry) {
  Logger::log(LOG_INFO, "Received Packet ID: "); Serial.print(String(telemetry.id) + ",");
  Logger::print(LOG_INFO, " Timestamp: ");   Serial.print(String(telemetry.timestamp) + ",");
  Logger::print(LOG_INFO, " Latitude: ");    Serial.print(String(telemetry.latitude) + ",");
  Logger::print(LOG_INFO, " Longitude: ");   Serial.print(String(telemetry.longitude) + ",");
  Logger::print(LOG_INFO, " Altitude: ");    Serial.print(String(telemetry.altitude) + ",");
  Logger::print(LOG_INFO, " Speed: ");       Serial.print(String(telemetry.speed) + "\n");
  Logger::print(LOG_INFO, " Satellites: ");  Serial.print(String(telemetry.satellites) + "\n");
  Logger::print(LOG_INFO, " Voltage: ");     Serial.print(String(telemetry.voltage) + "\n");
  Logger::print(LOG_INFO, " Temperature: "); Serial.print(String(telemetry.temperature) + "\n");
}