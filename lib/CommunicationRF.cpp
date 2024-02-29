#include "CommunicationRF.h"

int ComRF::setup() {
    int status;

    // Inicializa o LoRa
    LoRa.setPins(LORA_PIN_SS, LORA_PIN_RST, LORA_PIN_DIO0);
    
    if (status = LoRa.begin(LORA_FREQUENCY) != 1){
        Logger::log(LOG_ERROR, "Erro ao inicializar o LoRa.");
        while (1);
    }
    
    LoRa.setSyncWord(LORA_SYNC_WORD);
    
    Logger::log(LOG_INFO, "LoRa inicializado.");
    return status;
}

void ComRF::sendPacket(const Telemetry& packet) {
    // Serializa a mensagem
    Package::serialize(packet, buffer_sender);

    // Envia a mensagem serializada
    LoRa.beginPacket();
    LoRa.write(buffer_sender, telemetry_length);
    LoRa.endPacket();

    // Logga
    Logger::log(LOG_INFO, "LoRa: Pacote enviado.");
    Logger::print(LOG_DEBUG, "Conteúdo serializado: ");
    for (size_t i = 0; i < telemetry_length; i++) {
        Logger::print(LOG_DEBUG, (char*) buffer_sender[i]);
    }
    Logger::print(LOG_DEBUG, "\n");

    // Atualiza o contador de pacotes enviados
    packages_sended++;
}

void ComRF::configurePackage(Telemetry& packet) {
    packet.id = getPackageId();
    packet.timestamp = millis();
}

com_uint ComRF::getPackageId() {
    return package_id;
}

void ComRF::updatePackageId() {
    package_id++;
}


Telemetry* ComRF::receivePacket() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // atualiza o contador de pacotes recebidos
        packages_received++;

        // Logga
        Logger::log(LOG_INFO, "LoRa: Pacote recebido.");
        Logger::print(LOG_DEBUG, "Conteúdo serializado: ");
        
        int i = 0;
        while (LoRa.available()) {
            com_serialized c = LoRa.read();
            buffer_receiver[i] = c;

            Logger::print(LOG_DEBUG, (char*) c);
        }
        
        Logger::print(LOG_DEBUG, "\n");
    }

    // Deserializa a mensagem
    telemetry_received = Package::deserialize(buffer_receiver);

    return &telemetry_received;
}

com_serialized* ComRF::getBufferReceiver() {
    return buffer_receiver;
}

void ComRF::monitor() {

    // Verifica o RSSI
    if (LoRa.packetRssi() > -85) {
        status_rssi = RSSI_GOOD;
    } else if (LoRa.packetRssi() > -100) {
        status_rssi = RSSI_NORMAL;
    } else if (LoRa.packetRssi() > -110) {
        status_rssi = RSSI_WARNING;
    } else {
        status_rssi = RSSI_CRITICAL;
    }

    // Verifica o status do pacote
    if (telemetry_received.id == 0) {
        status_packet = PACKET_NO_SIGNAL;
    } else {
        packages_received_rate = (float) packages_received / (float) telemetry_received.id;
        if (packages_received_rate > 0.75) {
            status_packet = PACKET_GOOD;
        } else if (packages_received_rate > 0.50) {
            status_packet = PACKET_NORMAL;
        } else if (packages_received_rate > 0.25) {
            status_packet = PACKET_WARNING;
        } else if (packages_received_rate > 0.05) {
            status_packet = PACKET_CRITICAL;
        } else {
            status_packet = PACKET_NO_SIGNAL;
        }
    }

}