# Communication Lib

## `ComRF` Class
### Overview
The `ComRF` class in `CommunicationRF.h` is a C++ class that facilitates communication using LoRa technology. It provides methods for initializing LoRa, sending and receiving telemetry packets, and managing packet configurations.

### Methods and Members
See the doxygen in `CommunicationRF.h`.

### Guidelines
1. Ensure proper initialization using the `setup()` method before sending or receiving packets.

2. Configure telemetry packets using `configurePacket()` before sending.

3. Use `sendPacket()` to transmit telemetry data.

4. Retrieve received telemetry using `receivePacket()` and access the data using appropriate methods.


## `MonitorRF` Class
### Overview 
The `MonitorRF` class, defined in the "MonitorRF.h" file, is responsible for monitoring the transceiver communication status. It keeps track of important metrics such as RSSI (Received Signal Strength Indication), packet success rate, and various status indicators. The class provides methods for updating and retrieving these metrics, as well as logging the monitoring results.

TODO: include LEDs for status in the Ground Station.

### Methods and Members
See the doxygen in `CommunicationRF.h`.

### Monitoring Strategy
1. Regular Monitoring: Periodically call the `monitor()` method to obtain an overview of the LoRa communication status. The `Logger` class is used to log important communication metrics in `LOG_INFO` level.

2. Incremental Packet Counting: Use `incrementPacketSended()` and `incrementPacketReceived()` methods to keep track of the total sent and received packets. This is already implemented in `ComRF::sendPacket()` and `ComRF::receivePacket()`.


## `Package` Class
### Overview
The `Package` class, defined in the "Package.h" file, provides functionalities for serializing and deserializing telemetry data. Telemetry, represented by the Telemetry structure, is a structured set of data related to communication status or other relevant metrics. Additionally, the class includes a method for printing telemetry data in a verbose manner using the Logger class.

Please, be shure to fill the `Telemetry` struct, defined in `_types.h` to match the sensors in the project design.

### Methods and Members
See the doxygen in `Package.h`.

### Additional Considerations
1. Review and potentially optimize the deserialization approach to avoid unnecessary object creation.

2. The method `printTelemetry()` only prints the telemetry in `LOG_INFO` log level.


