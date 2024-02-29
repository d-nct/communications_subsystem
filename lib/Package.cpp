#include "Package.h"

com_serialized* Package::serialize(const Telemetry& data, com_serialized* serializedData) {
  std::memcpy(serializedData, &data, sizeof(data));
}

Telemetry Package::deserialize(const com_serialized* serializedData) {
  Telemetry result;
  std::memcpy(&result, serializedData, sizeof(result));
  return result;
}